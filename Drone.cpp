#include "Drone.h"
#include <iostream>
#include <cmath>
#include <algorithm>

// Static vector to hold all drones
std::vector<Drone> Drone::all_drones;

Drone::Drone(int x, int y, int max_capacity)
		: x(x), y(y), max_capacity(max_capacity), total_time(0)
{
	all_drones.push_back(*this); // Add drone to the list
}

bool Drone::can_carry(int weight)
{
	return weight <= max_capacity;
}

int Drone::time_to_reach(Base &base)
{
	return static_cast<int>(sqrt(pow(base.x - x, 2) + pow(base.y - y, 2)));
}

bool Drone::make_delivery(Base &base)
{
	int travel_time = time_to_reach(base);

	if (total_time + travel_time > base.time_limit)
	{
		std::cout << "Failed to deliver to base (" << base.x << ", " << base.y
							<< ") within time limit.\n";
		return false;
	}

	// Deliver the required weight or as much as possible within the limit
	int deliverable_weight = std::min(base.weight_required, max_capacity);
	base.weight_required -= deliverable_weight;

	// Update drone position and time
	x = base.x;
	y = base.y;
	total_time += travel_time;

	std::cout << "Delivered " << deliverable_weight << " units to base ("
						<< base.x << ", " << base.y << "). Time taken: "
						<< travel_time << " seconds.\n";
	return true;
}

void Drone::make_multiple_trips(Base &base)
{
	while (base.weight_required > 0)
	{
		bool delivered = false;

		// Try to deliver using the first available drone
		for (auto &drone : all_drones)
		{
			if (drone.can_carry(base.weight_required))
			{
				delivered = drone.make_delivery(base);
				if (delivered)
					break;
			}
		}

		// If no drone can carry the required weight, create a new one and try again
		if (!delivered)
		{
			std::cout << "Need to dispatch another drone for remaining delivery.\n";
			Drone new_drone(0, 0, base.weight_required); // Create a new drone
			all_drones.push_back(new_drone);						 // Add to fleet
			new_drone.make_delivery(base);							 // Try delivering with the new drone
		}
	}
}
