#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL.h>

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer){
    if (fileName.substr(0, 7) != "assets/") {
        fileName = "assets/" + fileName;
    }
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if (pTempSurface == 0){
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    // everything went ok, add the texture to our list
    if (pTexture != 0){
        _textureMap[id] = pTexture;
        return true;
    }
    // reaching here means something went wrong
    return false;
}

// static image
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    // the fourth parameter - angle, the fifth - the center point
    SDL_RenderCopyEx(pRenderer, _textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

// animated image
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    // set the alpha of the texture and pass in the angle
    SDL_SetTextureAlphaMod(_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, _textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id) {
    _textureMap.erase(id);
}

void TextureManager::clearTextureMap() {
    _textureMap.clear();
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, _textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}