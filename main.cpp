#include "Series.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <sys/wait.h>
#include <signal.h>

int CreateHTTPserver();

void sigchldHandler(int s)
{
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (WIFEXITED(status)) printf("\nChild process terminated\n");
    }
}

void sigintHandler(int s)
{
    printf("Caught signal %d. Starting graceful exit procedure\n", s);
    
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status)) printf("\nChild process terminated\n");
    }
    
    if (pid == -1) printf("\nAll child processes terminated\n");
    
    exit(EXIT_SUCCESS);
}

int main()
{
    int choice;
    
    signal(SIGCHLD, sigchldHandler);
    signal(SIGINT, sigintHandler);
    
    std::cout << "Виберіть режим роботи:" << std::endl;
    std::cout << "1. Обчислення arccos(x)" << std::endl;
    std::cout << "2. Запуск HTTP сервера" << std::endl;
    std::cout << "Ваш вибір (1 або 2): ";
    std::cin >> choice;
    
    if (choice == 2) {
        std::cout << "Запуск HTTP сервера на порту 8081..." << std::endl;
        std::cout << "Доступ до /compute для обчислення та сортування." << std::endl;
        return CreateHTTPserver();
    }
    else {
        // обчислення arccos
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
}
