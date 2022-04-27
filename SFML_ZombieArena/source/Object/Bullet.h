#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Zombie;
class Bullet
{
private:
	// 총알 속도
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

	// 총알 스프라이트
	Sprite sprite;
	// 총알 텍스쳐 파일 이름
	std::string textureFileName;
	// 총알 포지션
	Vector2f position;
	// 맞았는지? 는 추후에
	bool isHitted;
public:
	Bullet();
	Bullet(float x, float y);
	// 총알이 생성됨
	// 총알이 제거됨

	void SetActive(bool active);
	bool IsActive();
	void Shoot(Vector2f pos, Vector2f dir);
	void Stop();
	RectangleShape GetShape();
	void update(float dt);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	// 총알이 날아감(이동)
	// 업데이트
	void Update(float dt, IntRect arena);
	// 총알 피격 체크
	bool IsHitted();

	Sprite GetSprite() const;
	void SetPosition(Vector2f& position);
	Vector2f GetPosition() const;
	void SetRotation(float rotation);
};

