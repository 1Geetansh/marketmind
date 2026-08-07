#pragma once

class PriceStrategy {
public:
    virtual ~PriceStrategy() = default;
    virtual double nextPrice(double currentPrice) = 0;
};