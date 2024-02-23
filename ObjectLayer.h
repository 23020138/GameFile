#pragma once
#include "Layer.h"
#include <iostream>
#include <vector>
#include "CollisionManager.h"

class GameObject;

class ObjectLayer : public Layer
{
public:
	virtual ~ObjectLayer();
	virtual void update(Level* pLevel);
	virtual void render();

	std::vector<GameObject*>* getGameObjects() {
		return &_gameObjects;
	}

private:
	CollisionManager _collisionManager;

	std::vector<GameObject*> _gameObjects;
};

