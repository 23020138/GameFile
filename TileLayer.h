#pragma once
#include <iostream>
#include <vector>
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset>& tilesets);

	virtual ~TileLayer() {}

	virtual void update(Level* pLevel);
	virtual void render();

    void setTileIDs(const std::vector<std::vector<int>>& data)
    {
        _tileIDs = data;
    }

    void setTileSize(int tileSize)
    {
        _tileSize = tileSize;
    }

    void setMapWidth(int mapWidth) { _mapWidth = mapWidth; }

    int getTileSize() { return _tileSize; }

    const std::vector<std::vector<int>>& getTileIDs() { return _tileIDs; }

    Tileset getTilesetByID(int tileID);

    const Vector2D getPosition() { return _position; }

private:
    int _numColumns;
    int _numRows;
    int _tileSize;

    int _mapWidth;

    Vector2D _position;
    Vector2D _velocity;

    const std::vector<Tileset>& _tilesets;
    std::vector<std::vector<int>> _tileIDs;
};