#include <iostream>
//https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/

#ifdef __cplusplus
extern "C"
{
#endif

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#ifdef __cplusplus
};
#endif


class LuaContext
{

    lua_State *L;

public:
    LuaContext();
    virtual ~LuaContext();

    bool  AddScript(const char* file);

    template<typename T> inline __attribute__((unused)) T get(__attribute__((unused))const std::string& val) {}

    template<typename T> inline __attribute__((unused)) T lua_get(__attribute__((unused))const std::string& val) {}

    template<typename T> inline __attribute__((unused)) T lua_getdefault(__attribute__((unused))const std::string& val) {}

    template<typename T> inline __attribute__((unused)) T lua_gettostack(__attribute__((unused))const std::string& val) {}

};

LuaContext::LuaContext()
{
    L = luaL_newstate();
}

LuaContext::~LuaContext()
{
    if (L)
        lua_close(L);
    L = nullptr;
}


bool  LuaContext::AddScript(const char* file)
{
    bool isOk = false;
    if (luaL_loadfile(L, file) || lua_pcall(L, 0, 0, 0))
    {
        printf("File (%s) not loaded!!!\r\n", file);
    }
    else
        isOk = true;
    return  isOk;
}

// specialization for different ret tupes

template <>
inline std::string LuaContext::lua_get(const std::string& str)
{
    return "null";
}

template <>
inline bool LuaContext::lua_get(const std::string& str)
{
    return false;
}


int main(int argc, char** argv)
{
    (void)argc; (void) argv;


    return 0;
}
