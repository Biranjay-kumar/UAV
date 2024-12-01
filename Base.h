// #pragma once
// #include <cmath>

// class Base
// {
// public:
//     int x, y;            // Coordinates of the base
//     int weight_required; // Weight required to be delivered
//     int time_limit;      // Time limit for delivery

//     Base(int x, int y, int weight, int time)
//         : x(x), y(y), weight_required(weight), time_limit(time) {}

//     double distance_from(int dx, int dy) const;
// };

#pragma once
#include <cmath>

class Base
{
public:
    int id;
    int x, y;            // Coordinates
    int weight_required; // Required weight
    int time_limit;      // Time limit
    int time_to_main;    // Time to main post

    Base(int x, int y, int weight, int time, int id)
        : x(x), y(y), weight_required(weight), time_limit(time), id(id), time_to_main(0) {}

    int distance_from(int other_x, int other_y) const;
    int time_to(int other_x, int other_y, int speed) const;
    void calculate_time_to_main(int main_x, int main_y, int speed);
};
