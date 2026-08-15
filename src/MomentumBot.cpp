#include "MomentumBot.h"

// Call the base class constructor (Bot) with the name and starting cash.
// This is required because Bot doesn't have a default constructor —
// it needs a name and starting cash to be built.
MomentumBot::MomentumBot(std::string botName, double startingCash)
    : Bot(botName, startingCash) {}

Action MomentumBot::decideAction(double currentPrice) {
    // Step 1: record this new price in our history.
    priceHistory.push_back(currentPrice);

    // Step 2: if history gets too long, drop the oldest price.
    // This keeps memory bounded and makes sure we're only reacting to
    // *recent* trends, not the entire history of the simulation.
    if (priceHistory.size() > HISTORY_SIZE) {
        priceHistory.pop_front();
    }

    // Step 3: if we don't have at least 2 prices yet, we can't detect a
    // trend, so just wait and watch.
    if (priceHistory.size() < 2) {
        return Action::HOLD;
    }

    // Step 4: compare the oldest price we have to the newest price.
    // If price has gone up since then -> uptrend -> BUY.
    // If price has gone down since then -> downtrend -> SELL.
    // If it's flat -> HOLD.
    double oldestPrice = priceHistory.front();
    double newestPrice = priceHistory.back();

    if (newestPrice > oldestPrice) {
        return Action::BUY;
    } else if (newestPrice < oldestPrice) {
        return Action::SELL;
    } else {
        return Action::HOLD;
    }
}
