#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "ShooterObject.h"

class AnimatedGraphic : public ShooterObject
{
public:
	AnimatedGraphic();
	virtual ~AnimatedGraphic() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);

	void draw();
	void update();
	void clean();
private:
	int _animSpeed;
	int _numFrames;
};

class AnimatedGraphicCreator : public BaseCreator {
public:
	virtual GameObject* createGameObject() const {
		return new AnimatedGraphic();
	}
};