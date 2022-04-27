#include "player.h"
#include "..\Utils\Utils.h"
#include "..\Utils\InputManager.h"
#include "..\Utils\TextureHolder.h"
#include "..\Object\Bullet.h"
#include "..\Object\Pickup.h"
#include "..\Enemy\Zombie.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Player::Player()
	: maxSpeed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS)//, velocity(0), accel(START_ACCEL)
	, textureFileName("graphics/player.png"), bullet(nullptr)
{
	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	Utils::SetOrigin(sprite, PIVOTS::CENTER);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
	{
		unUseBullets.push_back(new Bullet());
	}
	distanceToMuzzle = 45.f;
}

Player::~Player()
{
	for (auto bullet : unUseBullets)
	{
		delete bullet;
	}
	unUseBullets.clear();

	for (auto bullet : useBullets)
	{
		delete bullet;
	}
	useBullets.clear();
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = this->arena.width * 0.5f;
	position.y = this->arena.height * 0.5f;
}

void Player::Move(IntRect arena, Vector2f displacement)
{
	position += displacement;
	// boundary
	if (position.x < arena.left + 50.f || position.x > arena.left + arena.width - 50.f)
	{
		position.x -= displacement.x;
	}
	if (position.y < arena.top + 50.f || position.y > arena.top + arena.height - 50.f)
	{
		position.y -= displacement.y;
	}
}

bool Player::OnHitted(Time timeHit)
{
	// 0.2초 동안은 immune
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
	{
		std::cout << timeHit.asSeconds() << std::endl;
		lastHit = timeHit;
		health -= 10;
		return true;
	}
	return false;
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGlobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

void Player::SetDirection(Vector2f dir)
{
}

void Player::Update(float dt)
{
	// 사용자 입력
	float h = InputManager::GetAxis(Axis::Horizontal);
	float v = InputManager::GetAxis(Axis::Vertical);
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	// 입력이 있는 경우
	if (length > 1)
	{
		dir /= length;
		//lastDir = dir;
		//// v = at
		//// velocity = at
		//velocity += accel * dt;
		//if (velocity > maxSpeed)
		//	velocity = maxSpeed;
	}
	/*else
	{
		velocity -= accel * dt;
		if (velocity < 0.f)
			velocity = 0.f;
	}*/
	Vector2f displacement = dir * maxSpeed * dt;
	Move(arena, displacement);
	sprite.setPosition(position);
	//position += lastDir * velocity * dt; // d = vt;
	//sprite.setPosition(position);

	// 회전
	Vector2i mousePos = InputManager::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;
	//mouseDir.x = mousePos.x - position.x;
	//mouseDir.y = mousePos.y - position.y;

	// 사잇각
	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = (radian * 180.f) / 3.141592f;
	sprite.setRotation(degree);

	// 총알 업데이트
	if (InputManager::GetLeftButtonDown(Mouse::Left) 
		|| InputManager::GetLeftButton(Mouse::Left))
	{
		//Fire();
		Shoot(Vector2f(mouseDir.x, mouseDir.y));
	}

	auto it = useBullets.begin();
	while (it != useBullets.end())
	{
		Bullet* bullet = *it;
		bullet->update(dt);

		if (!bullet->IsActive())
		{
			it = useBullets.erase(it);
			unUseBullets.push_back(bullet);
		}
		else
		{
			++it;
		}
	}

	/*if (nullptr != bullet)
	{
		bullet->Update(dt, arena);
		if (bullet->IsHitted())
		{
			delete bullet;
			bullet = nullptr;
		}
	}*/
}

bool Player::UpdateCollision(const std::list<Pickup*>& items)
{
	bool isCollied = false;
	FloatRect bounds = sprite.getGlobalBounds();

	for (auto item : items)
	{
		if (bounds.intersects(item->GetGlobalBounds()))
		{
			item->GotIt();
		}
		isCollied = true;
	}

	return isCollied;
}

bool Player::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	bool isCollied = false;

	for (auto bullet : useBullets)
	{
		if (bullet->UpdateCollision(zombies))
		{
			isCollied = true;
		}
	}

	return isCollied;
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets)
	{
		window.draw(bullet->GetShape());
	}
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}

	if (health < 0)
	{
		health = 0;
	}
}

void Player::UpgradeSpeed()
{
	maxSpeed += START_SPEED * 0.2;
}

void Player::UpgradeMaxHealth()
{
	maxHealth += START_HEALTH * 0.2;
}

void Player::Fire()
{
	// 일단은 한발만 
	if (nullptr != bullet)
		return;
	// 리스트나 벡터로 관리해줘서 장탄수 관리?
	bullet = new Bullet(position.x, position.y);
}

Bullet* Player::GetBullet() const
{
	return bullet;
}

void Player::Shoot(Vector2f dir)
{
	dir = Utils::Normalize(dir);
	Vector2f spawnPos = position + dir * distanceToMuzzle;

	if (unUseBullets.empty())
	{
		for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
		{
			unUseBullets.push_back(new Bullet());
		}
	}

	Bullet* bullet = unUseBullets.front();
	unUseBullets.pop_front();

	useBullets.push_back(bullet);
	bullet->Shoot(spawnPos, dir);
}
