#pragma once
#include <cmath>

class Base
{
public:
    int x, y;            // Coordinates of the base
    int weight_required; // Weight required to be delivered
    int time_limit;      // Time limit for delivery

    Base(int x, int y, int weight, int time)
        : x(x), y(y), weight_required(weight), time_limit(time) {}

    double distance_from(int dx, int dy) const;
};