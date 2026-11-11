#include "Player.hpp"

#include <algorithm>
#include <cmath>

namespace {
constexpr float RadiansToDegrees = 57.29577951308232f;
}

Player::Player() : position(), coins(0), movementSpeed(1.0f), pickupRange(1.5f) {}

Player::Player(const Point& _position, int _coins, float _speed, float _range)
    : position(_position), coins(_coins), movementSpeed(_speed), pickupRange(_range) {}

Player::Player(const Player& other)
    : position(other.position), coins(other.coins),
      movementSpeed(other.movementSpeed), pickupRange(other.pickupRange),
      facingAngle(other.facingAngle), animationTime(other.animationTime),
      isMoving(other.isMoving) {}

Player& Player::operator=(const Player& other) {
    position = other.position;
    coins = other.coins;
    movementSpeed = other.movementSpeed;
    pickupRange = other.pickupRange;
    facingAngle = other.facingAngle;
    animationTime = other.animationTime;
    isMoving = other.isMoving;
    return *this;
}

bool Player::operator==(const Player& other) const {
    return position == other.position && coins == other.coins &&
           movementSpeed == other.movementSpeed && pickupRange == other.pickupRange;
}

bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}

std::istream& operator>>(std::istream& in, Player& player) {
    Point position;
    int coins;
    float speed, range;
    if (in >> position >> coins >> speed >> range) {
        player = Player(position, coins, speed, range);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << player.position << " " << player.coins << " "
        << player.movementSpeed << " " << player.pickupRange;
    return out;
}

void Player::Move(float dx, float dz, float mapWidth, float mapDepth, float deltaTime) {
    const float length = std::sqrt(dx * dx + dz * dz);
    if (length > 0.0f && deltaTime > 0.0f) {
        const float distance = movementSpeed * deltaTime;
        position.x += (dx / length) * distance;
        position.z += (dz / length) * distance;
        facingAngle = std::atan2(dx, dz) * RadiansToDegrees;
        animationTime += deltaTime;
        isMoving = true;
    } else {
        isMoving = false;
    }

    position.x = std::clamp(position.x, 0.0f, std::max(0.0f, mapWidth));
    position.z = std::clamp(position.z, 0.0f, std::max(0.0f, mapDepth));
}
void Player::BuySpeed() {}
void Player::BuyRange() {}