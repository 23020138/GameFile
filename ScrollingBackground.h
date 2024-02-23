#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "ShooterObject.h"

class ScrollingBackground : public ShooterObject
{
public:

    virtual ~ScrollingBackground() {}
    ScrollingBackground();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);

private:

    int _scrollSpeed;

    int count;
    int maxcount;

    SDL_Rect _srcRect1;
    SDL_Rect _srcRect2;

    SDL_Rect _destRect1;
    SDL_Rect _destRect2;

    int _srcRect1Width;
    int _srcRect2Width;

    int _destRect1Width;
    int _destRect2Width;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new ScrollingBackground();
    }
};
