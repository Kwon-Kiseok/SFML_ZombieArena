#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

enum class ZombieTypes
{
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT,
};

struct ZombieInfo
{
	ZombieTypes type;
	std::string textureFileName;
	float speed;
	int health;
};

class Player;
class Zombie
{
private:
	ZombieTypes zombieType;

	Vector2f position;
	Sprite sprite;

	Vector2i resoultion;

	float speed;
	int health;

	bool alive;

	static std::vector<ZombieInfo> zombieInfo;
	static bool isInitInfo;

public:
	Zombie();

	void Move(IntRect arena, Vector2f displacement);
	bool OnHitted();
	bool IsAlive();

	void Spawn(float x, float y, ZombieTypes type);
	void Update(float dt, Vector2f playerPos, IntRect arena);

	bool UpdateCollision(Time time, Player& player);

	FloatRect GetGlobalBound();
	Sprite GetSprite();

};