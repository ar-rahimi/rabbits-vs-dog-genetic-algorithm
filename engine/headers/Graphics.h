//
// Created by Ahmad Rahimi on 9/5/17.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();

    SDL_Surface* loadImage(const std::string &filePath);
    /* void blitSurface
     * Drawing images on a screen
     */
    void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, double angle = 0);

    /* void flip
     * Render everything on screen
     */
    void flip();

    /* void clear
     * Clear the screen
     */
    void clear();

    /* SDL_Renderer* getRenderer
     * Returns the renderer
     */
    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    int _rendercount;
    std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif //SHOOTER_GRAPHICS_H
