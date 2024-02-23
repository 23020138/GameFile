#pragma once

#include "ShooterObject.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

class PlayerBullet : public ShooterObject
{
public:
    PlayerBullet() : ShooterObject()
    {
        _dyingTime = 5;
    }

    virtual ~PlayerBullet() {}

    virtual std::string type() { return "PlayerBullet"; }

    virtual void load(std::unique_ptr<LoaderParams> pParams, Vector2D heading)
    {
        ShooterObject::load(std::move(pParams));
        _heading = heading;
    }

    virtual void draw()
    {
        ShooterObject::draw();
    }

    virtual void collision()
    {
        _textureID = "smallexplosion";
        _currentFrame = 0;
        _numFrames = 2;
        _width = 20;
        _height = 20;
        _bDying = true;
    }

    virtual void update()
    {
        if (!_bDying)
        {
            _velocity.setX(_heading.getX());
            _velocity.setY(_heading.getY());

            ShooterObject::update();
        }
        else
        {
            _velocity.setX(0);
            _velocity.setY(0);
            doDyingAnimation();
        }
    }

    virtual void clean()
    {
        ShooterObject::clean();
    }

private:

    Vector2D _heading;
};

class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet() : PlayerBullet()
    {
    }

    virtual ~EnemyBullet() {}

    virtual std::string type() { return "EnemyBullet"; }
};