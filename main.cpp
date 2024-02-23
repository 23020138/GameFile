#include <SDL.h>
#include <iostream>
#include "Game.h"

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

Game* g_game = 0;

int main(int argc, char** argv) {
	Uint32 frameStart, frameTime;
	std::cout << "game init attempt...\n";
	if (TheGame::Instance()->init("Space X Combat", 50, 50, 1024, 640, false)) {
		std::cout << "Game init success!\n";
		while (TheGame::Instance()->running()) {
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
			else {
				SDL_Delay((int)(DELAY_TIME));
			}
		}
	}
	else {
		std::cout << "Game init failure - " << SDL_GetError() << endl;
		return -1;
	}
	std::cout << "Game closing...\n";
	TheGame::Instance()->clean();
	return 0;
}