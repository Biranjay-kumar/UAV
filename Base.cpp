// #include "Base.h"

// double Base::distance_from(int dx, int dy) const
// {
//     return sqrt(pow(dx - x, 2) + pow(dy - y, 2));
// }

#include "Base.h"

int Base::distance_from(int other_x, int other_y) const
{
    return static_cast<int>(sqrt(pow(x - other_x, 2) + pow(y - other_y, 2)));
}

int Base::time_to(int other_x, int other_y, int speed) const
{
    int distance = distance_from(other_x, other_y);
    return distance / speed;
}

void Base::calculate_time_to_main(int main_x, int main_y, int speed)
{
    time_to_main = time_to(main_x, main_y, speed);
}
