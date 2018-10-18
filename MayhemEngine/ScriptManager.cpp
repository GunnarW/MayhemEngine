#include "ScriptManager.h"



ScriptManager::ScriptManager()
{
}


ScriptManager::~ScriptManager()
{
}

void ScriptManager::LoadScripts()
{
	lua_State* state = luaL_newstate();
	luaL_openlibs(state);

}

int ScriptManager::OpenObject(lua_State* state)
{
	//luaW_register<Character>(state, "Character", Character_table, Character_metatable, Character_new);
	return 1;
}
