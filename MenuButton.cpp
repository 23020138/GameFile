#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() :ShooterObject(), _callback(0), _released(true) {}

void MenuButton::load(std::unique_ptr<LoaderParams> const& pParams)
{
    ShooterObject::load(std::move(pParams));
    _callbackID = pParams->getCallbackID();
    _currentFrame = MOUSE_OUT; // start at frame 0
}

void MenuButton::draw() {
    ShooterObject::draw();
}

void MenuButton::update() {
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
    if (pMousePos->getX() < (_position.getX() + _width) && pMousePos->getX() > _position.getX() && pMousePos->getY() < (_position.getY() + _height) && pMousePos->getY() > _position.getY())
    {
        if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && _released)
        {
            _currentFrame = CLICKED;
            if (_callback != 0) {
                _callback(); // call our callback function
            }
            TheInputHandler::Instance()->reset();
            _released = false;
        }
        else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            _released = true;
            _currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        _currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean() {
    ShooterObject::clean();
}