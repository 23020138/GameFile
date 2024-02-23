#pragma once
#include "Enemy.h"
#include "Game.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "GameObjectFactory.h"

class Game;

class Level2Boss : public Enemy
{
public:

    virtual ~Level2Boss() {}

    Level2Boss() : Enemy()
    {
        _health = 100;
        _dyingTime = 100;
        _bulletFiringSpeed = 120;

        _moveSpeed = 3;

        _entered = false;
    }

    virtual void load(std::unique_ptr<LoaderParams> const& pParams)
    {
        ShooterObject::load(std::move(pParams));

        _velocity.setY(-_moveSpeed);
    }

    virtual void collision()
    {
        if (_entered)
        {
            _health -= 1;
            if (_health <= 99 && _health > 0) {
                if (!check2) {
                    TheSoundManager::Instance()->turnOff();
                    TheSoundManager::Instance()->load("assets/JotaroTheme.ogg", "music5", SOUND_MUSIC);
                    TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
                    TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

                    TheSoundManager::Instance()->playMusic("music5", -1);
                    check2 = 1;
                }
            }
            if (_health == 0)
            {
                if (!_bPlayedDeathSound)
                {
                    _position.setX(_position.getX() + 30);
                    _position.setY(_position.getY() + 70);
                    TheSoundManager::Instance()->playSound("explode", 0);

                    _textureID = "bossexplosion";
                    _currentFrame = 0;
                    _numFrames = 9;
                    _width = 180;
                    _height = 180;
                    _bDying = true;
                    check2 = 0;
                }

            }
        }
    }

    virtual void update()
    {
        if (!_entered)
        {
            scroll(TheGame::Instance()->getScrollSpeed());

            if (_position.getX() < (TheGame::Instance()->getGameWidth() - (_width + 20)))
            {
                _entered = true;
            }
        }
        else
        {
            if (!_bDying)
            {
                if (_position.getY() + _height >= TheGame::Instance()->getGameHeight())
                {
                    _velocity.setX(_moveSpeed);
                    _velocity.setY(-_moveSpeed);
                }
                else if (_position.getY() <= 0)
                {
                    _velocity.setX(-_moveSpeed);
                    _velocity.setY(_moveSpeed);
                }

                if (_bulletCounter == _bulletFiringSpeed)
                {
                    TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY() + 15, 33, 33, "bullet3", 1, Vector2D(-10, 0));
                    TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY() + 45, 33, 33, "bullet3", 1, Vector2D(-10, 0));

                    TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY() + 200, 33, 33, "bullet3", 1, Vector2D(-10, 0));
                    TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY() + 245, 33, 33, "bullet3", 1, Vector2D(-10, 0));

                    _bulletCounter = 0;
                }

                _bulletCounter++;

                ShooterObject::update();
            }
            else
            {
                scroll(TheGame::Instance()->getScrollSpeed());
                _currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % _numFrames));

                if (_dyingCounter == _dyingTime)
                {
                    TheSoundManager::Instance()->turnOff();
                    TheSoundManager::Instance()->load("assets/cup_song.ogg", "music1", SOUND_MUSIC);
                    TheSoundManager::Instance()->playMusic("music1", -1);

                    _bDead = true;
                    TheGame::Instance()->setLevelComplete(true);

                }
                _dyingCounter++;

            }

        }
    }

private:
    bool check2 = 0;
    bool _entered;
};

class Level2BossCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Level2Boss();
    }
};