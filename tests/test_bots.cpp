#include "MomentumBot.h"
#include "RandomBot.h"
#include <iostream>
#include <vector>

// Turns an Action enum into readable text for printing.
std::string actionToString(Action a) {
    switch (a) {
        case Action::BUY:  return "BUY";
        case Action::SELL: return "SELL";
        case Action::HOLD: return "HOLD";
    }
    return "UNKNOWN";
}

int main() {
    // A fake sequence of prices: rises, then falls, then rises again.
    // This lets us visually confirm MomentumBot reacts correctly to trends.
    std::vector<double> fakePrices = {
        100.0, 101.0, 103.0, 106.0,  // uptrend
        104.0, 101.0, 98.0,          // downtrend
        99.0, 100.0, 102.0           // recovering
    };

    MomentumBot momentumBot("MomentumBot", 1000.0);
    RandomBot randomBot("RandomBot", 1000.0);

    std::cout << "Price   | MomentumBot | RandomBot\n";
    std::cout << "--------|-------------|----------\n";

    for (double price : fakePrices) {
        Action momentumAction = momentumBot.decideAction(price);
        Action randomAction   = randomBot.decideAction(price);

        std::cout << price << "\t| "
                  << actionToString(momentumAction) << "\t\t| "
                  << actionToString(randomAction) << "\n";
    }

    return 0;
}
