#include ".\InputManager.h"

std::map<Axis, AxisInfo> InputManager::mapAxis;
std::list<Keyboard::Key> InputManager::OnKeysUp;
std::list<Keyboard::Key> InputManager::OnKeysDown;
std::list<Keyboard::Key> InputManager::OnKeysPress;

void InputManager::Init()
{
	mapAxis.clear();

	AxisInfo info;
	info.axis = Axis::Horizontal;
	info.positiveKeys.clear();

	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);

	info.negativeKeys.clear();

	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);

	mapAxis[info.axis] = info;

	info.axis = Axis::Vertical;
	info.positiveKeys.clear();

	info.positiveKeys.push_back(Keyboard::S);
	info.positiveKeys.push_back(Keyboard::Down);

	info.negativeKeys.clear();

	info.negativeKeys.push_back(Keyboard::W);
	info.negativeKeys.push_back(Keyboard::Up);

	mapAxis[info.axis] = info;
}

void InputManager::ClearPrevInput()
{
	if(!OnKeysUp.empty())
		OnKeysUp.clear();
	if (!OnKeysDown.empty())
		OnKeysDown.clear();
}

void InputManager::ProcessInput(const Event& event)
{
	Keyboard::Key eventKey = event.key.code;

	switch (event.type)
	{
	case Event::KeyPressed:
	{
		if (!GetKey(eventKey))
		{
			OnKeysDown.push_back(eventKey);
			OnKeysPress.push_back(eventKey);
		}
	}
		break;
	case Event::KeyReleased:
	{
		OnKeysPress.remove(eventKey);
		OnKeysUp.push_back(eventKey);
	}
		break;
	default:
		break;
	}
}

int InputManager::GetAxis(const std::list<Keyboard::Key>& positive, const std::list<Keyboard::Key>& negative)
{
	int axis = 0;
	bool isPositive = false, isNegative = false;

	for (auto it = positive.begin(); it != positive.end(); it++)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isPositive = true;
			break;
		}
	}

	for (auto it = negative.begin(); it != negative.end(); it++)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isNegative = true;
			break;
		}
	}

	if (isPositive && isNegative)
	{
		axis = 0;
	}
	else if (isPositive)
	{
		axis = 1;
	}
	else if (isNegative)
	{
		axis = -1;
	}

	return axis;
}

int InputManager::GetAxis(Axis axis)
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxis(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	return 0;
}

int InputManager::GetAxisH()
{
	std::list<Keyboard::Key> pos(Keyboard::D, Keyboard::Right);
	std::list<Keyboard::Key> nega(Keyboard::A, Keyboard::Left);
	return GetAxis(pos, nega);
}

int InputManager::GetAxisV()
{
	std::list<Keyboard::Key> pos(Keyboard::S, Keyboard::Down);
	std::list<Keyboard::Key> nega(Keyboard::W, Keyboard::Up);
	return GetAxis(pos, nega);
}

bool InputManager::GetKeyDown(Keyboard::Key key)
{
	auto it = std::find(OnKeysDown.begin(), OnKeysDown.end(), key);
	return it != OnKeysDown.end();
}

bool InputManager::GetKey(Keyboard::Key key)
{
	auto it = std::find(OnKeysPress.begin(), OnKeysPress.end(), key);
	return it != OnKeysPress.end();
}

bool InputManager::GetKeyUp(Keyboard::Key key)
{
	auto it = std::find(OnKeysUp.begin(), OnKeysUp.end(), key);
	return it != OnKeysUp.end();
}

Vector2i InputManager::GetMousePosition()
{
	return Mouse::getPosition();
}
