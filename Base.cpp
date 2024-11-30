#include "Base.h"
#include <cmath>

double Base::distance_from(int dx, int dy) const {
    return sqrt(pow(dx - x, 2) + pow(dy - y, 2));
}
