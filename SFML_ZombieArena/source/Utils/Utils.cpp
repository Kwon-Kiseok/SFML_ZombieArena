#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen(rd());

void Utils::SetOrigin(Transformable& tr, FloatRect bounds, PIVOTS preset)
{
	switch (preset)
	{
	case PIVOTS::TOP_LEFT:
		tr.setOrigin(0.f, 0.f);
		break;
	case PIVOTS::TOP_CENTER:
		tr.setOrigin(bounds.width * 0.5f, 0.f);
		break;
	case PIVOTS::TOP_RIGHT:
		tr.setOrigin(bounds.width, 0.f);
		break;
	case PIVOTS::LEFT:
		tr.setOrigin(0.f, bounds.height * 0.5f);
		break;
	case PIVOTS::CENTER:
		tr.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
		break;
	case PIVOTS::RIGHT:
		tr.setOrigin(bounds.width, bounds.height * 0.5f);
		break;
	case PIVOTS::BOTTOM_LEFT:
		tr.setOrigin(0.f, bounds.height);
		break;
	case PIVOTS::BOTTOM_CENTER:
		tr.setOrigin(bounds.width * 0.5f, bounds.height);
		break;
	case PIVOTS::BOTTOM_RIGHT:
		tr.setOrigin(bounds.width, bounds.height);
		break;
	default:
		break;
	}
}

void Utils::SetOrigin(Sprite& sprite, PIVOTS preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}

void Utils::SetOrigin(Text& text, PIVOTS preset)
{
	SetOrigin(text, text.getGlobalBounds(), preset);
}

void Utils::SetOrigin(Shape& shape, PIVOTS preset)
{
	SetOrigin(shape, shape.getGlobalBounds(), preset);
}

int Utils::RandomRange(int min, int max)
{
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

float Utils::GetLength(const Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Utils::Normalize(Vector2f vector)
{
	float length = GetLength(vector);
	if (length > 0)
	{
		vector /= length;
	}

	return vector;
}

float Utils::GetAngle(const Vector2f& from, const Vector2f& to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	float degree = (radian * 180.f) / 3.141592f;
	return degree;
}
