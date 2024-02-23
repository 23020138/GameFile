#pragma once

#include <SDL.h>
#include "GameStateMachine.h"
#include <vector>
#include "GameObject.h"

class Game
{
public:
	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);

	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();

	// a function to access the private running variable 
	bool running() { return _running; }

	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	SDL_Renderer* getRenderer() const { return _renderer; }
	SDL_Window* getWindow() const { return _window; }
	GameStateMachine* getStateMachine() { return _gameStateMachine; }

	void setPlayerLives(int lives) { _playerLives = lives; }
	int getPlayerLives() { return _playerLives; }

	void setCurrentLevel(int currentLevel);
	const int getCurrentLevel() { return _currentLevel; }

	void setNextLevel(int nextLevel) { _nextLevel = nextLevel; }
	const int getNextLevel() { return _nextLevel; }

	void setLevelComplete(bool levelComplete) { _bLevelComplete = levelComplete; }
	const bool getLevelComplete() { return _bLevelComplete; }

	bool changingState() { return _changingState; }
	void changingState(bool cs) { _changingState = cs; }

	int getGameWidth() const { return _width; }
	int getGameHeight() const { return _height; }
	float getScrollSpeed() { return _scrollSpeed; }

	std::vector<std::string> getLevelFiles() { return _levelFiles; }

	int getNumLevels() { return _levelFiles.size(); }

private:
	int _width, _height;
	float _scrollSpeed;
	bool _changingState;

	int _playerLives;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	int _currentFrame;
	bool _running;
	std::vector<GameObject*> _gameObjects;

	GameStateMachine* _gameStateMachine;

	int _currentLevel;
	int _nextLevel;
	bool _bLevelComplete;

	std::vector<std::string> _levelFiles;

	Game();
	~Game();
	static Game* s_pInstance;

	Game(const Game&);
	Game& operator=(const Game&);
};

typedef Game TheGame;
