//
// Created by Ahmad Rahimi on 12/13/17.
//

#include "headers/CRect.h"

void CRect::setX(float x) {
    rect.x = x;
    CRect::x = x;
}

void CRect::setY(float y) {
    rect.y = y;
    CRect::y = y;
}

void CRect::setW(float w) {
    rect.w = w;
    CRect::w = w;
}

void CRect::setH(float h) {
    rect.h = h;
    CRect::h = h;
}

const SDL_Rect &CRect::getRect() const {
    return rect;
}

CRect::CRect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){
    this->rect = SDL_Rect();
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
}

int CRect::rectTileY() {
    return rect.y - (this->getRect().y % 20);
}

int CRect::rectTileX() {
    return rect.x - (this->getRect().x % 20);
}

float CRect::getX() const {
    return x;
}

float CRect::getY() const {
    return y;
}

int CRect::getOriginY() const {
    return (this->y + (this->h / 2));
}

int CRect::getOriginX() const {
    return (this->x + (this->w / 2));
}

bool CRect::collides(CRect rect) {
    return (rect.x > this->x && rect.x < (this->x + this->w) && rect.y > this->rect.y && rect.y < this->rect.y + this->rect.w);
}
