#pragma once

#include <iostream>
#include <vector>
#include "MenuState.h"

class GameObject;

class WinState : public MenuState
{
public:
	virtual ~WinState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _winID; }
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
	static void _winToMain();
	static void _restartPlay();

	static const std::string _winID;

	std::vector<GameObject*> _gameObjects;
};