#include <iostream>
#include "Series.h"
#include <limits>

int main()
{
    Series series;
    double x;
    
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
    
    std::cout << "Result: " << series.FuncA(x) << std::endl;
    return 0;
}
