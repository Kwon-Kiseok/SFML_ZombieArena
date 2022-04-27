#pragma once
#include "SFML/Graphics.hpp"
#include <list>
using namespace sf;

class Zombie;
class Bullet;
class Pickup;
class Player
{
private:
	const float START_SPEED = 300;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;
	const float START_ACCEL = 110;

	float maxSpeed; // maxSpeed
	//float velocity;
	//float accel;

	Vector2f position;
	
	Sprite sprite;
	std::string textureFileName;
	
	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f lastDir;

	int health;
	int maxHealth;
	float immuneMs;

	Time lastHit;

	Bullet* bullet;
	
	const int BULLET_CACHE_SIZE = 1000;
	std::list<Bullet*> unUseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;
public:
	Player();
	~Player();
	void Spawn(IntRect arena, Vector2i res, int tileSize);
	
	void Move(IntRect arena, Vector2f displacement);
	bool OnHitted(Time timeHit);

	Time GetLastTime() const ;
	FloatRect GetGlobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	void SetDirection(Vector2f dir);

	void Update(float dt);
	bool UpdateCollision(const std::list<Pickup*>& items);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	void Draw(RenderWindow& window);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();

	void Fire();
	Bullet* GetBullet() const;

	void Shoot(Vector2f dir);
};