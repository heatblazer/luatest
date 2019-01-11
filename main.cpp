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

    int m_level;
    lua_State *L;

public:
    LuaContext();
    virtual ~LuaContext();

    bool  AddScript(const char* file);

    template<typename T> inline T get(const std::string& val)
    {
        T result;

        if (!L)
        {
            printf("Script is not loaded (%s)\r\n", val.c_str());
            return  lua_getdefault<T>();
        }

        if (lua_gettostack(val))
        {
            result = lua_get<T>(val);
        }
        else
        {
            result = lua_getdefault<T>();
        }


        lua_pop(L, m_level + 1);
        return  result;
    }

    template<typename T> inline __attribute__((unused)) T lua_get(__attribute__((unused))const std::string& val) {}

    template<typename T> inline __attribute__((unused)) T lua_getdefault(__attribute__((unused))const std::string& val) {}

    bool lua_gettostack(const std::string& val);

};

LuaContext::LuaContext() : m_level{0}
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

bool LuaContext::lua_gettostack(const std::string& str)
{

    m_level = 0;
    std::string var = "";
    for(unsigned int i =0; i < str.size(); ++i)
    {
        if (str.at(i) == '.')
        {
            if (m_level == 0)
                lua_getglobal(L, str.c_str());
            else
                lua_getfield(L, -1, str.c_str());

            if (lua_isnil(L, -1))
                return  false;
            else
            {
                var = "";
                m_level++;
            }
        }
        else
        {
            var += str.at(i);
        }
    }
    if (m_level == 0)
        lua_getglobal(L, str.c_str());
    else
        lua_getfield(L, -1, str.c_str());

    if (lua_isnil(L, -1))
        return  false;

    return true;
}



int main(int argc, char** argv)
{
    (void)argc; (void) argv;


    return 0;
}
