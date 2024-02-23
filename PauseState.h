#pragma once

#include <iostream>
#include <vector>
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
	virtual ~PauseState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _pauseID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void _pauseToMain();
	static void _resumePlay();

	static const std::string _pauseID;
	std::vector<GameObject*> _gameObjects;
};

