
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stddef.h>

typedef double (*Operation)(size_t count, const double args[]);
typedef int (*DivisionOperation)(double arg_1, double arg_2,
                                 double* result);

typedef struct Select
{
    int func;
    const char* name;
    Operation function;
    DivisionOperation division;
} Select;

double Addition(size_t count, const double args[]);
double Subtraction(size_t count, const double args[]);
double Multiplication(size_t count, const double args[]);
int Division(double arg_1, double arg_2, double* result);
double Max(size_t count, const double args[]);
double Min(size_t count, const double args[]);

#endif
