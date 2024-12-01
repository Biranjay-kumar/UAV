
// 1st Code ------------------------------------->
// #include <iostream>
// #include "Drone.h"
// #include "Base.h"
// #include <vector>
// #include <algorithm>

// int main()
// {
// 	int startX, startY, capacity, numBases;

// 	std::cout << "Enter drone's starting position (x y): ";
// 	std::cin >> startX >> startY;
// 	std::cout << "Enter drone's max capacity: ";
// 	std::cin >> capacity;

// 	std::cout << "Enter maximum number of drones allowed: ";
// 	std::cin >> Drone::max_drones;

// 	Drone drone(startX, startY, capacity); // Create the initial drone

// 	std::cout << "Enter number of bases: ";
// 	std::cin >> numBases;

// 	std::vector<Base> bases;
// 	for (int i = 0; i < numBases; ++i)
// 	{
// 		int x, y, weight, time_limit;
// 		std::cout << "Enter Base " << i + 1 << " details (x y weight_required time_limit): ";
// 		std::cin >> x >> y >> weight >> time_limit;
// 		bases.emplace_back(x, y, weight, time_limit);
// 	}

// 	// Sort bases by time limit and distance
// 	std::sort(bases.begin(), bases.end(), [&drone](Base &a, Base &b)
// 			  {
//         if (a.time_limit == b.time_limit) {
//             return a.distance_from(drone.x, drone.y) < b.distance_from(drone.x, drone.y);
//         }
//         return a.time_limit < b.time_limit; });

// 	for (auto &base : bases)
// 	{
// 		if (base.weight_required > 0)
// 		{
// 			Drone::make_multiple_trips(base);
// 		}
// 	}

// 	int total_time = 0;
// 	for (auto &drone : Drone::all_drones)
// 	{
// 		total_time += drone.total_time;
// 	}
// 	std::cout << "\nTotal time for deliveries: " << total_time << " seconds.\n";

// 	return 0;
// }


// 2nd Code -------------------------->

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

	std::cout << "Enter maximum number of drones allowed: ";
	std::cin >> Drone::max_drones;

	Drone drone(startX, startY, capacity);

	std::cout << "Enter number of bases: ";
	std::cin >> numBases;

	int speed = 10; // Example speed for travel calculation

	std::vector<Base> bases;
	std::vector<std::vector<int>> time_matrix(numBases, std::vector<int>(numBases, 0));

	for (int i = 0; i < numBases; ++i)
	{
		int x, y, weight, time_limit;
		std::cout << "Enter Base " << i + 1 << " details (x y weight_required time_limit): ";
		std::cin >> x >> y >> weight >> time_limit;

		Base base(x, y, weight, time_limit, i + 1);
		base.calculate_time_to_main(startX, startY, speed);
		bases.push_back(base);
	}

	// Create time matrix for base-to-base travel
	for (int i = 0; i < numBases; ++i)
	{
		for (int j = 0; j < numBases; ++j)
		{
			time_matrix[i][j] = bases[i].time_to(bases[j].x, bases[j].y, speed);
		}
	}

	// Sort bases by time limit and distance from main base
	std::sort(bases.begin(), bases.end(), [](const Base &a, const Base &b)
			  {
        if (a.time_limit == b.time_limit) {
            return a.time_to_main < b.time_to_main;
        }
        return a.time_limit < b.time_limit; });

	// Make deliveries
	for (auto &base : bases)
	{
		if (base.weight_required > 0)
		{
			Drone::make_multiple_trips(base, time_matrix, bases);
		}
	}

	// Calculate total time and drones used
	int total_time = 0;
	for (const auto &drone : Drone::all_drones)
	{
		total_time += drone.total_time;
	}

	std::cout << "\nTotal time for deliveries: " << total_time << " seconds.\n";
	std::cout << "Minimum number of drones used: " << Drone::all_drones.size() << "\n";

	return 0;
}
