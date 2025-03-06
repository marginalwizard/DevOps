#ifndef SERIES_H
#define SERIES_H

class Series
{
public:
    Series() {}
    virtual ~Series() {}
    
    // обчислення  значення arccos(x) використовуючи 3 елементи ряду
    // x - аргумент функції, |x| < 1
    double FuncA(double x);
};

#endif
