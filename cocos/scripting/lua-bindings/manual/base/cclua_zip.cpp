#include "scripting/lua-bindings/manual/base/cclua_file_read.hpp"
#include "io/zip/ZipReader.h"
#include "io/zip/ZipWriter.h"
#include <algorithm>
#include <cmath>

using namespace cc;
using namespace cc::archive;
using namespace cc::luaio;

namespace
{
constexpr auto readerType = "cc.ZipReader";
constexpr auto writerType = "cc.ZipWriter";
constexpr auto entryIdType = "cc.ZipEntryId";

template<class Integer>
Integer integerField(lua_State* L, int index, const char* field, Integer fallback)
{
    if (lua_isnoneornil(L, index))
        return fallback;
    luaL_checktype(L, index, LUA_TTABLE);
    lua_pushstring(L, field);
    lua_rawget(L, index);
    if (lua_isnil(L, -1))
    {
        lua_pop(L, 1);
        return fallback;
    }
    Integer value{};
    bool valid;
    if (lua_type(L, -1) == LUA_TSTRING)
    {
        const auto input = checkString(L, -1);
        const auto parsed = std::from_chars(input.data(), input.data() + input.size(), value);
        valid = parsed.ec == std::errc{} && parsed.ptr == input.data() + input.size();
    }
    else
    {
        const auto number = lua_tonumber(L, -1);
        const auto bound = std::ldexp(1.0, std::min(53, std::numeric_limits<Integer>::digits));
        valid = lua_type(L, -1) == LUA_TNUMBER && number >= 0 && number < bound && std::trunc(number) == number;
        if (valid)
            value = static_cast<Integer>(number);
    }
    lua_pop(L, 1);
    if (!valid)
        luaL_error(L, "invalid ZIP option '%s'", field);
    return value;
}

std::optional<std::string_view> stringField(lua_State* L, int index, const char* field)
{
    if (lua_isnoneornil(L, index))
        return std::nullopt;
    luaL_checktype(L, index, LUA_TTABLE);
    lua_pushstring(L, field);
    lua_rawget(L, index);
    std::optional<std::string_view> result;
    if (!lua_isnil(L, -1))
    {
        if (lua_type(L, -1) != LUA_TSTRING)
            luaL_error(L, "invalid ZIP option '%s'", field);
        result = checkString(L, -1);
    }
    lua_pop(L, 1);
    return result;
}

ZipReadOptions readOptions(lua_State* L, int index)
{
    ZipReadOptions options;
    options.maxArchiveBytes = integerField(L, index, "maxArchiveBytes", options.maxArchiveBytes);
    options.maxEntries = integerField(L, index, "maxEntries", options.maxEntries);
    options.maxIndexBytes = integerField(L, index, "maxIndexBytes", options.maxIndexBytes);
    if (!lua_isnoneornil(L, index))
    {
        lua_pushliteral(L, "checkConsistency");
        lua_rawget(L, index);
        options.checkConsistency = lua_toboolean(L, -1) != 0;
        lua_pop(L, 1);
    }
    options.password = stringField(L, index, "password").value_or("");
    return options;
}

EntryReadOptions entryReadOptions(lua_State* L, int index)
{
    EntryReadOptions options;
    options.maxBytes = integerField(L, index, "maxBytes", options.maxBytes);
    if (const auto password = stringField(L, index, "password"))
        options.password = std::string(*password);
    return options;
}

EntryWriteOptions entryWriteOptions(lua_State* L, int index)
{
    EntryWriteOptions options;
    options.compression = static_cast<Compression>(integerField(L, index, "compression",
        static_cast<uint16_t>(options.compression)));
    options.level = integerField(L, index, "level", options.level);
    options.encryption = static_cast<Encryption>(integerField(L, index, "encryption",
        static_cast<uint16_t>(options.encryption)));
    options.password = stringField(L, index, "password").value_or("");
    return options;
}

Bytes copyBytes(std::string_view input)
{
    auto data = reinterpret_cast<const uint8_t*>(input.data());
    return std::make_shared<std::vector<uint8_t>>(data, data + input.size());
}

int pushReader(lua_State* L, io::Result<ZipReader::Ptr> reader)
{
    if (!reader)
        return pushError(L, reader.error);
    pushObject<ZipReader::Ptr>(L, readerType, std::move(reader.value));
    return 1;
}

int openFile(lua_State* L)
{
    const auto path = checkString(L, 2);
    return pushReader(L, ZipReader::openFile(path, readOptions(L, 3)));
}

int openBuffer(lua_State* L)
{
    const auto input = checkString(L, 2);
    const auto options = readOptions(L, 3);
    if (input.size() > options.maxArchiveBytes)
        return pushError(L, {io::ErrorCode::LimitExceeded});
    return pushReader(L, ZipReader::openBuffer(copyBytes(input), options));
}

int find(lua_State* L)
{
    const auto& reader = checkObject<ZipReader::Ptr>(L, 1, readerType);
    const auto id = reader->find(checkString(L, 2));
    if (!id)
        return pushError(L, id.error);
    pushObject<EntryId>(L, entryIdType, id.value);
    return 1;
}

template<class T>
void setMetadata(lua_State* L, const char* name, const std::optional<T>& value)
{
    if (value)
    {
        pushExact(L, *value);
        lua_setfield(L, -2, name);
    }
}

int entries(lua_State* L)
{
    const auto& reader = checkObject<ZipReader::Ptr>(L, 1, readerType);
    const auto entries = reader->entries();
    lua_createtable(L, static_cast<int>(entries.size()), 0);
    int index = 1;
    for (const auto& entry : entries)
    {
        lua_createtable(L, 0, 9);
        pushObject<EntryId>(L, entryIdType, entry.id);
        lua_setfield(L, -2, "id");
        setString(L, "name", entry.name);
        constexpr const char* types[] = {"file", "directory", "link", "other"};
        setString(L, "type", types[static_cast<int>(entry.type)]);
        setMetadata(L, "size", entry.size);
        setMetadata(L, "compressedSize", entry.compressedSize);
        setMetadata(L, "crc", entry.crc);
        setMetadata(L, "modified", entry.modified);
        setMetadata(L, "compression", entry.compression);
        setMetadata(L, "encryption", entry.encryption);
        lua_rawseti(L, -2, index++);
    }
    return 1;
}

int readEntry(lua_State* L)
{
    const auto& reader = checkObject<ZipReader::Ptr>(L, 1, readerType);
    const auto& id = checkObject<EntryId>(L, 2, entryIdType);
    const auto data = reader->readEntry(id, entryReadOptions(L, 3));
    if (!data)
        return pushError(L, data.error);
    pushString(L, data.value->empty() ? std::string_view{} :
        std::string_view(reinterpret_cast<const char*>(data.value->data()), data.value->size()));
    return 1;
}

int verify(lua_State* L)
{
    const auto& reader = checkObject<ZipReader::Ptr>(L, 1, readerType);
    const auto& id = checkObject<EntryId>(L, 2, entryIdType);
    return pushStatus(L, reader->verify(id, entryReadOptions(L, 3)));
}

template<class Enum>
void setCapabilities(lua_State* L, const char* field, const std::vector<Enum>& values)
{
    lua_createtable(L, static_cast<int>(values.size()), 0);
    int index = 1;
    for (const auto value : values)
    {
        lua_pushinteger(L, static_cast<int>(value));
        lua_rawseti(L, -2, index++);
    }
    lua_setfield(L, -2, field);
}

int capabilities(lua_State* L)
{
    const auto caps = zipCapabilities();
    lua_createtable(L, 0, 4);
    setCapabilities(L, "readCompression", caps.readCompression);
    setCapabilities(L, "writeCompression", caps.writeCompression);
    setCapabilities(L, "readEncryption", caps.readEncryption);
    setCapabilities(L, "writeEncryption", caps.writeEncryption);
    return 1;
}

int begin(lua_State* L)
{
    const auto path = checkString(L, 2);
    const auto intent = luaL_checknumber(L, 3);
    if (intent != 0 && intent != 1 && intent != 2)
        return pushError(L, {io::ErrorCode::InvalidArgument});
    ZipWriteOptions options;
    options.maxStagedBytes = integerField(L, 4, "maxStagedBytes", options.maxStagedBytes);
    auto writer = ZipWriter::begin(path, static_cast<WriteIntent>(static_cast<int>(intent)), options);
    if (!writer)
        return pushError(L, writer.error);
    pushObject<ZipWriter::Ptr>(L, writerType, std::move(writer.value));
    return 1;
}

template<auto Method>
int writeBytes(lua_State* L)
{
    const auto& writer = checkObject<ZipWriter::Ptr>(L, 1, writerType);
    const auto name = checkString(L, 2);
    const auto bytes = checkString(L, 3);
    const auto options = entryWriteOptions(L, 4);
    return pushStatus(L, ((*writer).*Method)(name, copyBytes(bytes), options));
}

int addFile(lua_State* L)
{
    const auto& writer = checkObject<ZipWriter::Ptr>(L, 1, writerType);
    const auto name = checkString(L, 2);
    const auto path = checkString(L, 3);
    return pushStatus(L, writer->addFile(name, path, entryWriteOptions(L, 4)));
}

template<auto Method>
int writeName(lua_State* L)
{
    const auto& writer = checkObject<ZipWriter::Ptr>(L, 1, writerType);
    return pushStatus(L, ((*writer).*Method)(checkString(L, 2)));
}

template<auto Method>
int writeNames(lua_State* L)
{
    const auto& writer = checkObject<ZipWriter::Ptr>(L, 1, writerType);
    return pushStatus(L, ((*writer).*Method)(checkString(L, 2), checkString(L, 3)));
}

int setEntryOptions(lua_State* L)
{
    const auto& writer = checkObject<ZipWriter::Ptr>(L, 1, writerType);
    const auto name = checkString(L, 2);
    return pushStatus(L, writer->setEntryOptions(name, entryWriteOptions(L, 3)));
}

int commit(lua_State* L)
{
    return pushStatus(L, checkObject<ZipWriter::Ptr>(L, 1, writerType)->commit());
}

int discard(lua_State* L)
{
    checkObject<ZipWriter::Ptr>(L, 1, writerType)->discard();
    return 0;
}

template<class T>
void registerObject(lua_State* L, const char* name, const luaL_Reg* methods = nullptr)
{
    luaL_newmetatable(L, name);
    lua_pushcfunction(L, destroyObject<T>);
    lua_setfield(L, -2, "__gc");
    lua_pushstring(L, name);
    lua_setfield(L, -2, "__metatable");
    if (methods)
    {
        lua_newtable(L);
        luaL_register(L, nullptr, methods);
        lua_setfield(L, -2, "__index");
    }
    lua_pop(L, 1);
}
}

