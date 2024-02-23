#include "InputHandler.h"
#include "Game.h"
#include <iostream>

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : _keystates(0), _mousePosition(new Vector2D(0,0)) {
	for (int i = 0; i < 3; i++)
	{
		_mouseButtonStates.push_back(false);
	}
	// 0 for the left, 1 for the middle and 2 for the right
}

InputHandler::~InputHandler() {
	delete _keystates;
	delete _mousePosition;
}

void InputHandler::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				TheGame::Instance()->quit(); 
				break;
			case SDL_MOUSEMOTION:
				onMouseMove(event); 
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event); 
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event); 
				break;
			case SDL_KEYDOWN:
				onKeyDown();
				break;

			case SDL_KEYUP:
				onKeyUp();
				break;
			default: 
				break;
		}
	}
}

void InputHandler::clean() {
}

bool InputHandler::getMouseButtonState(int buttonNumber) const {
	return _mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() const{
	return _mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
	if (_keystates != 0)
	{
		if (_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void InputHandler::onMouseButtonDown(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onMouseMove(SDL_Event& event) {
	_mousePosition->setX(event.motion.x);
	_mousePosition->setY(event.motion.y);
}

void InputHandler::reset() {
	_mouseButtonStates[LEFT] = false;
	_mouseButtonStates[MIDDLE] = false;
	_mouseButtonStates[RIGHT] = false;
}

void InputHandler::onKeyDown() {
	_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {
	_keystates = SDL_GetKeyboardState(0);
}