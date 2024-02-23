#pragma once

#include "Enemy.h"
#include "SoundManager.h"
#include "Game.h"
#include "BulletHandler.h"

class Game;
class BulletHandler;

class Eskeletor : public Enemy {
public:
	virtual ~Eskeletor() {}

	Eskeletor() : Enemy() {
		_dyingTime = 50;
		_health = 1;
		_moveSpeed = 3;
		_bulletFiringSpeed = 50;
	}

	virtual void collision() {
		_health -= 1;
		if (_health == 0) {
			if (!_bPlayedDeathSound) {
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

	virtual void update() {
		if (!_bDying)
		{
			scroll(TheGame::Instance()->getScrollSpeed());
			_velocity.setY(_moveSpeed);

			if (_bulletCounter == _bulletFiringSpeed)
			{
				TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY(), 16, 16, "bullet1", 1, Vector2D(-3, 0));
				TheBulletHandler::Instance()->addEnemyBullet(_position.getX(), _position.getY(), 16, 16, "bullet1", 1, Vector2D(3, 0));
				_bulletCounter = 0;
			}
			_bulletCounter++;

		}
		else
		{
			_velocity.setY(0);
			doDyingAnimation();
		}

		ShooterObject::update();
	}
};

class EskeletorCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Eskeletor();
	}
};