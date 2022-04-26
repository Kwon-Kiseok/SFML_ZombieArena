#include "Zombie.h"
#include "..\Utils\TextureHolder.h"
#include "..\Utils\Utils.h"

std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isInitInfo = false;

Zombie::Zombie()
	: resoultion()
{
	if (!isInitInfo)
	{
		zombieInfo.resize(static_cast<int>(ZombieTypes::COUNT));

		{
			auto& info = zombieInfo[static_cast<int>(ZombieTypes::BLOATER)];
			info.type = ZombieTypes::BLOATER;
			info.textureFileName = "graphics/bloater.png";
			info.speed = 40.f;
			info.health = 5;
		}
		{
			auto& info = zombieInfo[static_cast<int>(ZombieTypes::CHASER)];
			info.type = ZombieTypes::CHASER;
			info.textureFileName = "graphics/chaser.png";
			info.speed = 70.f;
			info.health = 1;
		}
		{
			auto& info = zombieInfo[static_cast<int>(ZombieTypes::CRAWLER)];
			info.type = ZombieTypes::CRAWLER;
			info.textureFileName = "graphics/crawler.png";
			info.speed = 20.f;
			info.health = 3;
		}

		isInitInfo = true;
	}
}

bool Zombie::OnHitted()
{
	return false;
}

bool Zombie::IsAlive()
{
	return alive;
}

void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	auto& info = zombieInfo[static_cast<int>(type)];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed;
	health = info.health;

	position.x = x;
	position.y = y;

	Utils::SetOrigin(sprite, PIVOTS::CENTER);
	sprite.setPosition(position);
}

void Zombie::Update(float dt, Vector2f playerPos)
{
	//
	// �߰� ���� ���ϱ�
	float h = playerPos.x - position.x;
	float v = playerPos.y - position.y;
	Vector2f dir(h, v);
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	dir /= length;

	position += dir * speed * dt;
	sprite.setPosition(position);

	// ȸ��
	float radian = atan2(dir.y, dir.x);
	float degree = (radian * 180.f) / 3.141592f;
	sprite.setRotation(degree);
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}