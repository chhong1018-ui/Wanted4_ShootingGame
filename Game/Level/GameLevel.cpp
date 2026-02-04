#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerBullet.h"
#include "Actor/EnemyBullet.h"
#include "Actor/EnemySpawner.h"

GameLevel::GameLevel()
{
	// Player 액터 추가.
	AddNewActor(new Player());

	// 적 생성기 추가.
	AddNewActor(new EnemySpawner());
}
GameLevel::~GameLevel()
{
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 충돌 판정 처리.
	ProcessCollisionPlayerBulletAndEnemy();
	ProcessCollisionPlayerEnemyAndBullet();
}

void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// 플레이어 탄약과 적 액터 필터링.
	std::vector<Actor*> bullets;
	std::vector<Enemy*> enemies;

	// 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<PlayerBullet>())
		{
			bullets.emplace_back(actor);
			continue;
		}
		if (actor->IsTypeOf<Enemy>())
		{
			enemies.emplace_back(actor->As<Enemy>());
			continue;
		}
	}

	// 판정 안해도 되는지 확인.
	if (bullets.size() == 0 || enemies.size() == 0)
	{
		return;
	}

	// 충돌 판정.
	for (Actor* const bullet : bullets)
	{
		for (Enemy* const enemy : enemies)
		{
			// AABB 겹침 판정.
			if (bullet->TestIntersect(enemy))
			{
				enemy->OnDamaged();
				bullet->Destroy();

				// Todo: 점수 추가.
				continue;
			}
		}
	}
}

void GameLevel::ProcessCollisionPlayerEnemyAndBullet()
{
	// 액터 필터링을 위한 변수.
	Player* player = nullptr;
	std::vector<Actor*> bullets;

	// 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>();
			continue;
		}

		if (actor->IsTypeOf<EnemyBullet>())
		{
			bullets.emplace_back(actor);
		}
	}

	// 판정 처리 안해도 되는지 확인.
	if (bullets.size() == 0 || !player)
	{
		return;
	}

	// 충돌 판정.
	for (Actor* const bullet : bullets)
	{
		if (bullet->TestIntersect(player))
		{
			player->Destroy();
			bullet->Destroy();
			break;
		}
	}
}
