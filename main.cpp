#include "Series.h"
#include <cmath>
#include <iostream>
#include <limits>

int main()
{
    Series series;
    double x;
    int n;
    
    // Введення x з перевіркою, що |x| < 1
    do {
        std::cout << "Введіть значення x (|x| < 1): ";
        std::cin >> x;
        
        if (std::cin.fail() || std::abs(x) >= 1.0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некоректне значення. |x| має бути менше 1." << std::endl;
        } else {
            break;
        }
    } while (true);
    
    // Введення n з перевіркою, що n > 0
    do {
        std::cout << "Введіть кількість елементів ряду n (n > 0): ";
        std::cin >> n;
        
        if (std::cin.fail() || n <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некоректне значення. n має бути більше 0." << std::endl;
        } else {
            break;
        }
    } while (true);
    
    std::cout << "Result: " << series.FuncA(x, n) << std::endl;
    return 0;
}
