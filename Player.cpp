#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "TileLayer.h"
#include "BulletHandler.h"
#include "SoundManager.h"

Player::Player() : ShooterObject(),
                _invulnerable(false),
                _invulnerableTime(200),
                _invulnerableCounter(0)
{
}

void Player::collision()
{
    // if the player is not invulnerable then set to dying and change values for death animation tile sheet
    if (!_invulnerable && !TheGame::Instance()->getLevelComplete())
    {
        _textureID = "largeexplosion";
        _currentFrame = 0;
        _numFrames = 9;
        _width = 60;
        _height = 60;
        _bDying = true;
    }
}

void Player::draw()
{
	ShooterObject::draw();
}

void Player::update()
{
    if (TheGame::Instance()->getLevelComplete())
    {
        if (_position.getX() >= TheGame::Instance()->getGameWidth())
        {
            if (TheGame::Instance()->getCurrentLevel() != TheGame::Instance()->getNumLevels()) {
                TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
            }
            else {
                TheGame::Instance()->setCurrentLevel(1);
            }
        }
        else
        {
            _velocity.setY(0);
            _velocity.setX(3);
            ShooterObject::update();
            handleAnimation();
        }
    }
    else
    {
        // if the player is not doing its death animation then update it normally
        if (!_bDying)
        {
            // reset velocity
            _velocity.setX(0);
            _velocity.setY(0);

            // get input
            handleInput();

            // do normal position += velocity update
            ShooterObject::update();

            // update the animation
            handleAnimation();
        }
        else // if the player is doing the death animation
        {
            _currentFrame = int(((SDL_GetTicks() / (100)) % _numFrames));
            // if the death animation has completed
            if (_dyingCounter == _dyingTime)
            {
                // ressurect the player
                ressurect();
            }
            _dyingCounter++;
        }
    }
}

void Player::clean()
{
	ShooterObject::clean();
}

void Player::handleInput() {
    if (!_bDead)
    {
        // handle keys
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && _position.getY() > 0)
        {
            _velocity.setY(-_moveSpeed);
        }
        else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && (_position.getY() + _height) < TheGame::Instance()->getGameHeight() - 10)
        {
            _velocity.setY(_moveSpeed);
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && _position.getX() > 0)
        {
            _velocity.setX(-_moveSpeed);
        }
        else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && (_position.getX() + _width) < TheGame::Instance()->getGameWidth())
        {
            _velocity.setX(_moveSpeed);
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            if (_bulletCounter == _bulletFiringSpeed)
            {
                TheSoundManager::Instance()->playSound("shoot", 0);
                TheBulletHandler::Instance()->addPlayerBullet(_position.getX() + 90, _position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10, 0));
                _bulletCounter = 0;
            }

            _bulletCounter++;
        }
        else
        {
            _bulletCounter = _bulletFiringSpeed;
        }
    }
}

void Player::load(std::unique_ptr<LoaderParams> const& pParams) {
	ShooterObject::load(std::move(pParams));

    // set up bullets
    _bulletFiringSpeed = 13;
    _moveSpeed = 3;

    // we want to be able to fire instantly
    _bulletCounter = _bulletFiringSpeed;

    _dyingTime = 100;
}

void Player::ressurect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);
	_position.setX(10);
	_position.setY(200);
	_bDying = false;
	_textureID = "player";
	_currentFrame = 0;
	_numFrames = 5;
	_width = 119;
	_height = 52;
	_dyingCounter = 0;
	_invulnerable = true;
}

void Player::handleAnimation()
{
    // if the player is invulnerable we can flash its alpha to let people know
    if (_invulnerable)
    {
        // invulnerability is finished, set values back
        if (_invulnerableCounter == _invulnerableTime)
        {
            _invulnerable = false;
            _invulnerableCounter = 0;
            _alpha = 255;
        }
        else // otherwise, flash the alpha on and off
        {
            if (_alpha == 255)
            {
                _alpha = 0;
            }
            else
            {
                _alpha = 255;
            }
        }

        // increment our counter
        _invulnerableCounter++;
    }

    // if the player is not dead then we can change the angle with the velocity to give the impression of a moving helicopter
    if (!_bDead)
    {
        if (_velocity.getX() < 0)
        {
            _angle = -10.0;
        }
        else if (_velocity.getX() > 0)
        {
            _angle = 10.0;
        }
        else
        {
            _angle = 0.0;
        }
    }

    // our standard animation code - for helicopter propellors
    _currentFrame = int(((SDL_GetTicks() / (100)) % _numFrames));
}