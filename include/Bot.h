#pragma once
#include <string>

enum class Action { BUY, SELL, HOLD };

class Bot {
protected:
    std::string name;
    double cash;

public:
    Bot(std::string botName, double startingCash)
        : name(botName), cash(startingCash) {}

    virtual ~Bot() = default;

    virtual Action decideAction(double currentPrice) = 0;

    std::string getName() const { return name; }
};