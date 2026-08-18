#pragma once
#include "Bot.h"

class ValueBot : public Bot {
private:
    double fairValue; // the price ValueBot thinks the stock is "really" worth

public:
    ValueBot(std::string botName, double startingCash, double initialFairValue)
        : Bot(botName, startingCash), fairValue(initialFairValue) {}

    Action decideAction(double currentPrice) override;
};