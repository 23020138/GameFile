#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
    for (std::vector<GameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); ++it)// < _gameObjects.size(); i++)
    {
        delete (*it);
    }
    _gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
    _collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
    _collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)_gameObjects);
    _collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)_gameObjects);

    if (pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
    {
        _collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
    }

    // iterate through the objects
    if (!_gameObjects.empty())
    {
        for (std::vector<GameObject*>::iterator it = _gameObjects.begin(); it != _gameObjects.end();)// < m_gameObjects.size(); i++)
        {
            if ((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth())
            {
                (*it)->setUpdating(true);
                (*it)->update();
            }
            else
            {
                if ((*it)->type() != std::string("Player"))
                {
                    (*it)->setUpdating(false);
                    (*it)->scroll(TheGame::Instance()->getScrollSpeed());
                }
                else
                {
                    (*it)->update();
                }
            }

            // check if dead or off screen
            if ((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheGame::Instance()->getGameHeight()) || ((*it)->dead()))
            {
                delete* it;
                it = _gameObjects.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }

        }
    }
}
void ObjectLayer::render()
{
    for (int i = 0; i < _gameObjects.size(); i++)
    {
        if (_gameObjects[i]->getPosition().getX() <= TheGame::Instance()->getGameWidth())
        {
            _gameObjects[i]->draw();
        }
    }
}