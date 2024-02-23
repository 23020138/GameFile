#pragma once
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class MenuButton : public ShooterObject
{
public:
	MenuButton();
	virtual ~MenuButton() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void setCallback(void(*callback)()) { _callback = callback; }
	int getCallbackID() { return _callbackID; }

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	bool _released;
	int _callbackID;
	void(*_callback)();
};

class MenuButtonCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new MenuButton();
	}
};

