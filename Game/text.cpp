//
// Created by Ahmad Rahimi on 12/14/17.
//

#include "Text.h"

Text::Text(CRect bounds, std::string text, int r, int g, int b, int angle) : bounds(bounds), text(text), r(r), g(g), b(b), angle(angle){

}

void Text::draw() {
    RenderManager::getRenderManager()->DrawText(text, bounds.getX(), bounds.getY(), bounds.getRect().w, bounds.getRect().h, r, g, b);
}
