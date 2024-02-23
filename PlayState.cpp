#include <iostream>
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Level.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include "WinState.h"

const std::string PlayState::_playID = "PLAY";

void PlayState::update() {
	//if (_loadingComplete && !_exiting) {
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_K)) // k key on the keyboard
		{
			TheGame::Instance()->getStateMachine()->pushState(new PauseState());
		}
		
		TheBulletHandler::Instance()->updateBullets();

		if (TheGame::Instance()->getPlayerLives() == 0)
		{
			TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
		}

	if (pLevel != 0) {
		pLevel->update();
	}
	//}
}

void PlayState::render() {
	if (pLevel != 0) {
		pLevel->render();
	}

	for (int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
	{
		TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
	}

	TheBulletHandler::Instance()->drawBullets();
}

bool PlayState::onEnter() {
	TheSoundManager::Instance()->turnOff();
	TheSoundManager::Instance()->load("assets/cup_song.ogg", "music1", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

	TheSoundManager::Instance()->playMusic("music1", -1);

	TheGame::Instance()->setPlayerLives(3);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());

	TheTextureManager::Instance()->load("assets/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/lives.png", "lives", TheGame::Instance()->getRenderer());

	if (pLevel != 0) _loadingComplete = true;

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit() {
	_exiting = true;

	TheInputHandler::Instance()->reset();
	TheBulletHandler::Instance()->clearBullets();

	std::cout << "exiting PlayState\n";
	return true;
}