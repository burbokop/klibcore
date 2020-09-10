#include "kfading.h"

#include <math.h>

KFading::KFading(double a, double b) {
    const double sqrtB = std::sqrt(b);
    x0 = -a * sqrtB / (1 - sqrtB);
    k = std::pow(x0, 2);
}

double KFading::function(double x) const {
    return k / std::pow(x - x0, 2);
}

double KFading::derivative(double x) const {
    return -2 * k / std::pow(x - x0, 3);
}
