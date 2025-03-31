#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include "../Series.h"

int main(int argc, char** argv)
{
    Series series;
    
    // Частина 1: Тест точності обчислень
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
    
    // Частина 2: Тест часу виконання
    std::cout << "Тестування часу обчислень... " << std::endl;
    
    // Записуємо час початку
    auto t1 = std::chrono::high_resolution_clock::now();
    
    // Створюємо вектор для зберігання значень
    std::vector<double> aValues;
    
    // Mersenne Twister random engine
    std::mt19937 mtre {123}; 
    std::uniform_real_distribution<double> distr {-0.99, 0.99}; // Діапазон для arccos
    
    // Заповнюємо вектор значеннями arccos для випадкових аргументів
    for (int i=0; i<1500000; i++)
    {
    double x = distr(mtre);
    aValues.push_back(series.FuncA(x, 7));
    }
    
    // Сортуємо і перевертаємо вектор декілька разів
    for (int i=0; i<350; i++)
    {
    std::sort(begin(aValues), end(aValues));
    std::reverse(begin(aValues), end(aValues));
    }
    
    // Записуємо час закінчення
    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
    
    int computation_time_ms = int_ms.count();
    std::cout << "Час виконання: " << computation_time_ms << " мс" << std::endl;
    
    // Перевіряємо, чи час у межах від 5 до 20 секунд
    bool time_ok = (computation_time_ms >= 5000 && computation_time_ms <= 20000);
    
    if (!time_ok) {
        std::cerr << "Тест часу виконання не пройдено. Час має бути від 5 до 20 секунд." << std::endl;
        all_passed = false;
    }
    
    if (all_passed) {
        std::cout << "Всі тести успішно пройдено!" << std::endl;
        return 0; // успіх
    } else {
        return 1; // помилка
    }
}
