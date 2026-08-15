// include/BullRunStrategy.h
#pragma once
#include "PriceStrategy.h"
#include <cstdlib>

class BullRunStrategy : public PriceStrategy {
public:
    double nextPrice(double currentPrice) override {
        double change = (rand() % 150) / 100.0; // always positive, 0 to +1.5
        return currentPrice + change;
    }
};