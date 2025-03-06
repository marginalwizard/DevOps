#include "Series.h"
#include <cmath>

double Series::FuncA(double x)
{
    // arccos(x) = π/2 - arcsin(x) = π/2 - сума ряду з 3 елементів
    double pi = M_PI;
    double sum = 0.0;
    
    // Елемент 1
    sum += x;
    
    // Елемент 2
    sum += (1.0/2.0) * (pow(x, 3) / 3.0);
    
    // Елемент 3
    sum += (1.0*3.0)/(2.0*4.0) * (pow(x, 5) / 5.0);
    
    return pi/2 - sum;
}
