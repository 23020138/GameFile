#pragma once
#include <iostream>
#include <string>
#include "ShooterObject.h"

class Enemy : public ShooterObject
{
public:
	virtual std::string type() { return"Enemy"; }
protected:
	int _health;
	Enemy() : ShooterObject() {}
	virtual ~Enemy() {} // for polymorphism
};
