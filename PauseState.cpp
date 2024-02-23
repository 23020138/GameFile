#include "PauseState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"

const std::string PauseState::_pauseID = "PAUSE";

void PauseState::_pauseToMain() {
	TheGame::Instance()->getStateMachine()->pushState(new MainMenuState());
}

void PauseState::_resumePlay() {
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update() {
	TheSoundManager::Instance()->resumeMusic();
	//if (_loadingComplete && !_gameObjects.empty()) {
	if(!_gameObjects.empty()){
		for (int i = 0, q = _gameObjects.size();i < q;i++) {
			_gameObjects[i]->update();
		}
	}
}

void PauseState::render() {
	TheSoundManager::Instance()->pauseMusic();
	TheTextureManager::Instance()->load("assets/pauseGround.png", "background", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->draw("background", 0, 0, 1024, 640, TheGame::Instance()->getRenderer());
	//if (_loadingComplete && !_gameObjects.empty()) {
	if (!_gameObjects.empty()) {
		for (unsigned int i = 0, q = _gameObjects.size();i < q;i++) {
			_gameObjects[i]->draw();
		}
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", _pauseID, &_gameObjects, &_textureIDList);
	_callbacks.push_back(0);
	_callbacks.push_back(_pauseToMain);
	_callbacks.push_back(_resumePlay);

	setCallbacks(_callbacks);
	_loadingComplete = true;

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	//if (_loadingComplete && !_gameObjects.empty()) {
	if (!_gameObjects.empty()) {
		for (int i = 0, q = _gameObjects.size(); i < q; i++)
		{
			_gameObjects[i]->clean();
		}
		_gameObjects.clear();
	}

	// clear the texture manager
	for (int i = 0; i < _textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(_textureIDList[i]);
	}

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();

	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	if (!_gameObjects.empty()) {
		for (unsigned int i = 0; i < _gameObjects.size(); i++)
		{
			// if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(_gameObjects[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}