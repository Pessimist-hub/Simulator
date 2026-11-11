#include "EventListener.hpp"

#include <raylib.h>

char EventListener::GetEvent() { return ' '; }

void EventListener::GetMovement(float& dx, float& dz) const {
    dx = static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A));
    dz = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));
}