#pragma once

#include <vector>

#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:

	virtual ~MainMenuState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _menuID; }

private:
	virtual void setCallbacks(const std::vector<Callback>&callbacks);

	// call back functions for menu items
	static void _menuToPlay();
	static void _exitFromMenu();

	static const std::string _menuID;

	std::vector<GameObject*> _gameObjects;
};