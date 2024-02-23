#pragma once

#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
		
	void reset();

	void update();
	void clean();

	bool isKeyDown(SDL_Scancode key) const;

	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;


private:
	InputHandler();
	~InputHandler();

	InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);

	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	const Uint8* _keystates;

	// mouse specific
	std::vector<bool> _mouseButtonStates;
	Vector2D* _mousePosition;

	static InputHandler* s_pInstance;

};

typedef InputHandler TheInputHandler;
