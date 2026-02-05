#include "Actor/Target.h"
#include "Actor/Ground.h"
#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/Wall.h"
#include "Util/Util.h"

#include <iostream>

GameLevel::GameLevel()
{
	// Player 액터 추가.
	AddNewActor(new Player());

	LoadMap("Map.txt");
}

GameLevel::~GameLevel()
{
}

void GameLevel::Draw()
{
	super::Draw();

	// 게임 클리어인 경우. 메시지 출력.
	if (isGameClear)
	{
		// 콘솔 위치/색상 설정.
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// 게임 클리어 메시지 출력.
		std::cout << "Game Clear!";
	}
}

void GameLevel::LoadMap(const char* filename)
{
	// 파일 로드.
	// 최종 파일 경로 만들기
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외 처리
	if (!file)
	{
		std::cerr << "Failed to open map file...\n";

		__debugbreak();
	}
	// 맵읽기
	// 맵 크기 파악: file position 포인터를 파일의 끝으로 이동.
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기.
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];

	// 데이터 읽기.
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석해서 출력.
	// 인덱스를 사용해 한 문자씩 읽기.
	int index = 0;

	// 객체를 생성할 위치 값.
	Wanted::Vector2 position;

	while (true)
	{
		// 종료 조건
		if (index >= fileSize)
		{
			break;
		}
		
		// 캐릭터 읽기
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리.
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}

		/*
		■: 벽
		□: 바닥
		●: 플레이어(Green), 박스(Blue), Enemy(Red)
		*/
		switch (mapCharacter)
		{
		case '#':
			//std::cout << "#";
			AddNewActor(new Wall(position));
			break;
		case '.':
			//std::cout << " ";
			AddNewActor(new Ground(position));
			break;
		case 't':
			//std::cout << " ";
			AddNewActor(new Target(position));
			break;
		}

		// x 좌표 증가 처리.
		++position.x;
	}
	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}


bool GameLevel::CanMove(const Wanted::Vector2& playerPosition, const Wanted::Vector2& newPosition)
{
	for (Actor* const actor : actors)
	{
		if (actor->GetPosition() == newPosition)
		{
			// #2: 벽이면 이동 불가.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}

			if (actor->IsTypeOf<Target>())
			{
				// 게임 점수 확인.
				isGameClear = CheckGameClear();

				// 플레이어 이동 가능.
				return true;
			}
		}
	}
	return true;
}

bool GameLevel::CheckGameClear()
{
	// 타겟 위에 있는 박스의 수 검증.
	int currentScore = 0;

	// 배열에 박스 및 타겟 저장.
	std::vector<Actor*> players;
	std::vector<Actor*> targets;

	// 레벨에 배치된 배열 순회하면서 두 액터 필터링.
	for (Actor* const actor : actors)
	{
		// 박스인 경우 박스 배열에 추가.
		if (actor->IsTypeOf<Player>())
		{
			players.emplace_back(actor);
			continue;
		}

		// 타겟의 경우 타겟 배열에 추가.
		if (actor->IsTypeOf<Target>())
		{
			targets.emplace_back(actor);
		}
	}

	// 점수 확인 (플레이어의 위치가 타겟의 위치와 같은지 비교).
	for (Actor* const player : players)
	{
		for (Actor* const target : targets)
		{
			// 두 액터의 위치가 같으면 점수 +.
			if (player->GetPosition() == target->GetPosition())
			{
				currentScore += 1;
			}
		}
	}

	// 목표 점수에 도달했는지 확인.
	return currentScore == targetScore;
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 매 프레임 게임 클리어 여부 확인
	isGameClear = CheckGameClear();
}