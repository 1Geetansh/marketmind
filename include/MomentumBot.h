#pragma once
#include "Bot.h"
#include <deque>

// MomentumBot follows "the trend is my friend": it buys when the price has
// been rising recently, and sells when the price has been falling recently.
// It doesn't try to predict anything fancy — it just reacts to the last
// couple of price observations.
class MomentumBot : public Bot {
private:
    // Keeps the most recent prices we've seen, oldest at the front.
    // We only need a handful of recent prices to detect a trend, so we cap
    // the size of this deque (see decideAction()).
    std::deque<double> priceHistory;

    // How many recent prices we keep around before we start dropping old ones.
    static constexpr size_t HISTORY_SIZE = 3;

public:
    MomentumBot(std::string botName, double startingCash);

    // Looks at recent price history and decides BUY / SELL / HOLD.
    Action decideAction(double currentPrice) override;
};
