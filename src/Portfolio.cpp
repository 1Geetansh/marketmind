#include "Portfolio.h"

bool Portfolio::buy(const std::string& stockName, int quantity, double price)
{
    double totalCost = quantity * price;

    if (totalCost > cash)
    {
        return false;
    }

    cash -= totalCost;
    holdings[stockName] += quantity;

    return true;
}

bool Portfolio::sell(const std::string& stockName, int quantity, double price)
{
    if (holdings[stockName] < quantity)
    {
        return false;
    }

    holdings[stockName] -= quantity;
    cash += quantity * price;

    return true;
}

double Portfolio::getTotalValue(double currentPrice) const
{
    double totalValue = cash;

    for (const auto& holding : holdings)
    {
        totalValue += holding.second * currentPrice;
    }

    return totalValue;
}