#pragma once
#include "SFML/Graphics.hpp"
#include <random>

using namespace sf;

enum class PIVOTS
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	LEFT,
	CENTER,
	RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT
};

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;
public:
	static void SetOrigin(Transformable& tr, FloatRect bounds, PIVOTS preset);
	static void SetOrigin(Sprite& sprite, PIVOTS preset);
	static void SetOrigin(Text& text, PIVOTS preset);
	static void SetOrigin(Shape& shape, PIVOTS preset);

	static int RandomRange(int min, int max);

	static float GetLength(const Vector2f& vector);
	static Vector2f Normalize(Vector2f vector);
	static float GetAngle(const Vector2f& from, const Vector2f& to);
};