#pragma once

#include "Player.hpp"

class UpgradeManager {
public:
    int SpeedPrice() const;
    int RangePrice() const;
    int CoinPrice() const;
    int StaminaPrice() const;
    int RegenerationPrice() const;
    int SpeedLevel() const;
    int RangeLevel() const;
    int CoinLevel() const;
    int StaminaLevel() const;
    int RegenerationLevel() const;

    bool BuySpeed(Player& player);
    bool BuyRange(Player& player);
    bool BuyCoins(Player& player);
    bool BuyStamina(Player& player);
    bool BuyRegeneration(Player& player);
    void Reset();

private:
    int speedLevel = 0;
    int rangeLevel = 0;
    int coinLevel = 0;
    int staminaLevel = 0;
    int regenerationLevel = 0;
};
