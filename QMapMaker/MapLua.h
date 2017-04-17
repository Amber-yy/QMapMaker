#pragma once
#include "LuaOperator.h"

class MapLua :public LuaOperator
{
public:
	static int addObject(lua_State *);
	static int setMap(lua_State *);
	static int setAllTrigger(lua_State *);
};

