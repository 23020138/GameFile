#include "ShooterObject.h"
#include "Game.h"
#include "TextureManager.h"

ShooterObject::ShooterObject() : GameObject(), _bulletFiringSpeed(0), _bulletCounter(0), _moveSpeed(0), _dyingTime(0), _dyingCounter(0), _bPlayedDeathSound(false)
{
}

void ShooterObject::load(std::unique_ptr<LoaderParams> const& pParams) {
	_position = Vector2D(pParams->getX(), pParams->getY());

	_width = pParams->getWidth();
	_height = pParams->getHeight();
	_textureID = pParams->getTextureID();
	_numFrames = pParams->getNumFrames();
}

void ShooterObject::draw() {
	TextureManager::Instance()->drawFrame(_textureID, (Uint32)_position.getX(), (Uint32)_position.getY(), _width, _height, _currentRow, _currentFrame, TheGame::Instance()->getRenderer(), _angle, _alpha);
}

void ShooterObject::update() {
	_position += _velocity;
	_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % _numFrames));
}

void ShooterObject::doDyingAnimation()
{
	_currentFrame = int(((SDL_GetTicks() / (1000 / 10)) % _numFrames));

	if (_dyingCounter == _dyingTime)
	{
		_bDead = true;
	}
	_dyingCounter++; //simple counter, fine with fixed frame rate
}