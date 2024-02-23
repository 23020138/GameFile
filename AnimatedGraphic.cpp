#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject() {}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(pParams);
	_animSpeed = pParams->getAnimSpeed();
	_numFrames = pParams->getNumFrames();
}

void AnimatedGraphic::draw() {
	ShooterObject::draw();
}

void AnimatedGraphic::update() {
	_currentFrame = int(((SDL_GetTicks() / (300 / _animSpeed)) % _numFrames));
}

void AnimatedGraphic::clean() {
	ShooterObject::clean();
}