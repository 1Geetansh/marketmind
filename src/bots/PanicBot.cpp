#include "PanicBot.h"

Action PanicBot::decideAction(double currentPrice) {
    // On the very first price we ever see, there's nothing to compare to yet
    if (!hasSeenPrice) {
        previousPrice = currentPrice;
        hasSeenPrice = true;
        return Action::HOLD;
    }

    Action decision;

    if (currentPrice < previousPrice) {
        // Price dropped by ANY amount, however small — panic and sell everything
        decision = Action::SELL;
    } else {
        // Price stayed the same or went up — no reason to panic
        decision = Action::HOLD;
    }

    // Remember this price for next time
    previousPrice = currentPrice;

    return decision;
}