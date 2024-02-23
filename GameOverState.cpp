#include "GameOverState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"

const std::string GameOverState::_gameOverID = "GAMEOVER";

void GameOverState::_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->pushState(new MainMenuState());
}

void GameOverState::_restartPlay()
{
	TheGame::Instance()->getStateMachine()->pushState(new PlayState());
}

void GameOverState::update() {
	//if (_loadingComplete&&!_gameObjects.empty()) {
		for (unsigned int i = 0, q = _gameObjects.size();i < q;i++) {
			_gameObjects[i]->update();
		}
	//}
}

void GameOverState::render() {
	TheTextureManager::Instance()->load("assets/ocean_over.png", "background", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->draw("background", 0, 0, 1024, 640, TheGame::Instance()->getRenderer());
	//if (_loadingComplete&&!_gameObjects.empty()) {
		for (unsigned int i = 0, q = _gameObjects.size();i < q;i++) {
			_gameObjects[i]->draw();
		}
	//}
}

bool GameOverState::onEnter() {
	TheSoundManager::Instance()->turnOff();
	TheSoundManager::Instance()->load("assets/rickSound.ogg", "music3", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

	TheSoundManager::Instance()->playMusic("music3", -1);
	// parse the state
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", _gameOverID, &_gameObjects,&_textureIDList);
	_callbacks.push_back(0);
	_callbacks.push_back(_gameOverToMain);
	_callbacks.push_back(_restartPlay);
	// set the callbacks for menu items
	setCallbacks(_callbacks);

	_loadingComplete = true;

	std::cout << "entering PauseState\n";
	return true;
}

bool GameOverState::onExit() {
	//if (_loadingComplete&&!_gameObjects.empty()) {
	if (!_gameObjects.empty()) {
		for (int i = 0, q = _gameObjects.size();i < q;i++) {
			_gameObjects[i]->clean();
			delete _gameObjects[i];
		}
		_gameObjects.clear();
	}

	// clear the texture manager
	for (int i = 0; i < _textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(_textureIDList[i]);
	}

	TheInputHandler::Instance()->reset();

	std::cout << "exiting GameOverState!\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<MenuButton*>(_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}