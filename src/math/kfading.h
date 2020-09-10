#ifndef KFADING_H
#define KFADING_H


class KFading {
    double x0 = 0;
    double k = 0;
public:
    KFading(double a, double b);
    double function(double x) const;
    double derivative(double x) const;
};

#endif // KFADING_H
