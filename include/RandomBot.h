#pragma once
#include "Bot.h"
#include <random>

// RandomBot ignores the price entirely and just picks BUY, SELL, or HOLD
// at random. It exists as a "dumb" baseline — if the smarter bots
// (MomentumBot, ValueBot, etc.) can't consistently beat RandomBot, that's
// a sign something's wrong with their strategy.
class RandomBot : public Bot {
private:
    // A random number generator and a distribution that picks one of the
    // three actions with equal probability. These are stored as member
    // variables (not created fresh each call) so the generator's internal
    // state persists properly between calls — recreating it every time
    // would give worse randomness.
    std::mt19937 rng;
    std::uniform_int_distribution<int> distribution;

public:
    RandomBot(std::string botName, double startingCash);

    Action decideAction(double currentPrice) override;
};
