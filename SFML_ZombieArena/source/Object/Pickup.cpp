#include "Pickup.h"
#include "..\Utils\TextureHolder.h"
#include "..\Utils\Utils.h"

#include <iostream>

Pickup::Pickup(PICKUP_TYPES type)
	: type(type), timer(START_WAIT_TIME), value(0), spawned(false)
{
	std::string textureID;

	switch (this->type)
	{
	case PICKUP_TYPES::Ammo:
		textureID = "graphics/ammo_pickup.png";
		value = AMMO_START_VALUE;
		break;
	case PICKUP_TYPES::Healpack:
		textureID = "graphics/health_pickup.png";
		value = HEALTH_START_VALUE;
		break;
	default:
		break;
	}

	sprite.setTexture(TextureHolder::GetTexture(textureID));
	Utils::SetOrigin(sprite, PIVOTS::CENTER);

	Spawn(false);
}

void Pickup::Update(float dt)
{
	timer -= dt;

	// 설정해둔 생존 시간이 다된 경우
	if (timer < 0.f)
	{
		Spawn(!spawned);
	}
}

void Pickup::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned)
	{
		timer = START_SECONDS_FOR_LIVE;
		int x = Utils::RandomRange(arena.left, arena.left + arena.width);
		int y = Utils::RandomRange(arena.top, arena.top + arena.height);
		
		
		sprite.setPosition(Vector2f(x, y));
	}
	else
	{
		timer = START_WAIT_TIME;
	}
}

int Pickup::GotIt()
{
	return value;
}

void Pickup::SetArena(IntRect rect)
{
	arena = rect;
}

bool Pickup::IsSpawned()
{
	return spawned;
}

Sprite Pickup::GetSprite()
{
	return sprite;
}

FloatRect Pickup::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

PICKUP_TYPES Pickup::GetType()
{
	return type;
}
