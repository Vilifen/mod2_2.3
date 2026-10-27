
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <limits.h>

#include "Calculator.h"

#define COUNT_FUNC 6

static const Select functions[COUNT_FUNC] =
{
    {1, "Сложение",       Addition,       NULL},
    {2, "Вычитание",      Subtraction,    NULL},
    {3, "Умножение",      Multiplication, NULL},
    {4, "Деление",        NULL,           Division},
    {5, "Максимум",       Max,            NULL},
    {6, "Минимум",        Min,            NULL}
};

static int ReadInt(const char* prompt, int* value)
{
    char line[128];

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return 0;
        }

        char* end;
        errno = 0;
        long number = strtol(line, &end, 10);

        if (end == line || errno == ERANGE ||
            number < INT_MIN || number > INT_MAX)
        {
            printf("Ошибка! Введите целое число.\n");
            continue;
        }

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (*end != '\0')
        {
            printf("Ошибка! Введите целое число.\n");
            continue;
        }

        *value = (int)number;
        return 1;
    }
}

static int ReadDouble(const char* prompt, double* value)
{
    char line[128];

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return 0;
        }

        char* end;
        errno = 0;
        double number = strtod(line, &end);

        if (end == line || errno == ERANGE || !isfinite(number))
        {
            printf("Ошибка! Введите корректное число.\n");
            continue;
        }

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (*end != '\0')
        {
            printf("Ошибка! Введите корректное число.\n");
            continue;
        }

        *value = number;
        return 1;
    }
}

static void Menu(void)
{
    int action;

    printf("\nДоступные действия:\n");

    for (int i = 0; i < COUNT_FUNC; i++)
    {
        printf("%d - %s\n", functions[i].func, functions[i].name);
    }

    printf("7 - Выход\n");

    if (!ReadInt("Введите номер действия: ", &action))
    {
        exit(EXIT_SUCCESS);
    }

    if (action == 7)
    {
        printf("Выход из программы.\n");
        exit(EXIT_SUCCESS);
    }

    const Select* selected = NULL;

    for (int i = 0; i < COUNT_FUNC; i++)
    {
        if (functions[i].func == action)
        {
            selected = &functions[i];
            break;
        }
    }

    if (selected == NULL)
    {
        printf("Некорректный номер действия!\n");
        return;
    }

    double result;

    /* Деление принимает ровно два аргумента. */
    if (selected->division != NULL)
    {
        double arg_1;
        double arg_2;

        if (!ReadDouble("Введите первое число: ", &arg_1) ||
            !ReadDouble("Введите второе число: ", &arg_2))
        {
            exit(EXIT_SUCCESS);
        }

        if (selected->division(arg_1, arg_2, &result))
        {
            printf("Ответ: %.10g\n", result);
        }
        else
        {
            printf("Ошибка: деление на ноль невозможно!\n");
        }

        return;
    }

    int count;

    if (!ReadInt("Введите количество аргументов (не менее 2): ",
                 &count))
    {
        exit(EXIT_SUCCESS);
    }

    if (count < 2)
    {
        printf("Количество аргументов должно быть не меньше 2.\n");
        return;
    }

    double* args = malloc((size_t)count * sizeof(*args));

    if (args == NULL)
    {
        printf("Ошибка: не удалось выделить память.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        char prompt[64];

        snprintf(prompt, sizeof(prompt),
                 "Введите аргумент %d: ", i + 1);

        if (!ReadDouble(prompt, &args[i]))
        {
            free(args);
            exit(EXIT_SUCCESS);
        }
    }

    /* Вызов выбранной операции через указатель на функцию. */
    result = selected->function((size_t)count, args);

    if (isfinite(result))
    {
        printf("Ответ: %.10g\n", result);
    }
    else
    {
        printf("Ошибка: результат выходит за допустимый диапазон.\n");
    }

    free(args);
}

int main(void)
{
    printf("Задание 2.3: Калькулятор с указателями на функции\n");

    while (1)
    {
        Menu();
    }

    return 0;
}
