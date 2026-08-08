#pragma once
#include <vector>
#include <memory>
#include "Observer.h"
#include "PriceStrategy.h"

class MarketEngine {
private:
    static MarketEngine* instance;   // the ONE and only instance (Singleton)

    double currentPrice;
    std::vector<Observer*> observers;      // everyone "subscribed" to price updates
    std::unique_ptr<PriceStrategy> strategy; // how prices move right now (swappable)

    MarketEngine(double startingPrice); // private constructor — nobody can create this directly

public:
    static MarketEngine* getInstance(double startingPrice = 100.0);

    void subscribe(Observer* obs);
    void setStrategy(std::unique_ptr<PriceStrategy> newStrategy);
    void tick();                 // advances the market by one time step
    double getCurrentPrice() const;
};