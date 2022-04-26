#pragma once
#include "SFML/Graphics.hpp"
#include "..\Utils\InputManager.h"

using namespace sf;

class Crosshair
{
private:
	static Vector2i position;
	static Vector2f mapPixelCoords;
	Sprite sprite;

	std::string textureFileName;

public:
	Crosshair();
	void Update(RenderWindow& window);

	static Vector2i GetPosition();
	static Vector2f GetMapPixelCoords();
	Sprite GetSprite() const;
};

