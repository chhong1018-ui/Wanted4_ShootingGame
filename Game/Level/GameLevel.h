#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

using namespace Wanted;

class GameLevel : public Wanted::Level, public ICanPlayerMove
{

	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	// 이벤트 함수 오버라이드.
	virtual void Draw() override;
private:
	void LoadMap(const char* filename);

	virtual bool CanMove(
		const Wanted::Vector2& playerPosition,
		const Wanted::Vector2& newPosition) override;

	//게임 클리어 확인 함수.
	bool CheckGameClear();

	virtual void Tick(float deltaTime) override;

private:
	// 획득해야하는 목표 점수.
	int targetScore = 0;

	// 게임 클리어 여부를 알려주는 변수.
	bool isGameClear = false;
};
