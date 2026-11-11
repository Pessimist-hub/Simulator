#pragma once

#include "Player.hpp"

class UpgradeManager {
public:
    int SpeedPrice() const;
    int RangePrice() const;
    int SpeedLevel() const;
    int RangeLevel() const;

    bool BuySpeed(Player& player);
    bool BuyRange(Player& player);
    void Reset();

private:
    int speedLevel = 0;
    int rangeLevel = 0;
};
