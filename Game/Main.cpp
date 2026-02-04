#include <iostream>
#include "Engine/Engine.h"

using namespace Wanted;

int main()
{
	Engine engine;
	engine.SetNewLevel(new GameLevel());
	engine.Run();
}