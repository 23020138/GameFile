#pragma once

#include "Turret.h"

class RoofTurret : public Turret
{
public:

    virtual ~RoofTurret() {}

    virtual void draw()
    {
        TextureManager::Instance()->drawFrame(_textureID, (Uint32)_position.getX(), (Uint32)_position.getY(), _width, _height, _currentRow, _currentFrame, TheGame::Instance()->getRenderer(), _angle, _alpha, SDL_FLIP_VERTICAL);
    }

    virtual void update()
    {
        if (!_bDying)
        {
            // we want to scroll this object with the rest
            scroll(TheGame::Instance()->getScrollSpeed());

            if (_bulletCounter == _bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX() + 20, _position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX() + 40, _position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
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

class RoofTurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new RoofTurret();
    }
};