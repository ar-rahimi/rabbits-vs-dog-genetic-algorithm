//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

struct SDL_Window;
struct SDL_Renderer;

class RenderManager {
public:
    RenderManager();
    ~RenderManager();

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


    /* void DrawText
    * Draw text on screen
    */
    void DrawText(const std::string text, const int x, const int y, int width, int height, const double angle = 0,  Uint8 r = 255,  Uint8 g = 255,  Uint8 b = 255);

    /* SDL_Renderer* getRenderer
     * Returns the renderer
     */
    SDL_Renderer* getRenderer() const;

    static RenderManager* getRenderManager();


private:
    TTF_Font* font;
    int fontHeight = 0;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    int _rendercount;
    std::map<std::string, SDL_Surface*> _spriteSheets;
    static RenderManager *renderManager;
};
#endif //GRAPHICSMANAGER_H
