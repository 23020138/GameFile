#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Layer.h"
#include "LevelParser.h"
#include "Player.h"
#include "CollisionManager.h"

class TileLayer;

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level
{
public:
	~Level();

	void update();
	void render();

	std::vector<Tileset>* getTilesets() {
		return &_tilesets;
	}

	std::vector<Layer*>* getLayers() {
		return &_layers;
	}

	std::vector<TileLayer*>* getCollisionLayers() { return &_collisionLayers; }

	const std::vector<TileLayer*>& getCollidableLayers() { return _collisionLayers; }

	Player* getPlayer() { return _player; }
	void setPlayer(Player* pPlayer) { _player = pPlayer; }

private:
	std::vector<Tileset> _tilesets;
	std::vector<Layer*> _layers;
	std::vector<TileLayer*> _collisionLayers;

	friend class LevelParser;
	Level();

	Player* _player;
};

