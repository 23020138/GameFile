#pragma once

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <memory>

class GameObject
{
public:

    // base class needs virtual destructor
    virtual ~GameObject() {}

    // load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
    virtual void load(std::unique_ptr<LoaderParams> const& pParams) = 0;

    // draw the object
    virtual void draw() = 0;

    // do update stuff
    virtual void update() = 0;

    // remove anything that needs to be deleted
    virtual void clean() = 0;

    // object has collided, handle accordingly
    virtual void collision() = 0;

    // get the type of the object
    virtual std::string type() = 0;

    // getters for common variables
    Vector2D& getPosition() { return _position; }
    Vector2D& getVelocity() { return _velocity; }

    int getWidth() { return _width; }
    int getHeight() { return _height; }

    // scroll along with tile map
    void scroll(float scrollSpeed)
    {
        if (type() != std::string("Player")) // player is never scrolled
        {
            _position.setX(_position.getX() - scrollSpeed);
        }
    }

    // is the object currently being updated?
    bool updating() { return _bUpdating; }

    // is the object dead?
    bool dead() { return _bDead; }

    // is the object doing a death animation?
    bool dying() { return _bDying; }

    // set whether to update the object or not
    void setUpdating(bool updating) { _bUpdating = updating; }

protected:

    // constructor with default initialisation list
    GameObject() : _position(0, 0),
        _velocity(0, 0),
        _acceleration(0, 0),
        _width(0),
        _height(0),
        _currentRow(0),
        _currentFrame(0),
        _bUpdating(false),
        _bDead(false),
        _bDying(false),
        _angle(0),
        _alpha(255)
    {
    }

    // movement variables
    Vector2D _position;
    Vector2D _velocity;
    Vector2D _acceleration;

    // size variables
    int _width;
    int _height;

    // animation variables
    int _currentRow;
    int _currentFrame;
    int _numFrames;
    std::string _textureID;

    // common boolean variables
    bool _bUpdating;
    bool _bDead;
    bool _bDying;

    // rotation
    double _angle;

    // blending
    int _alpha;
};