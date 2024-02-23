#include "WinState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"

const std::string WinState::_winID = "WIN";

void WinState::_winToMain()
{
	TheGame::Instance()->getStateMachine()->pushState(new MainMenuState());
}

void WinState::_restartPlay()
{
	TheGame::Instance()->getStateMachine()->pushState(new PlayState());
}

void WinState::update() {
	//if (_loadingComplete&&!_gameObjects.empty()) {
	for (unsigned int i = 0, q = _gameObjects.size();i < q;i++) {
		_gameObjects[i]->update();
	}
	//}
}

void WinState::render() {
	TheTextureManager::Instance()->load("assets/oceanWin.png", "background", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->draw("background", 0, 0, 1024, 640, TheGame::Instance()->getRenderer());
	//if (_loadingComplete&&!_gameObjects.empty()) {
	for (unsigned int i = 0, q = _gameObjects.size();i < q;i++) {
		_gameObjects[i]->draw();
	}
	//}
}

bool WinState::onEnter() {
	TheSoundManager::Instance()->turnOff();
	TheSoundManager::Instance()->load("assets/winSound.ogg", "music4", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

	TheSoundManager::Instance()->playMusic("music4", -1);

	// parse the state
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", _winID, &_gameObjects, &_textureIDList);
	_callbacks.push_back(0);
	_callbacks.push_back(_winToMain);
	_callbacks.push_back(_restartPlay);
	// set the callbacks for menu items
	setCallbacks(_callbacks);

	_loadingComplete = true;

	std::cout << "entering PauseState\n";
	return true;
}

bool WinState::onExit() {
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

void WinState::setCallbacks(const std::vector<Callback>& callbacks)
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