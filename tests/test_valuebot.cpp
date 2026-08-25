#include <iostream>
#include "ValueBot.h"

int main() {
    // Create a ValueBot with $1000 cash, believing fair value is $50
    ValueBot bot("ValueBot", 1000.0, 50.0);

    // A list of fake prices to test different situations
    double testPrices[] = { 50.0, 45.0, 40.0, 55.0, 60.0, 51.0 };

    for (double price : testPrices) {
        Action action = bot.decideAction(price);

        std::cout << "Price: $" << price << " -> ";
        if (action == Action::BUY) std::cout << "BUY (looks like a discount)\n";
        else if (action == Action::SELL) std::cout << "SELL (looks overpriced)\n";
        else std::cout << "HOLD (close enough to fair value)\n";
    }

    return 0;
}