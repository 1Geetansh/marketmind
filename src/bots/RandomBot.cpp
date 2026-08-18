#include "RandomBot.h"

RandomBot::RandomBot(std::string botName, double startingCash)
    : Bot(botName, startingCash),
      rng(std::random_device{}()),   // seed the generator with true randomness
      distribution(0, 2)             // will produce 0, 1, or 2
{}

Action RandomBot::decideAction(double currentPrice) {
    // currentPrice isn't used — RandomBot doesn't care about the market at
    // all, it just rolls the dice. The parameter is still required because
    // it must match Bot's virtual function signature exactly.
    (void)currentPrice; // silences "unused parameter" compiler warnings

    int roll = distribution(rng);

    switch (roll) {
        case 0: return Action::BUY;
        case 1: return Action::SELL;
        default: return Action::HOLD;
    }
}
