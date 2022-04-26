#include "Bullet.h"
#include "..\Utils\InputManager.h"
#include "..\Utils\TextureHolder.h"
#include "..\Utils\Utils.h"
#include "..\Object\Crosshair.h"

#include <iostream>

Bullet::Bullet(float x, float y)
	:textureFileName("graphics/bullet.png"), isHitted(false)
{
	position.x = x;
	position.y = y;
	std::cout << "x: " << position.x << "y: " << position.y << std::endl;

	// ������ �� �������
	h = Crosshair::GetMapPixelCoords().x - position.x;
	v = Crosshair::GetMapPixelCoords().y - position.y;
	Vector2f dir(h, v);
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	dir /= length;
	direction = dir;

	// ȸ��
	Vector2i mousePos = static_cast<Vector2i>(Crosshair::GetMapPixelCoords());
	Vector2i mouseDir;

	mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;

	// ���հ�
	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = (radian * 180.f) / 3.141592f;
	sprite.setRotation(degree);

	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	//Utils::SetOrigin(sprite, PIVOTS::CENTER);
	// �ϴ��� �ѳ����� �������� 15��ŭ ������ ����
	sprite.setOrigin(-15.f, sprite.getLocalBounds().height * 0.5f);
}

void Bullet::Update(float dt, IntRect arena)
{
	displacement = direction * speed * dt;
	position += displacement;
	sprite.setPosition(position);
	// ������ ������ ������ �ǰ������� ���̴� �Ϳ� ���� �ʰ� ��
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
