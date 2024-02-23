#pragma once
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0) :
        _x(x),
        _y(y),
        _width(width),
        _height(height),
        _textureID(textureID),
        _numFrames(numFrames),
        _callbackID(callbackID),
        _animSpeed(animSpeed)
    {
    }

    int getX() const { return _x; }
    int getY() const { return _y; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    std::string getTextureID() const { return _textureID; }
    int getNumFrames() const { return _numFrames; }
    int getCallbackID() const { return _callbackID; }
    int getAnimSpeed() const { return _animSpeed; }
private:
	int _x;
	int _y;

	int _width;
	int _height;
	
	int _callbackID;
	int _animSpeed;

	std::string _textureID;
	int _numFrames;
};

