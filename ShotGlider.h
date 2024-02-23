#pragma once

#include "Glider.h"

class ShotGlider : public Glider
{
public:

    virtual ~ShotGlider() {}

    ShotGlider() : Glider()
    {
        _bulletFiringSpeed = 25;
        _moveSpeed = 3;
    }

    virtual void load(std::unique_ptr<LoaderParams> const& pParams)
    {
        ShooterObject::load(std::move(pParams));

        _velocity.setX(-_moveSpeed);
    }

    virtual void update()
    {
        if (!_bDying)
        {
            if (_bulletCounter == _bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY() + 15, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                _bulletCounter = 0;
            }

            _bulletCounter++;
        }
        else
        {
            _velocity.setX(0);
            doDyingAnimation();
        }

        ShooterObject::update();
    }
};

class ShotGliderCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new ShotGlider();
    }
};