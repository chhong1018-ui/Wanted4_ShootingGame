#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();
	~Player();


private:
	virtual void Tick(float deltaTime) override;

	// 오른쪽으로 이동하는 함수.
	void MoveRight();

	// 왼쪽으로 이동하는 함수.
	void MoveLeft();

private:

};
