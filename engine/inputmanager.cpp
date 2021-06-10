//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "headers/InputManager.h"
#include "globals.h"

void InputManager::beginNewFrame() {
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
    this->_mousePressedButtons.clear();
    this->_mouseReleasedButtons.clear();
}

void InputManager::keyDownEvent(const SDL_Event &event) {
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

void InputManager::keyUpEvent(const SDL_Event &event) {
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

void InputManager::mouseDownEvent(const SDL_Event &event) {
    this->_mousePressedButtons[event.button.button] = true;
    this->_mouseHeldButtons[event.button.button] = true;
}

void InputManager::mouseUpEvent(const SDL_Event &event) {
    this->_mouseReleasedButtons[event.button.button] = true;
    this->_mouseHeldButtons[event.button.button] = false;
}

void InputManager::mouseMovedEvent(const SDL_Event &event) {
    globals::MOUSEPOSITION_X = event.motion.x;
    globals::MOUSEPOSITION_Y = event.motion.y;
}

bool InputManager::wasKeyPressed(SDL_Scancode key) {
    return this->_pressedKeys[key];
}

bool InputManager::wasKeyReleased(SDL_Scancode key) {
    return this->_releasedKeys[key];
}

bool InputManager::isKeyHeld(SDL_Scancode key) {
    return this->_heldKeys[key];
}

bool InputManager::wasMouseButtonPressed(Uint8 button) {
    return this->_mousePressedButtons[button];
}

bool InputManager::wasMouseButtonReleased(Uint8 button) {
    return this->_mouseReleasedButtons[button];
}

bool InputManager::isMouseButtonHeld(Uint8 button) {
    return this->_mouseHeldButtons[button];
}