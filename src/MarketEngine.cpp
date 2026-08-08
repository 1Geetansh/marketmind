#include "MarketEngine.h"

MarketEngine* MarketEngine::instance = nullptr;

MarketEngine::MarketEngine(double startingPrice) : currentPrice(startingPrice) {}

MarketEngine* MarketEngine::getInstance(double startingPrice) {
    if (instance == nullptr) {
        instance = new MarketEngine(startingPrice);
    }
    return instance;
}

void MarketEngine::subscribe(Observer* obs) {
    observers.push_back(obs);
}

void MarketEngine::setStrategy(std::unique_ptr<PriceStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

void MarketEngine::tick() {
    if (!strategy) return; // safety check — no strategy set yet, do nothing

    currentPrice = strategy->nextPrice(currentPrice);

    // notify every subscribed bot that the price changed
    for (Observer* obs : observers) {
        obs->onPriceUpdate(currentPrice);
    }
}

double MarketEngine::getCurrentPrice() const {
    return currentPrice;
}