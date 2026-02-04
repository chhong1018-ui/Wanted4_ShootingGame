#include "Player.h"
#include "Core/Input.h"
#include "Actor/PlayerBullet.h"
#include "Engine/Engine.h"
#include "Level/Level.h"

Player::Player()
	: super("<=A=>", Vector2::Zero, Color::Green)
{
	// 생성 위치 설정.
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = Engine::Get().GetHeight() - 2;
	SetPosition(Vector2(xPosition, yPosition));
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

	// 좌우 방향키 입력 처리.
	if (Input::Get().GetKey(VK_LEFT))
	{
		MoveLeft();
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		MoveRight();
	}

	// 스페이스키를 활용해 탄약 발사.
	if (Input::Get().GetKey(VK_SPACE))
	{
		Fire();
	}
}

void Player::MoveRight()
{
	Vector2 position = GetPosition();
	// 오른쪽 이동 처리
	position.x += 1;

	// 좌표 검사.
	// "<-=A=->"
	if (position.x + width > Engine::Get().GetWidth())
	{
		position.x -= 1;
	}

	// 변경된 위치 적용
	SetPosition(position);
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

void Player::Fire()
{
	// 위치 설정.
	Vector2 bulletPosition(position.x + (width / 2), position.y);
	
	// 액터 생성.
	GetOwner()->AddNewActor(new PlayerBullet(bulletPosition));
}
