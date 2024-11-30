#include <iostream>
#include "Drone.h"
#include "Base.h"
#include <vector>
#include <algorithm>

int main()
{
	int startX, startY, capacity, numBases;

	std::cout << "Enter drone's starting position (x y): ";
	std::cin >> startX >> startY;
	std::cout << "Enter drone's max capacity: ";
	std::cin >> capacity;

	Drone drone(startX, startY, capacity); // Create the initial drone

	std::cout << "Enter number of bases: ";
	std::cin >> numBases;

	std::vector<Base> bases;
	for (int i = 0; i < numBases; ++i)
	{
		int x, y, weight, time_limit;
		std::cout << "Enter Base " << i + 1 << " details (x y weight_required time_limit): ";
		std::cin >> x >> y >> weight >> time_limit;
		bases.emplace_back(x, y, weight, time_limit);
	}

	// Sort bases by time limit first, then by distance to ensure timely delivery
	std::sort(bases.begin(), bases.end(), [&drone](Base &a, Base &b)
						{
        if (a.time_limit == b.time_limit) {
            return a.distance_from(drone.x, drone.y) < b.distance_from(drone.x, drone.y);
        }
        return a.time_limit < b.time_limit; });

	for (auto &base : bases)
	{
		if (base.weight_required > 0)
		{
			Drone::make_multiple_trips(base); // Dispatch drones for delivery
		}
	}

	// Output total time taken
	int total_time = 0;
	for (auto &drone : Drone::all_drones)
	{
		total_time += drone.total_time;
	}
	std::cout << "\nTotal time for deliveries: " << total_time << " seconds.\n";
	return 0;
}

// ---------for compile--------------------------------
// g++ Main.cpp Drone.cpp Base.cpp -o drone_delivery
// ------for run--------------------------------
// .\drone_delivery.exe
