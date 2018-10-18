#pragma once
#include <iostream>
#include <string>

#include "lua.hpp"
#include "luawrapper.hpp"
#include "luawrapperutil.hpp"

#include "Engine.h"

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void LoadScripts();

	static int OpenObject(lua_State*);

private:
};

