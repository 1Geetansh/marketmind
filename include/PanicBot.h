#pragma once
#include "Bot.h"

class PanicBot : public Bot {
private:
    double previousPrice; // the last price PanicBot saw
    bool hasSeenPrice;    // tracks whether we have a previous price yet

public:
    PanicBot(std::string botName, double startingCash)
        : Bot(botName, startingCash), previousPrice(0.0), hasSeenPrice(false) {}

    Action decideAction(double currentPrice) override;
};