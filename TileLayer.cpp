#include "TileLayer.h"
#include "TextureManager.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) : _tileSize(tileSize), _tilesets(tilesets), _position(0, 0), _velocity(0, 0)
{
	_numColumns = (TheGame::Instance()->getGameWidth() / _tileSize) + 1;
	_numRows = (TheGame::Instance()->getGameHeight() / _tileSize);
}

void TileLayer::update(Level* pLevel) {
    if (_position.getX() < ((_mapWidth * _tileSize) - TheGame::Instance()->getGameWidth()) - _tileSize)
    {
        _velocity.setX(TheGame::Instance()->getScrollSpeed());
        _position += _velocity;

    }
    else
    {
        _velocity.setX(0);
    }
}

void TileLayer::render() {
	int x, y, x2, y2 = 0;

	x = _position.getX() / _tileSize;
	y = _position.getY() / _tileSize;

	x2 = int(_position.getX()) % _tileSize;
	y2 = int(_position.getY()) % _tileSize;

    for (int i = 0; i < _numRows; i++)
    {
        for (int j = 0; j < _numColumns; j++)
        {
            if (i + y >= _tileIDs.size()) {
                break;
            }
            if (j + x >= _tileIDs[0].size()) {
                break;
            }
            int id = _tileIDs[i+y][j+x];
            if (id == 0)
            {
                continue;
            }
            Tileset tileset = getTilesetByID(id);
            id--;
            TheTextureManager::Instance()->drawTile(tileset.name, 2, 2, (j * _tileSize) - x2, (i * _tileSize) - y2, _tileSize, _tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::Instance()->getRenderer());
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) {
    for (int i = 0; i < _tilesets.size(); i++)
    {
        if (i + 1 <= _tilesets.size() - 1)
        {
            if (tileID >= _tilesets[i].firstGridID && tileID < _tilesets[i + 1].firstGridID)
            {
                return _tilesets[i];
            }
        }
        else
        {
            return _tilesets[i];
        }
    }
    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}