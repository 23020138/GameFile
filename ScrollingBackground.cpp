#include "ScrollingBackground.h"
#include "TextureManager.h"
#include "Game.h"

ScrollingBackground::ScrollingBackground() : ShooterObject()
{
    count = 0;
    maxcount = 10;
}

void ScrollingBackground::load(std::unique_ptr<LoaderParams> const& pParams)
{
    ShooterObject::load(std::move(pParams));
    _scrollSpeed = pParams->getAnimSpeed();

    _scrollSpeed = 1;

    _srcRect1.x = 0;
    _destRect1.x = _position.getX();
    _srcRect1.y = 0;
    _destRect1.y = _position.getY();

    _srcRect1.w = _destRect1.w = _srcRect2Width = _destRect1Width = _width;
    _srcRect1.h = _destRect1.h = _height;

    _srcRect2.x = 0;
    _destRect2.x = _position.getX() + _width;
    _srcRect2.y = 0;
    _destRect2.y = _position.getY();

    _srcRect2.w = _destRect2.w = _srcRect2Width = _destRect2Width = 0;
    _srcRect2.h = _destRect2.h = _height;
}

void ScrollingBackground::draw()
{
    // draw first rect
    SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), TheTextureManager::Instance()->getTextureMap()[_textureID], &_srcRect1, &_destRect1, 0, 0, SDL_FLIP_NONE);

    // draw second rect
    SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), TheTextureManager::Instance()->getTextureMap()[_textureID], &_srcRect2, &_destRect2, 0, 0, SDL_FLIP_NONE);

}

void ScrollingBackground::update()
{
    if (count == maxcount)
    {
        // make first rectangle smaller
        _srcRect1.x += _scrollSpeed;
        _srcRect1.w -= _scrollSpeed;
        _destRect1.w -= _scrollSpeed;

        // make second rectangle bigger
        _srcRect2.w += _scrollSpeed;
        _destRect2.w += _scrollSpeed;
        _destRect2.x -= _scrollSpeed;

        // reset and start again
        if (_destRect2.w >= _width)
        {
            _srcRect1.x = 0;
            _destRect1.x = _position.getX();
            _srcRect1.y = 0;
            _destRect1.y = _position.getY();

            _srcRect1.w = _destRect1.w = _srcRect2Width = _destRect1Width = _width;
            _srcRect1.h = _destRect1.h = _height;

            _srcRect2.x = 0;
            _destRect2.x = _position.getX() + _width;
            _srcRect2.y = 0;
            _destRect2.y = _position.getY();

            _srcRect2.w = _destRect2.w = _srcRect2Width = _destRect2Width = 0;
            _srcRect2.h = _destRect2.h = _height;
        }
        count = 0;
    }

    count++;
}

void ScrollingBackground::clean()
{
    ShooterObject::clean();
}