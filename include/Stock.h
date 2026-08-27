#pragma once

#include <string>
#include <vector>

class Stock
{
private:
    std::string name;
    double currentPrice;
    std::vector<double> priceHistory;

public:
    Stock(const std::string& stockName, double initialPrice);

    void updatePrice(double newPrice);

    std::string getName() const;
    double getCurrentPrice() const;
    const std::vector<double>& getPriceHistory() const;
};