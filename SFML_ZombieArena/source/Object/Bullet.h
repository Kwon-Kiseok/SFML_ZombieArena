#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Zombie;
class Bullet
{
private:
	// �Ѿ� �ӵ�
	float speed = 500.f;
	float h;
	float v;
	Vector2f direction;
	Vector2f displacement;

	//
	const float DEFAULT_SPEED = 1000.f;
	const float DEFAULT_DISTANCE = 1500.f;
	RectangleShape shape;
	bool isActive;
	float distance;

	// �Ѿ� ��������Ʈ
	Sprite sprite;
	// �Ѿ� �ؽ��� ���� �̸�
	std::string textureFileName;
	// �Ѿ� ������
	Vector2f position;
	// �¾Ҵ���? �� ���Ŀ�
	bool isHitted;
public:
	Bullet();
	Bullet(float x, float y);
	// �Ѿ��� ������
	// �Ѿ��� ���ŵ�

	void SetActive(bool active);
	bool IsActive();
	void Shoot(Vector2f pos, Vector2f dir);
	void Stop();
	RectangleShape GetShape();
	void update(float dt);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	// �Ѿ��� ���ư�(�̵�)
	// ������Ʈ
	void Update(float dt, IntRect arena);
	// �Ѿ� �ǰ� üũ
	bool IsHitted();

	Sprite GetSprite() const;
	void SetPosition(Vector2f& position);
	Vector2f GetPosition() const;
	void SetRotation(float rotation);
};

