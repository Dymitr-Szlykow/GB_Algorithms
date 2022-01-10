#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lesson2.h"

#define _StringLength 16

// 1. Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
// 2. Реализовать функцию возведения числа a в степень b :
//    a.без рекурсии;
//    b.рекурсивно;
//    c.* рекурсивно, используя свойство четности степени.
// 3. * *Исполнитель Калькулятор преобразует целое число, записанное на экране.
//    У исполнителя две команды, каждой команде присвоен номер: Прибавь 1, Умножь на 2.
//    Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза.
//    Сколько существует программ, которые число 3 преобразуют в число 20 ?


/// <summary>
/// 1. Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
/// </summary>
void Task_2_1() {
	int num, length = _StringLength, temp, error;
	char asbin[_StringLength];

	printf("Введите целое число: ");
	scanf("%d", &num);

	error = AsBinary_HeadOn_loop(num, length, asbin);
	if (!error)
		printf("Двоичное представление а): %s\n", asbin);
	else {
		printf("что-то пошло не так");
		if (error == 1)
			printf(", а именно: превышена длина строки\n");
		else if (error == 2)
			printf(". это же совсем короткая строка!\n");
	}

	temp = num;
	if (AsBinary_recursive(&temp, &length, asbin))
		printf("что-то пошло не так, а именно: превышена длина строки\n");
	else
		printf("Двоичное представление б): %s\n", asbin);

}

int AsBinary_HeadOn_loop(int number, unsigned int maxlength, char* out) {
	if (maxlength < 2) return 2;
	
	else if (number == 0) {
		*out = '0';
		*(out + 1) = '\0';
	}
	else if (number == 1) {
		*out = '1';
		*(out + 1) = '\0';
	}
	else {
		int power = 1, i = 0, cap = 1;
		if (number < 0) {
			*(out + i) = '-';
			number *= -1;
			i = 1;
		}

		while (power <= number) {
			power *= 2;
			cap++;
		}
		if (cap + i > maxlength) return 1;

		for (; cap > 1; cap--, i++) {
			power /= 2;

			if (number >= power) {
				number -= power;
				*(out + i) = '1';
			}
			else {
				*(out + i) = '0';
			}
		}
		*(out + i) = '\0';
	}

	return 0;
}

int AsBinary_recursive(int* number, unsigned int* maxlength, char* out) {
	if (*number == 0) {
		*out = '0';
		*(out + 1) = '\0';
	}

	else if (*number == 1) {
		*out = '1';
		*(out + 1) = '\0';
		*maxlength -= 1;
	}
	else {

		if (*number < 0) {
			*out = '-';
			*number *= -1;
			out++;
			*maxlength -= 1;
		}

		char thisposition = *number % 2 == 0 ? '0' : '1';
		*number = (*number % 2 == 0) ? (*number / 2) : ((*number - 1) / 2);
		if (AsBinary_recursive(number, maxlength, out)) return 1;

		if (*maxlength > 1) {
			*(out + *number) = thisposition;
			*(out + *number + 1) = '\0';
			*number += 1;
			*maxlength -= 1;
		}
		else return 1;

	}
	return 0;
}


/// <summary>
/// 2. Реализовать функцию возведения числа a в степень b:
/// a. без рекурсии;
/// b. рекурсивно;
/// c. *рекурсивно, используя свойство четности степени.
/// </summary>
void Task_2_2() {
	double a;
	unsigned int b;
	printf("Введите число для возведения в степень: ");
	scanf("%lf", &a);
	printf("Введите степень целым положительным числом: ");
	scanf("%lu", &b);

	printf("Ответ а): %lf\n", Power_loop(a, b));
	printf("Ответ б): %lf\n", Power_recursive(a, b));
}

int Multiply_loop(int first, int second) {
	if (first < second) SwapIntegers_binary(&first, &second); // см. lesson1.c

	int i, res = first;
	for (i = 1; i <= second; i++) {
		res += first;
	}
	return res;
}

double Power_loop(double number, unsigned int power) {
	while (power % 2 == 0) {
		number *= number;
		power /= 2;
	}

	int i;
	double res = number;
	for (i = power; i > 1; i--) {
		res *= number;
	}
	return res;
}

double Power_recursive(double number, unsigned int power) {
	if (power == 1) return number;

	if (power % 2 == 0)
		return Power_recursive(number * number, power / 2);
	else
		return number * Power_recursive(number, power - 1);
}


/// <summary>
/// 3. **Исполнитель Калькулятор преобразует целое число, записанное на экране.
/// У исполнителя две команды, каждой команде присвоен номер: 1) Прибавь 1; 2) Умножь на 2.
/// Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза.
/// Сколько существует программ, которые число 3 преобразуют в число 20?
/// </summary>
void Task_2_3() {
	printf("not implemented. sorry");
	//printf("Начальное число: 3\n");
	//printf("Действие 1: +1\n");
	//printf("Действие 2: *2\n");
}