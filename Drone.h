#pragma once
#include <vector>
#include "Base.h"

class Drone
{
public:
    int x, y;         // Current coordinates of the drone (starting at the main base)
    int max_capacity; // Maximum weight the drone can carry
    int total_time;   // Total time taken for deliveries

    // Static vector to hold all drones
    static std::vector<Drone> all_drones;
    static int max_drones; // Maximum number of drones allowed

    // Constructor
    Drone(int x, int y, int max_capacity);

    // Method to check if the drone can carry the requested weight
    bool can_carry(int weight);

    // Method to calculate the time taken for the drone to reach a base
    int time_to_reach(Base &base);

    // Method to make a delivery, returns true if the delivery was successful
    bool make_delivery(Base &base);

    // Method to make multiple trips if weight exceeds drone's capacity
    static void make_multiple_trips(Base &base);
};
