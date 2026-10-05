#include "Player.hpp"

void Player::Move(float dx, float dz, float mapWidth, float mapDepth) {
    position.x += dx * movementSpeed;
    position.z += dz * movementSpeed;

    if (position.x < 0) position.x = 0;
    if (position.z < 0) position.z = 0;
    if (position.x > mapWidth - 1) position.x = mapWidth - 1;
    if (position.z > mapDepth - 1) position.z = mapDepth - 1;
}

void Player::BuySpeed() {
    if (coins >= 10) { coins -= 10; movementSpeed += 0.5f; }
}

void Player::BuyRange() {
    if (coins >= 10) { coins -= 10; pickupRange += 0.5f; }
}