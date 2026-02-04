#include "GameLevel.h"
#include "Actor/Player.h"

GameLevel::GameLevel()
{
	AddNewActor(new Player());
}
GameLevel::~GameLevel()
{
}
