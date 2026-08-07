#pragma once
#include <string>
#include <unordered_map>

class Portfolio {
private:
    double cash;
    std::unordered_map<std::string, int> holdings;

public:
    Portfolio(double startingCash) : cash(startingCash) {}

    bool buy(const std::string& stockName, int quantity, double price);
    bool sell(const std::string& stockName, int quantity, double price);
    double getTotalValue(double currentPrice) const;
    double getCash() const { return cash; }
};