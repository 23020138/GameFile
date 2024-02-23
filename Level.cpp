#include "Level.h"
#include "TextureManager.h"
#include "Game.h"
#include "Layer.h"
#include "TileLayer.h"
#include <math.h>
#include <iostream>

Level::Level() {
}

void Level::render()
{
    for (int i = 0; i < _layers.size(); i++)
    {
        _layers[i]->render();
    }
}
void Level::update()
{
    for (int i = 0; i < _layers.size(); i++)
    {
        _layers[i]->update(this);
    }
}

Level::~Level()
{
    for (int i = 0; i < _layers.size(); i++)
    {
        delete _layers[i];
    }

    _layers.clear();
}