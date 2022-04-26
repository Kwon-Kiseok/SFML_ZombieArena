#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Bullet
{
private:
	// �Ѿ� �ӵ�
	float speed = 500.f;
	float h;
	float v;
	Vector2f direction;
	Vector2f displacement;

	// �Ѿ� ��������Ʈ
	Sprite sprite;
	// �Ѿ� �ؽ��� ���� �̸�
	std::string textureFileName;
	// �Ѿ� ������
	Vector2f position;
	// �¾Ҵ���? �� ���Ŀ�
	bool isHitted;
public:
	Bullet(float x, float y);
	// �Ѿ��� ������
	// �Ѿ��� ���ŵ�

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

