#include <cmath>
#include <iostream>
#include "../Series.h"

int main(int argc, char** argv)
{
    Series series;
    
    // Тестові значення
    double test_values[] = {0.0, 0.5, -0.5, 0.7, -0.7};
    int n = 10; // кількість елементів ряду для обчислення
    
    bool all_passed = true;
    
    for (double x : test_values) {
        // Обчислюємо за допомогою нашої функції
        double result = series.FuncA(x, n);
        
        // Обчислюємо за допомогою стандартної функції
        double expected = acos(x);
        
        // Допустима похибка
        double epsilon = 1e-4;
        
        // Перевіряємо, чи відхилення в межах допустимої похибки
        if (fabs(result - expected) > epsilon) {
            std::cerr << "Тест не пройдено для x = " << x << std::endl;
            std::cerr << "Очікувано: " << expected << ", Отримано: " << result << std::endl;
            all_passed = false;
        }
    }
    
    if (all_passed) {
        std::cout << "Всі тести успішно пройдено!" << std::endl;
        return 0; // успіх
    } else {
        return 1; // помилка
    }
}
