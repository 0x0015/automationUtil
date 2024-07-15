#pragma once
#include <iostream>
#include <unordered_map>

class inputState{
	enum buttonState{
		NONE,
		PRESSED,
		HELD,
		CLICKED,
	};
	std::unordered_map<int, buttonState> mouseState;
	std::unordered_map<int, buttonState> keyboardState;
};
