#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

#include "Interface/ICanPlayerMove.h"

Player::Player()
	: super("P", Vector2::Zero, Color::Green)
{
	// 생성 위치 설정.
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = Engine::Get().GetHeight() - 2;
	SetPosition(Vector2(xPosition, yPosition));

	sortingOrder = 10;
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 종료 처리.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 게임 종료.
		QuitGame();
	}

	// 경과 시간 업데이트.
	//elapsedTime += deltaTime;
	timer.Tick(deltaTime);

	// 좌우 방향키 입력 처리.
	if (Input::Get().GetKey(VK_LEFT))
	{
		MoveLeft();
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		MoveRight();
	}

	// 위아래 방향키 입력 처리.
	if (Input::Get().GetKey(VK_UP))
	{
		MoveUp();
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
		MoveDown();
	}

	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		Fire();
	}

}

void Player::MoveRight()
{
	Vector2 currentPosition = GetPosition();
	Vector2 nextPosition = currentPosition;
	// 오른쪽 이동 처리
	nextPosition.x += 1;
	
	// 좌표 검사.
	// "<-=A=->"
	if (nextPosition.x + width > Engine::Get().GetWidth())
	{
		nextPosition.x -= 1;
	}

	// 변경된 위치 적용
	SetPosition(nextPosition);
}

void Player::MoveLeft()
{
	Vector2 position = GetPosition();
	// 왼쪽 이동 처리
	position.x -= 1;

	// 좌표 검사.
	if (position.x < 0)
	{
		position.x = 0;
	}

	// 변경된 위치 적용
	SetPosition(position);
}

void Player::MoveUp()
{
	Vector2 position = GetPosition();
	// 윗쪽 이동 처리
	position.y -= 1;

	// 좌표 검사.
	// "<-=A=->"
	if (position.y + height > Engine::Get().GetHeight())
	{
		position.y += 1;
	}

	// 변경된 위치 적용
	SetPosition(position);
}

void Player::MoveDown()
{
	Vector2 position = GetPosition();
	// 아랫쪽 이동 처리
	position.y += 1;

	// 좌표 검사.
	if (position.y < 0)
	{
		position.y = 0;
	}

	// 변경된 위치 적용
	SetPosition(position);
}
void Player::Fire()
{
	// 경과 시간 초기화.
	//elapsedTime = 0.0f;
	timer.Reset();

	// 위치 설정.
	Vector2 bulletPosition(position.x + (width / 2), position.y);

}

bool Player::CanShoot() const
{
	// 경과 시간 확인.
	// 발사 간격보다 더 많이 흘렀는지.
	return timer.IsTimeOut();
}
