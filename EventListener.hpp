#pragma once

struct EventListener {
    char GetEvent(); 
    void GetMovement(float& dx, float& dz) const;
};