#include "Series.h"
#include <cmath>

double Series::FuncA(double x, int n)
{
    // arccos(x) = π/2 - arcsin(x) = π/2 - сума ряду
    double sum = 0.0;
    double pi = M_PI;
    
    // Обчислюємо суму перших n елементів ряду
    for (int i = 0; i < n; i++) {
        double term = 1.0;
        // Обчислюємо (2n)!
        for (int j = 1; j <= 2*i; j++) {
            term *= j;
        }
        // Обчислюємо 4^n * (n!)^2 * (2n+1)
        double denominator = pow(4, i) * pow(tgamma(i+1), 2) * (2*i+1);
        
        // Додаємо до суми
        sum += (term / denominator) * pow(x, 2*i+1);
    }
    
    // arccos(x) = π/2 - arcsin(x)
    return pi/2 - sum;
}
