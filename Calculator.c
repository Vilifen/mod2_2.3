
#include <stddef.h>
#include "Calculator.h"

double Addition(size_t count, const double args[])
{
    double result = 0.0;

    for (size_t i = 0; i < count; i++)
    {
        result += args[i];
    }

    return result;
}

double Subtraction(size_t count, const double args[])
{
    double result = args[0];

    for (size_t i = 1; i < count; i++)
    {
        result -= args[i];
    }

    return result;
}

double Multiplication(size_t count, const double args[])
{
    double result = 1.0;

    for (size_t i = 0; i < count; i++)
    {
        result *= args[i];
    }

    return result;
}

int Division(double arg_1, double arg_2, double* result)
{
    if (result == NULL || arg_2 == 0.0)
    {
        return 0;
    }

    *result = arg_1 / arg_2;
    return 1;
}

double Max(size_t count, const double args[])
{
    double result = args[0];

    for (size_t i = 1; i < count; i++)
    {
        if (args[i] > result)
        {
            result = args[i];
        }
    }

    return result;
}

double Min(size_t count, const double args[])
{
    double result = args[0];

    for (size_t i = 1; i < count; i++)
    {
        if (args[i] < result)
        {
            result = args[i];
        }
    }

    return result;
}
