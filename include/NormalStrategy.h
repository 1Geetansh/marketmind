// include/NormalStrategy.h
#pragma once
#include "PriceStrategy.h"
#include <cstdlib>

class NormalStrategy : public PriceStrategy {
public:
    double nextPrice(double currentPrice) override {
        double change = ((rand() % 200) - 100) / 100.0; // random value between -1.0 and +1.0
        return currentPrice + change;
    }
};