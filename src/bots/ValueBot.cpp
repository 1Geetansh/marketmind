#include "ValueBot.h"

Action ValueBot::decideAction(double currentPrice) {
    // How far the current price is from what ValueBot considers "fair"
    double threshold = fairValue * 0.05; // 5% wiggle room

    if (currentPrice < fairValue - threshold) {
        // Price is meaningfully BELOW fair value — looks like a discount, buy it
        return Action::BUY;
    } else if (currentPrice > fairValue + threshold) {
        // Price is meaningfully ABOVE fair value — looks overpriced, sell it
        return Action::SELL;
    } else {
        // Price is close enough to fair value — do nothing
        return Action::HOLD;
    }
}