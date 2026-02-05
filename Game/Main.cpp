#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Font/ConsoleSetUp.h"

using namespace Wanted;

void ConsoleSetUp();

int main()
{
	Engine engine;
	engine.SetNewLevel(new GameLevel());
	engine.Run();
}