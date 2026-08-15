// src/main.cpp — updated
#include <iostream>
#include "MarketEngine.h"
#include "NormalStrategy.h"
#include "CrashStrategy.h"
#include "Observer.h"

// Temporary dummy bot just to test the Observer connection
class TestObserver : public Observer {
public:
    void onPriceUpdate(double newPrice) override {
        std::cout << "[TestObserver got notified] New price: " << newPrice << "\n";
    }
};

int main() {
    MarketEngine* engine = MarketEngine::getInstance(100.0);
    engine->setStrategy(std::make_unique<NormalStrategy>());

    TestObserver bot;
    engine->subscribe(&bot);   // this bot is now "listening"

    std::cout << "--- Normal market (bot should react automatically) ---\n";
    for (int i = 0; i < 5; i++) {
        engine->tick();  // notice: we're NOT manually printing price anymore
    }

    std::cout << "--- Crash triggered ---\n";
    engine->setStrategy(std::make_unique<CrashStrategy>());
    for (int i = 0; i < 3; i++) {
        engine->tick();
    }

    return 0;
}