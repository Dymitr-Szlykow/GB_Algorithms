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
/// 1. ����������� ������� �������� �� ���������� ������� � ��������, ��������� ��������.
/// </summary>
void Task_2_1() {
	printf("not implemented. sorry");
}


/// <summary>
/// 2. ����������� ������� ���������� ����� a � ������� b:
/// a. ��� ��������;
/// b. ����������;
/// c. *����������, ��������� �������� �������� �������.
/// </summary>
void Task_2_2() {
	double a;
	unsigned int b;
	printf("������� ����� ��� ���������� � �������: ");
	scanf("%lf", &a);
	printf("������� ������� ����� ������������� ������: ");
	scanf("%lu", &b);

	printf("����� �): %lf\n", Power_loop(a, b));
	printf("����� �): %lf\n", Power_recursive(a, b));
}

int Multiply_loop(int first, int second) {
	if (first < second) SwapIntegers_binary(&first, &second); // ��. lesson1.c

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
/// 3. **����������� ����������� ����������� ����� �����, ���������� �� ������.
/// � ����������� ��� �������, ������ ������� �������� �����: 1) ������� 1; 2) ������ �� 2.
/// ������ ������� ����������� ����� �� ������ �� 1, ������ ����������� ��� ����� � 2 ����.
/// ������� ���������� ��������, ������� ����� 3 ����������� � ����� 20?
/// </summary>
void Task_2_3() {
	printf("not implemented. sorry");
}