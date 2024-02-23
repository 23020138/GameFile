#pragma once
#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"

class Glider : public Enemy
{
public:

    Glider() : Enemy()
    {
        _dyingTime = 25;
        _health = 1;
        _moveSpeed = 3;
        _gap = 60;
    }

    virtual ~Glider() {}

    virtual void load(std::unique_ptr<LoaderParams> const& pParams)
    {
        ShooterObject::load(std::move(pParams));

        _velocity.setX(-_moveSpeed);
        _velocity.setY(_moveSpeed / 2);

        _maxHeight = _position.getY() + _gap;
        _minHeight = _position.getY() - _gap;
    }

    virtual void collision()
    {
        _health -= 1;

        if (_health == 0)
        {
            if (!_bPlayedDeathSound)
            {
                TheSoundManager::Instance()->playSound("explode", 0);

                _textureID = "explosion";
                _currentFrame = 0;
                _numFrames = 9;
                _width = 40;
                _height = 40;
                _bDying = true;
            }
        }
    }

    virtual void update()
    {
        if (!_bDying)
        {
            if (_position.getY() >= _maxHeight)
            {
                _velocity.setY(-_moveSpeed);
            }
            else if (_position.getY() <= _minHeight)
            {
                _velocity.setY(_moveSpeed);
            }
        }
        else
        {
            _velocity.setX(0);
            _velocity.setY(0);
            doDyingAnimation();
        }

        ShooterObject::update();

    }

private:

    int _maxHeight;
    int _minHeight;
    int _gap;
};

class GliderCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Glider();
    }
};