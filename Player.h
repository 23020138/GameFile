#pragma once

#include <iostream>
#include <vector>
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision();

	virtual std::string type() { return "Player"; }
private:
	// bring the player back if there are lives left
	void ressurect();
	// handle any input from the keyboard, mouse, or joystick
	void handleInput();
	// handle any animation for the player
	void handleAnimation();
	// player can be invulnerable for a time
	int _invulnerable;
	int _invulnerableTime;
	int _invulnerableCounter;
};

class PlayerCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new Player();
	}
};

