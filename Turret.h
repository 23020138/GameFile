#pragma once
#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"

class Turret : public Enemy
{
public:

    Turret()
    {
        _dyingTime = 100;
        _health = 3;
        _bulletFiringSpeed = 30;
    }

    virtual ~Turret() {}

    virtual void collision()
    {
        _health -= 1;

        if (_health == 0)
        {
            if (!_bPlayedDeathSound)
            {
                TheSoundManager::Instance()->playSound("explode", 0);

                _textureID = "largeexplosion";
                _currentFrame = 0;
                _numFrames = 9;
                _width = 60;
                _height = 60;
                _bDying = true;
            }

        }
    }

    virtual void update()
    {
        if (!_bDying)
        {
            // we want to scroll this object with the rest
            scroll(TheGame::Instance()->getScrollSpeed());

            if (_bulletCounter == _bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX() + 20, _position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX() + 40, _position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
                _bulletCounter = 0;
            }

            _bulletCounter++;
        }
        else
        {
            scroll(TheGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }

    }

};

class TurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Turret();
    }
};