#pragma once

#include <iostream>
#include <vector>
#include "MenuState.h"

class GameObject;

class GameOverState : public MenuState
{
public:
	virtual ~GameOverState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _gameOverID; }
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
	static void _gameOverToMain();
	static void _restartPlay();

	static const std::string _gameOverID;

	std::vector<GameObject*> _gameObjects;
};