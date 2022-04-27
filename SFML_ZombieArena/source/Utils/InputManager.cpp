#include ".\InputManager.h"
#include <cmath>

std::map<Axis, AxisInfo> InputManager::mapAxis;
std::list<Keyboard::Key> InputManager::OnKeysUp;
std::list<Keyboard::Key> InputManager::OnKeysDown;
std::list<Keyboard::Key> InputManager::OnKeysPress;
std::list<Mouse::Button> InputManager::OnButtonUp;
std::list<Mouse::Button> InputManager::OnButtonDown;
std::list<Mouse::Button> InputManager::OnButtonPress;

void InputManager::Init()
{
	mapAxis.clear();

	AxisInfo info;

	info.axis = Axis::Horizontal;
	info.positiveKeys.clear();

	info.value = 0.f;
	info.sensi = 3.f;
	info.limit = 0.05f;

	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);

	info.negativeKeys.clear();

	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);

	mapAxis[info.axis] = info;

	info.axis = Axis::Vertical;
	info.positiveKeys.clear();

	info.value = 0.f;
	info.sensi = 3.f;
	info.limit = 0.05f;

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
	if (!OnButtonDown.empty())
		OnButtonDown.clear();
	if (!OnButtonUp.empty())
		OnButtonUp.clear();
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
	case Event::MouseButtonPressed:
	{
		OnButtonDown.push_back(event.mouseButton.button);
		OnButtonPress.push_back(event.mouseButton.button);
	}
		break;
	case Event::MouseButtonReleased:
	{
		OnButtonPress.remove(event.mouseButton.button);
		OnButtonUp.push_back(event.mouseButton.button);
	}
		break;
	default:
		break;
	}
}

void InputManager::Update(float dt)
{
	for (auto it = mapAxis.begin(); it != mapAxis.end(); it++)
	{
		AxisInfo& ref = it->second;

		// Axis
		int axis = GetAxisRaw(ref.axis);

		// d = (dir) * vt;
		if (axis == 0)
		{
			axis = ref.value > 0 ? -1 : 1;
			if (abs(ref.value) < ref.limit)
			{
				axis = 0;
				ref.value = 0;
			}
		}
		ref.value += axis * ref.sensi * dt;
		if (ref.value > 1.f)
		{
			ref.value = 1.f;
		}
		else if (ref.value < -1.f)
		{
			ref.value = -1.f;
		}
	}

}

float InputManager::GetAxis(Axis axis)
{
	if (mapAxis.find(axis) != mapAxis.end())
	{
		return mapAxis[axis].value;
	}

	return 0.0f;
}

int InputManager::GetAxisRaw(const std::list<Keyboard::Key>& positive, const std::list<Keyboard::Key>& negative)
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

int InputManager::GetAxisRaw(Axis axis)
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxisRaw(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	return 0;
}

int InputManager::GetAxisH()
{
	std::list<Keyboard::Key> pos(Keyboard::D, Keyboard::Right);
	std::list<Keyboard::Key> nega(Keyboard::A, Keyboard::Left);
	return GetAxisRaw(pos, nega);
}

int InputManager::GetAxisV()
{
	std::list<Keyboard::Key> pos(Keyboard::S, Keyboard::Down);
	std::list<Keyboard::Key> nega(Keyboard::W, Keyboard::Up);
	return GetAxisRaw(pos, nega);
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

bool InputManager::GetLeftButtonDown(Mouse::Button button)
{
	auto it = std::find(OnButtonDown.begin(), OnButtonDown.end(), button);
	return it != OnButtonDown.end();
}

bool InputManager::GetLeftButton(Mouse::Button button)
{
	auto it = std::find(OnButtonPress.begin(), OnButtonPress.end(), button);
	return it != OnButtonPress.end();
}

bool InputManager::GetLeftButtonUp(Mouse::Button button)
{
	auto it = std::find(OnButtonUp.begin(), OnButtonUp.end(), button);
	return it != OnButtonUp.end();
}
