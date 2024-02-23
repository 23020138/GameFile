#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include <iostream>

class TextureManager{
public:
	static TextureManager* Instance() {
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id,SDL_Renderer* pRenderer);
	
	// static img
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// animated img
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer);

	void clearTextureMap();
	void clearFromTextureMap(std::string id);

	std::map<std::string, SDL_Texture*> getTextureMap() { return _textureMap; }

private:
	TextureManager() {}
	~TextureManager() {}

	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	std::map<std::string, SDL_Texture*> _textureMap;
	static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;