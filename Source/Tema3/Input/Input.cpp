#include "Input.h"

int Input::deltaMouseX = 0;
int Input::deltaMouseY = 0;
bool Input::fire0 = false;
bool Input::spaceKeyDown = false;
bool Input::w = false;
bool Input::a = false;
bool Input::s = false;
bool Input::d = false;

void Input::Reset()
{
	Input::deltaMouseX = 0;
	Input::deltaMouseY = 0;
	Input::spaceKeyDown = false;
	Input::w = false;
	Input::a = false;
	Input::s = false;
	Input::d = false;
	Input::fire0 = false;
}