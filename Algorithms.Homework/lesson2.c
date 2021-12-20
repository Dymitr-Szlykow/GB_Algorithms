#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0


void Task_2_1(void);

void Task_2_2(void);
int Multiply_loop(int first, int second);
double Power_loop(double number, unsigned int power);
double Power_recursive(double number, unsigned int power);

void Task_2_3(void);


/// <summary>
/// 1. Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
/// </summary>
void Task_2_1() {
	printf("not implemented. sorry");
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
}