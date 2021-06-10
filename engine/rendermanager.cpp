//
// Created by Ahmad Rahimi on 9/25/17.
//

#include <SDL.h>
#include "headers/RenderManager.h"
#include <SDL_image.h>
#include <iostream>

RenderManager* RenderManager::renderManager;

RenderManager::RenderManager() {
    SDL_CreateWindowAndRenderer(1280,720,0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Shooter");
    SDL_Surface* surface = SDL_GetWindowSurface(this->_window);
    _rendercount = 0;
    TTF_Init();
}

RenderManager::~RenderManager(){
    SDL_DestroyWindow(this->_window);
}

SDL_Surface* RenderManager::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0) {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
}

void RenderManager::DrawText(const std::string text, const int x, const int y, int width, int height, const double angle, Uint8 r, Uint8 g, Uint8 b)
{
    if (font == NULL || fontHeight != height) {
        fontHeight = height;
        //TTF_CloseFont(font);
        font = TTF_OpenFont(std::string{ "../content/OpenSans-Bold.ttf" }.c_str(), 12);
    }
    TTF_SizeText(font, text.c_str(), &width, &height);
    SDL_Color color = { r, g, b };
    SDL_Surface* sMessage = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(this->_renderer, sMessage);
    SDL_FreeSurface(sMessage);

    SDL_Rect messageRect;
    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = width;
    messageRect.h = height;

    this->blitSurface(message, NULL, &messageRect, angle);
    SDL_DestroyTexture(message);
}

void RenderManager::blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle, double angle) {
    int resp = SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, destinationRectangle, angle, NULL, SDL_FLIP_NONE);
//    std::cout << resp << std::endl;
    if (resp != 0) {
        std::cout << SDL_GetError() << std::endl;
    }

////    _rendercount += 1;
//    std::cout << std::to_string(_rendercount) << std::endl;
}

RenderManager* RenderManager::getRenderManager() {
    if(!renderManager){
        renderManager = new RenderManager;
    }
    return renderManager;
}

void RenderManager::flip(){
    SDL_RenderPresent(this->_renderer);
}

void RenderManager::clear() {
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* RenderManager::getRenderer() const {
    return this->_renderer;
}

