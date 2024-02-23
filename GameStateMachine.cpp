#include "GameStateMachine.h"
#include <iostream>

void GameStateMachine::pushState(GameState* pState) {
	_gameStates.push_back(pState);
	_gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
	if (!_gameStates.empty()) {
		_gameStates.back()->onExit();
		_gameStates.pop_back();
	}
	_gameStates.back()->resume();
}

void GameStateMachine::changeState(GameState* pState) {
	if (!_gameStates.empty()) {
		if (_gameStates.back()->getStateID() == pState->getStateID()) {
			return;
		}
		if (_gameStates.back()->onExit()) {
			delete _gameStates.back();
			_gameStates.pop_back();
		}
	}

	// push back new state
	_gameStates.push_back(pState);

	//initialise it
	_gameStates.back()->onEnter();
}

void GameStateMachine::update() {
	if (!_gameStates.empty()) {
		_gameStates.back()->update();
	}
}

void GameStateMachine::render() {
	if (!_gameStates.empty()) {
		_gameStates.back()->render();
	}
}

void GameStateMachine::clean()
{
	if (!_gameStates.empty())
	{
		_gameStates.back()->onExit();

		delete _gameStates.back();

		_gameStates.clear();
	}
}