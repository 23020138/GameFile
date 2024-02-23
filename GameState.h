#pragma once
#include <string>
#include <vector>

class GameState
{
public:
	virtual ~GameState() {}
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void resume() {}

	virtual std::string getStateID() const = 0;
protected:
	GameState() :_loadingComplete(false), _exiting(false) {}
	
	bool _loadingComplete;
	bool _exiting;

	std::vector<std::string> _textureIDList;
};