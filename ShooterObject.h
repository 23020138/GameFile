#pragma once
#include "GameObject.h"
#include "SDL.h"

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject() {}// for polymorphism
	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}// not implemented in this class
	virtual void collision() {}//not implemented in this class
	virtual std::string type() { return "SDLGameObject"; }
protected:
	// we won't directly create ShooterObject's
	ShooterObject();
	// draw the animation for the object being destroyed
	void doDyingAnimation();
	// how fast will this object fire bullets? with a counter
	int _bulletFiringSpeed;
	int _bulletCounter;
	// how fast will this object move?
	int _moveSpeed;
	// how long will the death animation takes? with a counter
	int _dyingTime;
	int _dyingCounter;
	// has the explosion sound played?
	bool _bPlayedDeathSound;
};

