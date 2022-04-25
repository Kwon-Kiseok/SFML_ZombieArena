#include "player.h"
#include "..\Utils\Utils.h"
#include "..\Utils\InputManager.h"
#include <cmath>

Player::Player()
	: speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS)
{
	texture.loadFromFile("graphics/player.png");
	sprite.setTexture(texture);

	Utils::SetOrigin(sprite, PIVOTS::CENTER);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = this->arena.width * 0.5f;
	position.y = this->arena.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)
{
	// 0.2초 동안은 immune
	if (timeHit.asMicroseconds() - lastHit.asMicroseconds() > immuneMs)
	{
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
	direction.x = InputManager::GetAxis(Axis::Horizontal);
	direction.y = InputManager::GetAxis(Axis::Vertical);

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if(length != 0)
		direction /= length;

	position += direction * speed * dt;
	sprite.setPosition(position);

	// 회전
	Vector2i mousePos = InputManager::GetMousePosition();
	Vector2i mouseDir;
	//mouseDir.x = mousePos.x - resolution.x * 0.5f;
	//mouseDir.y = mousePos.y - resolution.y * 0.5f;
	mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;

	// 사잇각
	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = (radian * 180.f) / 3.141592f;
	sprite.setRotation(degree);

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
	speed += START_SPEED * 0.2;
}

void Player::UpgradeMaxHealth()
{
	maxHealth += START_HEALTH * 0.2;
}
