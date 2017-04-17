#pragma once

#include <memory>
#include <string>

struct LuaData;
struct lua_State;
struct luaL_Reg;

typedef int(*LuaFunction) (lua_State *L);

class LuaOperator
{
public:
	LuaOperator();
	~LuaOperator();
	void openLib(const char *name, LuaFunction function);
	void openLibs(luaL_Reg *libs);
	void registerFunction(const char *name, LuaFunction function);
	void registerFunctions(luaL_Reg *libs);
	void registerClass(const char *name, const luaL_Reg *functions);
	void openAllLibs();
	void newMetaTable(const char *table);
	void pushValue(int index);
	void setField(int index, const char *key);
	void loadFile(const char *fileName);
	void doFile(const char *fileName);
	void getGlobal(const char *name);
	void pop(int num);
	void setTop(int index);
	void getRow(int index, int n);
	void setRow(int index,int n);
	void getTable(int index);
	void pushUserData(void *ptr,const char *className=nullptr);
	void pushNumber(double num);
	void pushInteger(long long in);
	void pushString(const char *str);
	void *toUserData(int index);
	const char *toString(int index);
	long long length(int index);
	long long toInteger(int index);
	lua_State *getState();
	void protectedCall(int argNum,int resultNum,int autoErrorHandle=0);
protected:
	std::unique_ptr<LuaData> data;
public:
	static LuaOperator *getLua();
protected:
	static std::unique_ptr<LuaOperator> uniqueState;
};

