#include "Crosshair.h"
#include "..\Utils\TextureHolder.h"
#include "..\Utils\Utils.h"

#include <iostream>

Vector2i Crosshair::position;
Vector2f Crosshair::mapPixelCoords;

Crosshair::Crosshair()
	:textureFileName("graphics/crosshair.png")
{
	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	Utils::SetOrigin(sprite, PIVOTS::CENTER);
}

void Crosshair::Update(RenderWindow& window)
{
	position = Mouse::getPosition(window);
	mapPixelCoords = window.mapPixelToCoords(position);
	sprite.setPosition(mapPixelCoords);
	//std::cout << "x: " << sprite.getPosition().x << "y: " << sprite.getPosition().y << std::endl;
}

Vector2i Crosshair::GetPosition()
{
	return position;
}

Vector2f Crosshair::GetMapPixelCoords()
{
	return mapPixelCoords;
}

Sprite Crosshair::GetSprite() const
{
	return sprite;
}
