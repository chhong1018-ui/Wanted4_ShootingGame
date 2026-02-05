#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

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

	// 윗쪽으로 이동하는 함수.
	void MoveUp();

	// 아랫쪽으로 이동하는 함수..
	void MoveDown();

	// 탄약 발사 함수.
	void Fire();

	// 발사 가능 여부 확인 함수.
	bool CanShoot() const;

private:

	Timer timer;

	// 연사 시간 간격.
	float fireInterval = 0.2f;
};
