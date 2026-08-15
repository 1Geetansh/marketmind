// include/CrashStrategy.h
#pragma once
#include "PriceStrategy.h"

class CrashStrategy : public PriceStrategy {
public:
    double nextPrice(double currentPrice) override {
        return currentPrice * 0.85; // sudden 15% drop each tick — this is your demo trigger
    }
};