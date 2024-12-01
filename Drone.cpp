#include "Drone.h"
#include <iostream>
#include <cmath>
#include <algorithm>

std::vector<Drone> Drone::all_drones;
int Drone::max_drones = 5;

Drone::Drone(int x, int y, int max_capacity)
	: x(x), y(y), max_capacity(max_capacity), total_time(0)
{
	if (all_drones.size() < max_drones)
	{
		all_drones.push_back(*this);
	}
	else
	{
		std::cout << "Drone limit reached. Cannot create a new drone.\n";
	}
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

	int deliverable_weight = std::min(base.weight_required, max_capacity);
	base.weight_required -= deliverable_weight;

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

		// Try existing drones first
		for (auto &drone : all_drones)
		{
			if (drone.can_carry(base.weight_required))
			{
				delivered = drone.make_delivery(base);
				if (delivered)
					break;
			}
		}

		// Dispatch new drone if necessary
		if (!delivered)
		{
			if (all_drones.size() >= max_drones)
			{
				std::cout << "Cannot dispatch a new drone. Delivery to base ("
						  << base.x << ", " << base.y
						  << ") failed due to drone limit.\n";
				break;
			}

			std::cout << "Dispatching a new drone for remaining weight of "
					  << base.weight_required << " units to base ("
					  << base.x << ", " << base.y << ").\n";

			Drone new_drone(0, 0, all_drones.front().max_capacity); // Use the first drone's capacity
			all_drones.push_back(new_drone);
			delivered = new_drone.make_delivery(base);
		}

		if (!delivered)
		{
			std::cout << "Delivery to base (" << base.x << ", " << base.y
					  << ") failed. Unable to meet requirements.\n";
			break;
		}
	}
}
