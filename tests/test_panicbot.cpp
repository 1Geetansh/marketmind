#include <iostream>
#include "PanicBot.h"

int main() {
    // Create a PanicBot with $1000 cash
    PanicBot bot("PanicBot", 1000.0);

    // A list of fake prices — includes a tiny drop, a bigger drop, and some rises
    double testPrices[] = { 50.0, 50.0, 49.99, 45.0, 46.0, 46.0, 44.5 };

    for (double price : testPrices) {
        Action action = bot.decideAction(price);

        std::cout << "Price: $" << price << " -> ";
        if (action == Action::BUY) std::cout << "BUY\n";
        else if (action == Action::SELL) std::cout << "SELL (panicking over the drop)\n";
        else std::cout << "HOLD\n";
    }

    return 0;
}