#include "UpgradeManager.hpp"

int UpgradeManager::SpeedPrice() const {
    return 25 + speedLevel * 20;
}

int UpgradeManager::RangePrice() const {
    return 30 + rangeLevel * 25;
}

int UpgradeManager::SpeedLevel() const {
    return speedLevel;
}

int UpgradeManager::RangeLevel() const {
    return rangeLevel;
}

bool UpgradeManager::BuySpeed(Player& player) {
    const int price = SpeedPrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    player.movementSpeed += 0.5f;
    ++speedLevel;
    return true;
}

bool UpgradeManager::BuyRange(Player& player) {
    const int price = RangePrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    player.pickupRange += 0.5f;
    ++rangeLevel;
    return true;
}

void UpgradeManager::Reset() {
    speedLevel = 0;
    rangeLevel = 0;
}
