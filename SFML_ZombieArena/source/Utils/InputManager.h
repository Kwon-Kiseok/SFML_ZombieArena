#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <map>

using namespace sf;

enum class Axis
{
	Horizontal,
	Vertical
};

struct AxisInfo
{
	Axis axis;
	std::list<Keyboard::Key> positiveKeys;
	std::list<Keyboard::Key> negativeKeys;
};

class InputManager
{
private:
	static std::map<Axis, AxisInfo> mapAxis;

	static std::list<Keyboard::Key> OnKeysUp;
	static std::list<Keyboard::Key> OnKeysDown; 
	static std::list<Keyboard::Key> OnKeysPress; //눌려지고 있을 때

public:
	static void Init();

	static void ClearPrevInput();
	static void ProcessInput(const Event& event);

	static int GetAxis(const std::list<Keyboard::Key>& positive, const std::list<Keyboard::Key>& negative);
	static int GetAxis(Axis axis);
	static int GetAxisH(); // 좌우 입력
	static int GetAxisV(); // 상하 입력

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static Vector2i GetMousePosition();
};

