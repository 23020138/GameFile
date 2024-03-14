#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"
#include <assert.h>

const std::string MainMenuState::_menuID = "MENU";

void MainMenuState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		_menuToPlay();
	}
	if (!_gameObjects.empty()) {
		for (unsigned int i = 0; i < _gameObjects.size(); i++)
		{
			if (_gameObjects[i] != 0) {
				_gameObjects[i]->update();
			}
		}
	}
}

void MainMenuState::render() {
	//if (_loadingComplete && !_gameObjects.empty()) {

	TheTextureManager::Instance()->load("assets/menuGround.png", "background", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->draw("background", 0, 0, 1024, 640, TheGame::Instance()->getRenderer());

	if(!_gameObjects.empty()){
		for (unsigned int i = 0; i < _gameObjects.size(); i++)
		{
			_gameObjects[i]->draw();
		}
	}
}

bool MainMenuState::onEnter() {
	TheSoundManager::Instance()->turnOff();
	TheSoundManager::Instance()->load("assets/cup_song.ogg", "music1", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

	TheSoundManager::Instance()->playMusic("music1", -1);

	// parse the state
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", _menuID, &_gameObjects,&_textureIDList);
	_callbacks.push_back(0); //pushback 0 callbackID start from 1
	_callbacks.push_back(_menuToPlay);
	_callbacks.push_back(_exitFromMenu);

	 //set the callbacks for menu items
	setCallbacks(_callbacks);

	_loadingComplete = true;
	std::cout << "entering MenuState\n";
	return true;
}

bool MainMenuState::onExit() {
	_exiting = true;

	if (!_gameObjects.empty()) {
		for (int i = 0; i < _gameObjects.size(); i++)
		{
			_gameObjects[i]->clean();
			delete _gameObject[i];
		}
	}
	//if (_loadingComplete && !_gameObjects.empty())
	//if (!_gameObjects.empty())
	//{
		//_gameObjects.back()->clean();
	//}
	_gameObjects.clear();
	
	 // clear the texture manager
	for (int i = 0; i < _textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(_textureIDList[i]);
	}

	TheInputHandler::Instance()->reset();

	std::cout << "exiting MenuState\n";
	return true;
}

void MainMenuState::_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->pushState(new PlayState());
}

void MainMenuState::_exitFromMenu()
{
	TheGame::Instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	if (!_gameObjects.empty()) {
		// go through the game objects
		for (int i = 0; i < _gameObjects.size(); i++)
		{
			//if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(_gameObjects[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}
