//
// Created by Ahmad Rahimi on 12/17/17.
//

#include <SDL_render.h>
#include <headers/RenderManager.h>
#include <Helper.h>
#include "GameObject.h"

int GameObject::index;

GameObject::GameObject(int x, int y, int w, int h) :
        x{x}, y{y} {
    rect = CRect(x, y, w, h);
    GameObject::index++;
    id = index;
}

void GameObject::draw() {
    if (this->visible) {
        SDL_RenderFillRect(RenderManager::getRenderManager()->getRenderer(), &this->rect.getRect());
    }
}

bool GameObject::isVisible() const {
    return visible;
}
