#ifndef SERIES_H
#define SERIES_H

class Series
{
public:
    Series() {}
    virtual ~Series() {}
    
    // обчислення значення arccos(x) використовуючи  n елементів ряду
    // x - аргумент функції arccos, |x| < 1
    // n - кількість елементів ряду для обчислення суми
    double FuncA(double x, int n);
};

#endif
