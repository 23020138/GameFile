#pragma once

#include "Level.h"
#include "tinyxml.h"
#include <iostream>
#include <vector>

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:
	Level* parseLevel(const char* LevelFile);
private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*>* pCollisionLayers);
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel);

	int _tileSize;
	int _width;
	int _height;
};

