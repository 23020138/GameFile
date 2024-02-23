#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	GameStateMachine() {}
	~GameStateMachine() {}

	void update();
	void render();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void clean();

	std::vector<GameState*>& getGameState() { return _gameStates; }

private:
	std::vector<GameState*> _gameStates;
};

