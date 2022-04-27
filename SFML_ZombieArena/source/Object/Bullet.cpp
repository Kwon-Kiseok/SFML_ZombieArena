#include "Bullet.h"
#include "..\Utils\InputManager.h"
#include "..\Utils\TextureHolder.h"
#include "..\Utils\Utils.h"
#include "..\Object\Crosshair.h"
#include "..\Enemy\Zombie.h"

#include <iostream>

Bullet::Bullet()
{
	speed = DEFAULT_SPEED;
	isActive = false;
	shape.setSize(Vector2f(10, 10));
	Utils::SetOrigin(shape, PIVOTS::CENTER);
}

Bullet::Bullet(float x, float y)
	:textureFileName("graphics/bullet.png"), isHitted(false)
{
	position.x = x;
	position.y = y;
	std::cout << "x: " << position.x << "y: " << position.y << std::endl;

	// 생성될 때 방향결정
	h = Crosshair::GetMapPixelCoords().x - position.x;
	v = Crosshair::GetMapPixelCoords().y - position.y;
	Vector2f dir(h, v);
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	dir /= length;
	direction = dir;

	// 회전
	Vector2i mousePos = static_cast<Vector2i>(Crosshair::GetMapPixelCoords());
	Vector2i mouseDir;

	mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;

	// 사잇각
	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = (radian * 180.f) / 3.141592f;
	sprite.setRotation(degree);

	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	//Utils::SetOrigin(sprite, PIVOTS::CENTER);
	// 일단은 총끝에서 나오도록 15만큼 오리진 수정
	sprite.setOrigin(-15.f, sprite.getLocalBounds().height * 0.5f);
}

void Bullet::SetActive(bool active)
{
	isActive = active;
}

bool Bullet::IsActive()
{
	return isActive;
}

void Bullet::Shoot(Vector2f pos, Vector2f dir)
{
	SetActive(true);

	distance = 0.f;
	position = pos;

	// clear
	//std::cout << position.x << ", " << position.y << std::endl;

	shape.setPosition(position);
	direction = Utils::Normalize(dir); // normalized
	float degree = Utils::GetAngle(position, position + direction);
	shape.setRotation(degree);
}

void Bullet::Stop()
{
	SetActive(false);
}

RectangleShape Bullet::GetShape()
{
	return shape;
}

void Bullet::update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;	// scalar

	// 
	//std::cout << distance << std::endl;

	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

bool Bullet::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	FloatRect bounds = shape.getGlobalBounds();

	for (auto zombie : zombies)
	{
		if (zombie->IsAlive())
		{
			if (bounds.intersects(zombie->GetGlobalBound()))
			{
				zombie->OnHitted();
				Stop();

				return true;
			}
		}
	}
	return false;
}

void Bullet::Update(float dt, IntRect arena)
{
	displacement = direction * speed * dt;
	position += displacement;
	sprite.setPosition(position);
	// 수정된 오리진 때문에 피격판정이 보이는 것에 비해 늦게 됨
	if (position.x < arena.left + 50.f || position.x > arena.left + arena.width - 50.f
		|| position.y < arena.top + 50.f || position.y > arena.top + arena.height - 50.f)
	{
		// delete
		//std::cout << "Hitted: " << position.x << ", " << position.y << std::endl;
		isHitted = true;
	}
}

bool Bullet::IsHitted()
{
	return isHitted;
}

Sprite Bullet::GetSprite() const
{
	return sprite;
}

void Bullet::SetPosition(Vector2f& position)
{
	this->position = position;
}

Vector2f Bullet::GetPosition() const
{
	return position;
}

void Bullet::SetRotation(float rotation)
{
	sprite.setRotation(rotation);
}
