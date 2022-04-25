#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	float speed;

	Vector2f position;
	
	Sprite sprite;
	Texture texture;
	
	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f direction;

	int health;
	int maxHealth;
	float immuneMs;

	Time lastHit;

public:
	Player();

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const ;
	FloatRect GetGlobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	void SetDirection(Vector2f dir);

	void Update(float dt);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();

};