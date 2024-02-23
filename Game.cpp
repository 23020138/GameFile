#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Player.h"
#include "ScrollingBackground.h"
#include "SoundManager.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"
#include "Level2Boss.h"
#include "GameOverState.h"
#include "WinState.h"
#include <iostream>

Game* Game::s_pInstance = 0;

Game::Game() :
    _window(0),
    _renderer(0),
    _running(false),
    _gameStateMachine(0),
    _playerLives(3),
    _scrollSpeed(0.8),
    _bLevelComplete(false),
    _changingState(false)
{
    // add some level files to an array
    _levelFiles.push_back("assets/map1.tmx");
    _levelFiles.push_back("assets/map2.tmx");

    // start at this level
    _currentLevel = 1;
}

Game::~Game() {
    _renderer = 0;
    _window = 0;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
    int flags = 0;
    _width = width; _height = height;

    if (fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // attempt to initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL init success\n";
        // init the window
        _window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (_window != 0) // window init success
        {
            std::cout << "window creation success\n";
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED); 
            if (_renderer != 0) // renderer init success
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false; // window init fail
        }

    }
    else
    {
        std::cout << "SDL init fail\n";
        return false; // SDL init fail
    }

    // add some sound effects - TODO move to better place
    TheSoundManager::Instance()->load("assets/cup_song.ogg", "music1", SOUND_MUSIC);
    TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
    TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

    TheSoundManager::Instance()->playMusic("music1", -1);

    // register the types for the game
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
    TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
    TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    TheGameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());
    TheGameObjectFactory::Instance()->registerType("Level2Boss", new Level2BossCreator());

    _gameStateMachine = new GameStateMachine();
    _gameStateMachine->pushState(new MainMenuState());

    _running = true;
    return true;
}

void Game::render(){
    SDL_RenderClear(_renderer); // clear the renderer to the draw color

    _gameStateMachine->render();

    SDL_RenderPresent(_renderer); // draw to the screen
}

void Game::clean() {
    std::cout << "cleaning game\n";
    TheInputHandler::Instance()->clean();

    _gameStateMachine->clean();
    delete _gameStateMachine;

    TheTextureManager::Instance()->clearTextureMap();

    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

void Game::handleEvents(){
    TheInputHandler::Instance()->update();
}

void Game::update() {
    _gameStateMachine->update();
}

void Game::quit() {
    _running = false;
}

void Game::setCurrentLevel(int currentLevel)
{
    _currentLevel = currentLevel;
    _gameStateMachine->pushState(new WinState());
    _bLevelComplete = false;
}