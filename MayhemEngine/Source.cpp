#include <iostream>
// Mayhem Engine
#include "Engine.h"
#include "MayhemObject.h"

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Setup new engine
	Engine* engine = new Engine();
	engine->Initialize();

	// Run engine
	engine->Run();

	delete engine;
	engine = NULL;

	return 0;
}

