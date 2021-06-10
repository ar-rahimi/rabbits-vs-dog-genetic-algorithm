//
// Created by Ahmad Rahimi on 12/13/17.
//

#ifndef TOETS_CRECT_H
#define TOETS_CRECT_H


#include <SDL_rect.h>

class CRect {
private:
    float x,y,w,h;
    SDL_Rect rect;

public:
    float getX() const;

    float getY() const;

    CRect(float x, float y, float w, float h);
    CRect() = default;

    const SDL_Rect &getRect() const;

    void setX(float x);

    void setY(float y);

    int getOriginX() const;
    int getOriginY() const;

    void setW(float w);

    void setH(float h);

    int rectTileX();

    int rectTileY();

    bool collides(CRect rect);
};


#endif //TOETS_CRECT_H
