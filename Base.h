#pragma once
#include <cmath>

class Base {
public:
    int x, y, weight_required, time_limit;
    Base(int x, int y, int weight, int time)
        : x(x), y(y), weight_required(weight), time_limit(time) {}

    double distance_from(int dx, int dy) const;  // Only declare here
};
