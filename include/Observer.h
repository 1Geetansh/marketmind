#pragma once

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onPriceUpdate(double newPrice) = 0;
};