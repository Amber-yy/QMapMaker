#include "LuaOperator.h"

#include <exception>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

struct LuaData
{
	LuaData()
	{
		state= luaL_newstate();
	}
	~LuaData()
	{
		lua_close(state);
	}
	lua_State *state;
};

std::unique_ptr<LuaOperator> LuaOperator::uniqueState;

LuaOperator::LuaOperator():data(std::make_unique<LuaData>())
{

}

LuaOperator::~LuaOperator()
{

}

LuaOperator * LuaOperator::getLua()
{
	if (uniqueState.get() == nullptr)
	{
		uniqueState.swap(std::make_unique<LuaOperator>());
	}

	return uniqueState.get();
}

void LuaOperator::openLib(const char * name, LuaFunction function)
{
	luaL_requiref(data->state, name, function, 1);
}

void LuaOperator::openLibs(luaL_Reg * libs)
{
	for (; libs->func != nullptr; libs++)
	{
		openLib(libs->name,libs->func);
	}
}

void LuaOperator::registerFunction(const char * name, LuaFunction function)
{
	lua_register(data->state,name,function);
}

void LuaOperator::registerFunctions(luaL_Reg * libs)
{
	for (; libs->func != nullptr; libs++)
	{
		registerFunction(libs->name, libs->func);
	}
}

void LuaOperator::registerClass(const char * name,const luaL_Reg * functions)
{
	luaL_newmetatable(data->state, name);
	lua_pushvalue(data->state, -1);
	lua_setfield(data->state, -2, "__index");
	luaL_setfuncs(data->state, functions, 0);
}

void LuaOperator::openAllLibs()
{
	luaL_openlibs(data->state);
}

void LuaOperator::newMetaTable(const char * table)
{
	luaL_newmetatable(data->state, table);
}

void LuaOperator::pushValue(int index)
{
	lua_pushvalue(data->state, index);
}

void LuaOperator::setField(int index, const char * key)
{
	lua_setfield(data->state,index, key);
}

void LuaOperator::loadFile(const char * fileName)
{
	int result=luaL_loadfile(data->state, fileName);
	if (result)
	{
		throw std::exception(lua_tostring(data->state, -1));
	}
}

void LuaOperator::doFile(const char * fileName)
{
	int result=luaL_dofile(data->state,fileName);
	if (result)
	{
		throw std::exception(lua_tostring(data->state, -1));
	}
}

void LuaOperator::getGlobal(const char * name)
{
	lua_getglobal(data->state, name);
}

void LuaOperator::pushUserData(void * ptr,const char *className)
{
	void **value = static_cast<void **>(lua_newuserdata(data->state, sizeof(void *)));
	*value = ptr;

	if (className)
	{
		luaL_getmetatable(data->state, className);
		lua_setmetatable(data->state, -2);
	}
}

void LuaOperator::pushNumber(double num)
{
	lua_pushnumber(data->state, num);
}

void LuaOperator::pushInteger(long long in)
{
	lua_pushinteger(data->state, in);
}

void LuaOperator::pushString(const char * str)
{
	lua_pushstring(data->state, str);
}

void * LuaOperator::toUserData(int index)
{
	return lua_touserdata(data->state, index);
}

const char * LuaOperator::toString(int index)
{
	return lua_tostring(data->state,index);
}

void LuaOperator::pop(int num)
{
	lua_pop(data->state, num);
}

void LuaOperator::setTop(int index)
{
	lua_settop(data->state, index);
}

void LuaOperator::getRow(int index, int n)
{
	lua_rawgeti(data->state, index, n);
}

void LuaOperator::setRow(int index, int n)
{
	lua_rawseti(data->state, index, n);
}

void LuaOperator::getTable(int index)
{
	lua_gettable(data->state, index);
}

long long LuaOperator::length(int index)
{
	return luaL_len(data->state,index);
}

long long LuaOperator::toInteger(int index)
{
	return lua_tointeger(data->state,index);
}

lua_State * LuaOperator::getState()
{
	return data->state;
}

void LuaOperator::protectedCall(int argNum, int resultNum, int autoErrorHandle)
{
	int result=lua_pcall(data->state, argNum, resultNum, autoErrorHandle);
	if (result)
	{
		throw std::exception(lua_tostring(data->state, -1));
	}
}

