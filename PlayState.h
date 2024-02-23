#pragma once
#include "GameState.h"
#include <vector>
#include "Collision.h"
#include "Level.h"

class GameObject;
class ShooterObject;
class Level;

class PlayState : public GameState
{
public:
	virtual ~PlayState() { delete pLevel; }
	//virtual ~PlayState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _playID; }

private:
	static const std::string _playID;

	CollisionManager _collisionManager;

	std::vector<GameObject*> _gameObjects;

	Level* pLevel;
};
