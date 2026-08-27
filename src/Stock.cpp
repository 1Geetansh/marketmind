#include "Stock.h"

Stock::Stock(const std::string& stockName, double initialPrice)
    : name(stockName), currentPrice(initialPrice)
{
    priceHistory.push_back(initialPrice);
}

void Stock::updatePrice(double newPrice)
{
    currentPrice = newPrice;
    priceHistory.push_back(newPrice);
}

std::string Stock::getName() const
{
    return name;
}

double Stock::getCurrentPrice() const
{
    return currentPrice;
}

const std::vector<double>& Stock::getPriceHistory() const
{
    return priceHistory;
}