#include "platform/FileDialog.h"
#include "scripting/lua-bindings/manual/lua_conversion/lua_conversion_tolua.hpp"
#include <cmath>
#include <stdexcept>
#include <string_view>

namespace {
using namespace cc;
template<class T> const char* meta();
template<> const char* meta<DocumentHandle>() { return "cc.Document"; }
template<> const char* meta<SaveTarget>() { return "cc.SaveTarget"; }
template<> const char* meta<DialogRequest>() { return "cc.DialogRequest"; }
template<class T> struct Box { bool alive; alignas(T) unsigned char storage[sizeof(T)]; };
template<class T> Box<T>* box(lua_State* L, int i) {
    if (lua_type(L, i) != LUA_TUSERDATA || lua_objlen(L, i) != sizeof(Box<T>) || !lua_getmetatable(L, i)) return nullptr;
    luaL_getmetatable(L, meta<T>());
    bool matches = lua_rawequal(L, -1, -2) != 0; lua_pop(L, 2);
    return matches ? static_cast<Box<T>*>(lua_touserdata(L, i)) : nullptr;
}
template<class T> T& value(lua_State* L, int i) {
    auto b = box<T>(L, i);
    if (!b || !b->alive) throw std::invalid_argument(meta<T>());
    return *std::launder(reinterpret_cast<T*>(b->storage));
}
template<class T> int collect(lua_State* L) {
    auto b = box<T>(L, 1);
    if (b && b->alive) { b->alive = false; std::launder(reinterpret_cast<T*>(b->storage))->~T(); }
    return 0;
}
template<class T> void push(lua_State* L, const T& object) {
    auto b = new (lua_newuserdata(L, sizeof(Box<T>))) Box<T>{};
    luaL_getmetatable(L, meta<T>()); lua_setmetatable(L, -2);
    new (b->storage) T(object); b->alive = true;
}
void str(lua_State* L, const std::string& s) { lua_pushlstring(L, s.data(), s.size()); }
void set(lua_State* L, const char* k, const std::string& v) { str(L, v); lua_setfield(L, -2, k); }
void flag(lua_State* L, const char* k, bool v) { lua_pushboolean(L, v); lua_setfield(L, -2, k); }
const char* errors[] = {"none","invalidArgument","wrongThread","notInitialized","busy","unavailable","unsupportedFeature",
    "parentClosed","permissionDenied","notFound","invalidResult","encodingError","ioError","limitExceeded","timeout","outOfMemory","backendError"};
void errorTable(lua_State* L, const FileDialogError& error) {
    lua_createtable(L, 0, 4);
    set(L, "code", errors[static_cast<unsigned>(error.code)]); set(L, "message", error.message);
    set(L, "nativeDomain", error.nativeDomain); lua_pushnumber(L, static_cast<lua_Number>(error.nativeCode)); lua_setfield(L, -2, "nativeCode");
}
template<class T> void resultTable(lua_State* L, const T& r) {
    lua_createtable(L, 0, 8);
    set(L, "status", r.status == DialogStatus::Ok ? "ok" : r.status == DialogStatus::Cancelled ? "cancelled" : "error");
    set(L, "cancelReason", r.cancelReason == CancelReason::Caller ? "caller" : r.cancelReason == CancelReason::User ? "user" : "none");
    if (r.error) { errorTable(L, r.error); lua_setfield(L, -2, "error"); }
    if constexpr (std::is_same_v<T, SelectionResult> || std::is_same_v<T, DocumentResult>) {
        lua_createtable(L, static_cast<int>(r.documents.size()), 0);
        int i = 0; for (const auto& doc : r.documents) { push(L, doc); lua_rawseti(L, -2, ++i); }
        lua_setfield(L, -2, "documents");
    }
    if constexpr (std::is_same_v<T, SelectionResult> || std::is_same_v<T, SaveTargetResult>) {
        if (r.selectedFilter) { lua_pushinteger(L, *r.selectedFilter + 1); lua_setfield(L, -2, "selectedFilter"); }
    }
    if constexpr (std::is_same_v<T, SaveTargetResult>) {
        if (r.target) { push(L, r.target); lua_setfield(L, -2, "target"); }
    }
    if constexpr (std::is_same_v<T, ExportResult> || std::is_same_v<T, DocumentResult>) {
        const char* effects[] = {"none","committed","partialPossible","unknown"};
        set(L, "effect", effects[static_cast<unsigned>(r.effect)]);
    }
    if constexpr (std::is_same_v<T, ExportResult>) {
        if (r.destination) { push(L, *r.destination); lua_setfield(L, -2, "destination"); }
        set(L, "displayName", r.displayName);
    }
    if constexpr (std::is_same_v<T, DocumentResult>) {
        if (!r.nextPage.empty()) set(L, "nextPage", r.nextPage);
    }
}
}
namespace lua {
template<> struct to_lua<cc::DocumentResult> { static void F(lua_State* L, const cc::DocumentResult& r) { resultTable(L, r); } };
template<> struct to_lua<cc::ExportResult> { static void F(lua_State* L, const cc::ExportResult& r) { resultTable(L, r); } };
template<> struct to_lua<cc::SelectionResult> { static void F(lua_State* L, const cc::SelectionResult& r) { resultTable(L, r); } };
template<> struct to_lua<cc::SaveTargetResult> { static void F(lua_State* L, const cc::SaveTargetResult& r) { resultTable(L, r); } };
}
namespace {
void requireTable(lua_State* L, int i) {
    if (!lua_istable(L, i)) throw std::invalid_argument("Expected options table");
}
template<class F> void field(lua_State* L, int table, const char* name, F parse) {
    table = lua::_absolute_index(L, table);
    requireTable(L, table); lua_pushstring(L, name); lua_rawget(L, table);
    if (!lua_isnil(L, -1)) parse(lua_gettop(L));
    lua_pop(L, 1);
}
std::string stringAt(lua_State* L, int i) {
    if (lua_type(L, i) != LUA_TSTRING) throw std::invalid_argument("Expected string");
    size_t n = 0; auto p = lua_tolstring(L, i, &n); return {p, n};
}
uint64_t numberAt(lua_State* L, int i, uint64_t maximum) {
    auto n = lua_tonumber(L, i);
    if (lua_type(L, i) != LUA_TNUMBER || !std::isfinite(n) || n < 0 || n > static_cast<double>(maximum) || std::floor(n) != n)
        throw std::invalid_argument("Expected non-negative integer in range");
    return static_cast<uint64_t>(n);
}
template<class F> void array(lua_State* L, int i, F item) {
    requireTable(L, i); auto n = lua_objlen(L, i);
    if (n > 1024) throw std::invalid_argument("Filter array too large");
    for (size_t k = 1; k <= n; ++k) { lua_rawgeti(L, i, static_cast<int>(k)); item(lua_gettop(L)); lua_pop(L, 1); }
}
FileDialogFilter filter(lua_State* L, int i) {
    FileDialogFilter f;
    field(L, i, "label", [&](int k) { f.label = stringAt(L, k); });
    auto strings = [&](const char* key, auto& dest) {
        field(L, i, key, [&](int k) { array(L, k, [&](int j) { dest.push_back(stringAt(L, j)); }); });
    };
    strings("extensions", f.extensions); strings("mimeTypes", f.mimeTypes); strings("appleTypeIdentifiers", f.appleTypeIdentifiers);
    return f;
}
template<class T> void common(lua_State* L, int i, T& o) {
    field(L, i, "title", [&](int k) { o.title = stringAt(L, k); });
    field(L, i, "initialDirectory", [&](int k) { o.initialDirectory = value<DocumentHandle>(L, k); });
}
void openOptions(lua_State* L, OpenFileOptions& o) {
    common(L, 1, o);
    field(L, 1, "filters", [&](int k) { array(L, k, [&](int j) { o.filters.push_back(filter(L, j)); }); });
    auto boolean = [&](const char* key, bool& out) {
        field(L, 1, key, [&](int k) { if (!lua_isboolean(L,k)) throw std::invalid_argument(key); out = lua_toboolean(L,k) != 0; });
    };
    boolean("allowMultiple", o.allowMultiple); boolean("allowAllFiles", o.allowAllFiles);
    field(L, 1, "maxSelectionCount", [&](int k) { o.maxSelectionCount = static_cast<uint32_t>(numberAt(L, k, UINT32_MAX)); });
}
TransferLimits limits(lua_State* L, int i) {
    TransferLimits v;
    field(L, i, "maxBytes", [&](int k) { v.maxBytes = numberAt(L, k, 9007199254740991ull); });
    field(L, i, "timeoutSeconds", [&](int k) { v.timeoutSeconds = static_cast<uint32_t>(numberAt(L, k, UINT32_MAX)); });
    return v;
}
template<class T> std::function<void(T)> callback(lua_State* L, int i) {
    std::function<void(T)> cb;
    if (!lua::luaval_to_owned_callback(L, i, &cb, "cc.FileDialog") || !cb) throw std::invalid_argument("Expected completion function");
    return cb;
}
int submitted(lua_State* L, const DialogSubmission& s) {
    if (s.request) { push(L, *s.request); return 1; }
    lua_pushnil(L); errorTable(L, s.error); return 2;
}
template<int(*F)(lua_State*)> int checked(lua_State* L) {
    try { return F(L); }
    catch (const std::exception& e) {
        lua_pushnil(L); errorTable(L, {DialogErrorCode::InvalidArgument, e.what()}); return 2;
    }
}

int open(lua_State* L) { OpenFileOptions o; openOptions(L,o); return submitted(L, FileDialog::openFiles(std::move(o), callback<SelectionResult>(L,2))); }
int folder(lua_State* L) { FolderOptions o; common(L,1,o); return submitted(L, FileDialog::pickFolder(std::move(o), callback<SelectionResult>(L,2))); }
int save(lua_State* L) {
    SaveTargetOptions o; openOptions(L,o);
    field(L,1,"suggestedName",[&](int k) { o.suggestedName = stringAt(L,k); });
    return submitted(L, FileDialog::chooseSaveTarget(std::move(o), callback<SaveTargetResult>(L,2)));
}
int exportFile(lua_State* L) {
    ExportFileOptions o; common(L,1,o);
    field(L,1,"suggestedName",[&](int k) { o.suggestedName = stringAt(L,k); });
    field(L,1,"contentType",[&](int k) { o.contentType = filter(L,k); });
    field(L,1,"limits",[&](int k) { o.limits = limits(L,k); });
    return submitted(L, FileDialog::exportFile(std::move(o), value<DocumentHandle>(L,2), callback<ExportResult>(L,3)));
}
int local(lua_State* L) {
    auto kind = lua_gettop(L) > 1 ? stringAt(L,2) : "file";
    if (kind != "file" && kind != "directory") throw std::invalid_argument("Unknown document kind");
    auto doc = DocumentAccess::fromLocalPath(stringAt(L,1), kind == "file" ? DocumentKind::File : DocumentKind::Directory);
    if (!doc) throw std::invalid_argument("Expected absolute UTF-8 path");
    push(L, doc); return 1;
}
int importFile(lua_State* L) {
    std::string path;
    field(L,2,"destination",[&](int k) { path = stringAt(L,k); });
    return submitted(L, DocumentAccess::importFile(value<DocumentHandle>(L,1), std::move(path), limits(L,2), callback<DocumentResult>(L,3)));
}
int list(lua_State* L) {
    std::string token; uint32_t limit = 128;
    field(L,2,"pageToken",[&](int k) { token = stringAt(L,k); });
    field(L,2,"limit",[&](int k) { limit = static_cast<uint32_t>(numberAt(L,k,1024)); });
    return submitted(L, DocumentAccess::listChildren(value<DocumentHandle>(L,1), std::move(token), limit, callback<DocumentResult>(L,3)));
}
int child(lua_State* L) {
    return submitted(L, DocumentAccess::exportChild(value<DocumentHandle>(L,1), stringAt(L,2), value<DocumentHandle>(L,3), limits(L,4), callback<DocumentResult>(L,5)));
}
int write(lua_State* L) {
    return submitted(L, DocumentAccess::writeTarget(value<SaveTarget>(L,1), value<DocumentHandle>(L,2), limits(L,3), callback<DocumentResult>(L,4)));
}
int cancel(lua_State* L) {
    const char* names[] = {"accepted","tooLate","alreadyFinished"};
    lua_pushstring(L, names[static_cast<unsigned>(value<DialogRequest>(L,1).cancel())]); return 1;
}
template<class T> int path(lua_State* L) {
    FileDialogError error;
    auto s = value<T>(L,1).tryGetLocalPath(error);
    if (s) str(L,*s); else lua_pushnil(L);
    if (error) { errorTable(L,error); return 2; }
    return 1;
}
int info(lua_State* L) {
    const auto& d = value<DocumentHandle>(L,1);
    lua_createtable(L,0,5);
    set(L,"displayName",d.displayName()); set(L,"mimeType",d.mimeType());
    set(L,"kind",d.kind() == DocumentKind::File ? "file" : "directory");
    const char* locations[] = {"localFile","androidDocument","appleDocument"};
    set(L,"locationKind",locations[static_cast<unsigned>(d.locationKind())]);
    if (auto size = d.size()) { lua_pushnumber(L,static_cast<double>(*size)); lua_setfield(L,-2,"size"); }
    const auto hints = d.accessHints();
    lua_createtable(L,0,3);
    flag(L,"read",hints.read); flag(L,"listChildren",hints.listChildren); flag(L,"createChild",hints.createChild);
    lua_setfield(L,-2,"accessHints");
    return 1;
}
int legacyUri(lua_State* L) { str(L, value<DocumentHandle>(L,1).legacyAndroidUri()); return 1; }
int capabilities(lua_State* L) {
    auto c = FileDialog::capabilities();
    lua_createtable(L,0,11);
    set(L,"backend",c.backend); set(L,"unavailableReason",c.unavailableReason);
    flag(L,"available",c.available); flag(L,"openFiles",c.openFiles); flag(L,"pickFolder",c.pickFolder);
    flag(L,"multipleFiles",c.multipleFiles); flag(L,"exportFile",c.exportFile); flag(L,"chooseSaveTarget",c.chooseSaveTarget);
    flag(L,"physicalDismiss",c.physicalDismiss); flag(L,"selectedFilter",c.selectedFilter); flag(L,"initialDirectoryHint",c.initialDirectoryHint);
    return 1;
}
template<class T> void registerType(lua_State* L, const luaL_Reg* methods) {
    luaL_newmetatable(L, meta<T>()); lua_pushcfunction(L, collect<T>); lua_setfield(L,-2,"__gc");
    lua_pushstring(L,meta<T>()); lua_setfield(L,-2,"__metatable");
    lua_newtable(L); luaL_register(L,nullptr,methods); lua_setfield(L,-2,"__index"); lua_pop(L,1);
}
}
void register_file_dialog(lua_State* L) {
    const luaL_Reg doc[] = {{"info",checked<info>},{"tryGetLocalPath",checked<path<DocumentHandle>>},
        {"legacyAndroidUri",checked<legacyUri>},{nullptr,nullptr}};
    const luaL_Reg target[] = {{"tryGetLocalPath",checked<path<SaveTarget>>},{nullptr,nullptr}};
    const luaL_Reg request[] = {{"cancel",checked<cancel>},{nullptr,nullptr}};
    registerType<DocumentHandle>(L,doc); registerType<SaveTarget>(L,target); registerType<DialogRequest>(L,request);
    const luaL_Reg methods[] = {
        {"capabilities",checked<capabilities>},{"openFiles",checked<open>},{"pickFolder",checked<folder>},
        {"chooseSaveTarget",checked<save>},{"exportFile",checked<exportFile>},{"fromLocalPath",checked<local>},
        {"importFile",checked<importFile>},{"listChildren",checked<list>},{"exportChild",checked<child>},{"writeTarget",checked<write>},{nullptr,nullptr}
    };
    lua_getglobal(L,"cc"); lua_newtable(L); luaL_register(L,nullptr,methods); lua_setfield(L,-2,"FileDialog"); lua_pop(L,1);
}
