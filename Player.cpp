#include "Player.hpp"

Player::Player() : position(), coins(0), movementSpeed(1.0f), pickupRange(1.5f) {}

Player::Player(const Point& _position, int _coins, float _speed, float _range)
    : position(_position), coins(_coins), movementSpeed(_speed), pickupRange(_range) {}

Player::Player(const Player& other)
    : position(other.position), coins(other.coins),
      movementSpeed(other.movementSpeed), pickupRange(other.pickupRange) {}

Player& Player::operator=(const Player& other) {
    position = other.position;
    coins = other.coins;
    movementSpeed = other.movementSpeed;
    pickupRange = other.pickupRange;
    return *this;
}

bool Player::operator==(const Player& other) const {
    return position == other.position && coins == other.coins &&
           movementSpeed == other.movementSpeed && pickupRange == other.pickupRange;
}

std::istream& operator>>(std::istream& in, Player& player) {
    Point position;
    int coins;
    float speed, range;
    in >> position >> coins >> speed >> range;
    player = Player(position, coins, speed, range);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << player.position << " " << player.coins << " "
        << player.movementSpeed << " " << player.pickupRange;
    return out;
}

void Player::Move(float dx, float dz, float mapWidth, float mapDepth) {}
void Player::BuySpeed() {}
void Player::BuyRange() {}