#pragma once

#include <cstdlib>
#include <cstdint>
#include <dlfcn.h>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct sd_bus;
struct sd_bus_error;
struct sd_bus_message;

namespace cc::system_info::linux_detail
{
// The system bus is optional. Keep the public sd-bus ABI here so systems without
// the development package, or without the runtime library, can use the kernel backend.
class SystemBus
{
    struct Api
    {
        int (*open)(sd_bus**) = nullptr;
        sd_bus* (*unref)(sd_bus*) = nullptr;
        int (*setTimeout)(sd_bus*, uint64_t) = nullptr;
        sd_bus_message* (*unrefMessage)(sd_bus_message*) = nullptr;
        int (*call)(sd_bus*, const char*, const char*, const char*, const char*, sd_bus_error*,
                    sd_bus_message**, const char*, ...) = nullptr;
        int (*get)(sd_bus*, const char*, const char*, const char*, const char*, sd_bus_error*,
                   sd_bus_message**, const char*) = nullptr;
        int (*read)(sd_bus_message*, const char*, ...) = nullptr;
        int (*enter)(sd_bus_message*, char, const char*) = nullptr;
        int (*exit)(sd_bus_message*) = nullptr;
        int (*skip)(sd_bus_message*, const char*) = nullptr;
        void* library = nullptr;

        template <typename T>
        bool load(T& function, const char* name)
        {
            function = reinterpret_cast<T>(dlsym(library, name));
            return function != nullptr;
        }

        Api()
        {
            library = dlopen("libsystemd.so.0", RTLD_LAZY | RTLD_LOCAL);
            if (!library)
                return;
            if (!load(open, "sd_bus_open_system") || !load(unref, "sd_bus_unref") ||
                !load(setTimeout, "sd_bus_set_method_call_timeout") ||
                !load(unrefMessage, "sd_bus_message_unref") ||
                !load(call, "sd_bus_call_method") || !load(get, "sd_bus_get_property") ||
                !load(read, "sd_bus_message_read") || !load(enter, "sd_bus_message_enter_container") ||
                !load(exit, "sd_bus_message_exit_container") || !load(skip, "sd_bus_message_skip"))
            {
                dlclose(library);
                library = nullptr;
            }
        }

        ~Api()
        {
            if (library)
                dlclose(library);
        }
    };

    static const Api& api()
    {
        static const Api loaded;
        return loaded;
    }

    sd_bus* _bus = nullptr;

public:
    using Message = std::unique_ptr<sd_bus_message, decltype(Api::unrefMessage)>;

    SystemBus()
    {
        if (api().library && api().open(&_bus) >= 0)
            api().setTimeout(_bus, 250'000);
    }

    ~SystemBus()
    {
        if (_bus)
            api().unref(_bus);
    }

    SystemBus(const SystemBus&) = delete;
    SystemBus& operator=(const SystemBus&) = delete;

    template <typename... Args>
    Message call(const char* destination, const char* path, const char* interface, const char* method,
                 const char* signature, Args... args) const
    {
        sd_bus_message* reply = nullptr;
        if (_bus)
            api().call(_bus, destination, path, interface, method, nullptr, &reply, signature, args...);
        return Message(reply, api().unrefMessage);
    }

    Message property(const char* owner, const char* path, const char* interface,
                     const char* name, const char* signature) const
    {
        sd_bus_message* reply = nullptr;
        if (_bus && owner)
            api().get(_bus, owner, path, interface, name, nullptr, &reply, signature);
        return Message(reply, api().unrefMessage);
    }

    template <typename... Args>
    static bool read(const Message& message, const char* signature, Args... args)
    {
        return message && api().read(message.get(), signature, args...) > 0;
    }

    static bool enter(const Message& message, char type, const char* contents)
    {
        return message && api().enter(message.get(), type, contents) > 0;
    }

    static bool exit(const Message& message)
    {
        return message && api().exit(message.get()) >= 0;
    }

    static bool skip(const Message& message, const char* signature)
    {
        return message && api().skip(message.get(), signature) > 0;
    }

    // Use the unique owner for calls so observing an inactive service never starts it.
    std::optional<std::string> owner(const char* service) const
    {
        auto message = call("org.freedesktop.DBus", "/org/freedesktop/DBus",
                            "org.freedesktop.DBus", "GetNameOwner", "s", service);
        const char* name = nullptr;
        if (read(message, "s", &name))
            return std::string(name);
        return std::nullopt;
    }

    std::optional<std::string> text(const char* owner, const char* path, const char* interface,
                                    const char* propertyName, const char* signature = "s") const
    {
        auto message = property(owner, path, interface, propertyName, signature);
        const char* value = nullptr;
        if (read(message, signature, &value))
            return std::string(value);
        return std::nullopt;
    }

    template <typename T>
    std::optional<T> scalar(const char* owner, const char* path, const char* interface,
                            const char* propertyName, const char* signature) const
    {
        auto message = property(owner, path, interface, propertyName, signature);
        T value{};
        if (read(message, signature, &value))
            return value;
        return std::nullopt;
    }

    std::optional<std::vector<std::string>> paths(const char* owner, const char* path, const char* interface,
                                                  const char* propertyName) const
    {
        auto message = property(owner, path, interface, propertyName, "ao");
        if (!enter(message, 'a', "o"))
            return std::nullopt;
        std::vector<std::string> result;
        const char* value = nullptr;
        while (read(message, "o", &value))
            result.emplace_back(value);
        if (!exit(message))
            return std::nullopt;
        return result;
    }
};
} // namespace cc::system_info::linux_detail
