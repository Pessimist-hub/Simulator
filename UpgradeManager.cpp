#include "UpgradeManager.hpp"

int UpgradeManager::SpeedPrice() const {
    return 25 + speedLevel * 20;
}

int UpgradeManager::RangePrice() const {
    return 30 + rangeLevel * 20;
}

int UpgradeManager::CoinPrice() const {
    return 45 + coinLevel * 35;
}

int UpgradeManager::StaminaPrice() const {
    return 35 + staminaLevel * 25;
}

int UpgradeManager::RegenerationPrice() const {
    return 40 + regenerationLevel * 30;
}

int UpgradeManager::SpeedLevel() const {
    return speedLevel;
}

int UpgradeManager::RangeLevel() const {
    return rangeLevel;
}

int UpgradeManager::CoinLevel() const {
    return coinLevel;
}

int UpgradeManager::StaminaLevel() const {
    return staminaLevel;
}

int UpgradeManager::RegenerationLevel() const {
    return regenerationLevel;
}

bool UpgradeManager::BuySpeed(Player& player) {
    const int price = SpeedPrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    player.movementSpeed += 0.45f;
    ++speedLevel;
    return true;
}

bool UpgradeManager::BuyRange(Player& player) {
    const int price = RangePrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    player.pickupRange += 0.35f;
    ++rangeLevel;
    return true;
}

bool UpgradeManager::BuyCoins(Player& player) {
    const int price = CoinPrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    ++player.coinMultiplier;
    ++coinLevel;
    return true;
}

bool UpgradeManager::BuyStamina(Player& player) {
    const int price = StaminaPrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    player.maxStamina += 25.0f;
    player.stamina += 25.0f;
    ++staminaLevel;
    return true;
}

bool UpgradeManager::BuyRegeneration(Player& player) {
    const int price = RegenerationPrice();
    if (player.coins < price) {
        return false;
    }

    player.coins -= price;
    player.staminaRegeneration += 5.0f;
    ++regenerationLevel;
    return true;
}

void UpgradeManager::Reset() {
    speedLevel = 0;
    rangeLevel = 0;
    coinLevel = 0;
    staminaLevel = 0;
    regenerationLevel = 0;
}