void register_cc_zip_manual(lua_State* L)
{
    registerObject<EntryId>(L, entryIdType);
    const luaL_Reg readerMethods[] = {
        {"entries", entries}, {"find", find}, {"readEntry", readEntry}, {"verify", verify},
        {nullptr, nullptr}
    };
    registerObject<ZipReader::Ptr>(L, readerType, readerMethods);
    const luaL_Reg writerMethods[] = {
        {"add", writeBytes<&ZipWriter::add>}, {"replace", writeBytes<&ZipWriter::replace>},
        {"addFile", addFile}, {"addDirectory", writeName<&ZipWriter::addDirectory>},
        {"remove", writeName<&ZipWriter::remove>}, {"rename", writeNames<&ZipWriter::rename>},
        {"setArchiveComment", writeName<&ZipWriter::setArchiveComment>},
        {"setEntryComment", writeNames<&ZipWriter::setEntryComment>}, {"setEntryOptions", setEntryOptions},
        {"commit", commit}, {"discard", discard}, {nullptr, nullptr}
    };
    registerObject<ZipWriter::Ptr>(L, writerType, writerMethods);

    lua_getglobal(L, "cc");
    lua_newtable(L);
    const luaL_Reg reader[] = {
        {"openFile", openFile}, {"openBuffer", openBuffer}, {"capabilities", capabilities}, {nullptr, nullptr}
    };
    luaL_register(L, nullptr, reader);
    lua_setfield(L, -2, "ZipReader");
    lua_newtable(L);
    lua_pushcfunction(L, begin);
    lua_setfield(L, -2, "begin");
    lua_createtable(L, 0, 3);
    setNumber(L, "CreateNew", static_cast<int>(WriteIntent::CreateNew));
    setNumber(L, "Replace", static_cast<int>(WriteIntent::Replace));
    setNumber(L, "UpdateExisting", static_cast<int>(WriteIntent::UpdateExisting));
    lua_setfield(L, -2, "WriteIntent");
    lua_createtable(L, 0, 5);
    setNumber(L, "Store", static_cast<int>(Compression::Store));
    setNumber(L, "Deflate", static_cast<int>(Compression::Deflate));
    setNumber(L, "Bzip2", static_cast<int>(Compression::Bzip2));
    setNumber(L, "Xz", static_cast<int>(Compression::Xz));
    setNumber(L, "Zstd", static_cast<int>(Compression::Zstd));
    lua_setfield(L, -2, "Compression");
    lua_createtable(L, 0, 5);
    setNumber(L, "None", static_cast<int>(Encryption::None));
    setNumber(L, "Traditional", static_cast<int>(Encryption::Traditional));
    setNumber(L, "Aes128", static_cast<int>(Encryption::Aes128));
    setNumber(L, "Aes192", static_cast<int>(Encryption::Aes192));
    setNumber(L, "Aes256", static_cast<int>(Encryption::Aes256));
    lua_setfield(L, -2, "Encryption");
    lua_setfield(L, -2, "ZipWriter");
    lua_pop(L, 1);
}
