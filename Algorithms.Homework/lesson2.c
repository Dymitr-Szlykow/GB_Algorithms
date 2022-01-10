#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lesson2.h"

#define _StringLength 16

// 1. ����������� ������� �������� �� ���������� ������� � ��������, ��������� ��������.
// 2. ����������� ������� ���������� ����� a � ������� b :
//    a.��� ��������;
//    b.����������;
//    c.* ����������, ��������� �������� �������� �������.
// 3. * *����������� ����������� ����������� ����� �����, ���������� �� ������.
//    � ����������� ��� �������, ������ ������� �������� �����: ������� 1, ������ �� 2.
//    ������ ������� ����������� ����� �� ������ �� 1, ������ ����������� ��� ����� � 2 ����.
//    ������� ���������� ��������, ������� ����� 3 ����������� � ����� 20 ?


/// <summary>
/// 1. ����������� ������� �������� �� ���������� ������� � ��������, ��������� ��������.
/// </summary>
void Task_2_1() {
	int num, length = _StringLength, temp, error;
	char asbin[_StringLength];

	printf("������� ����� �����: ");
	scanf("%d", &num);

	error = AsBinary_HeadOn_loop(num, length, asbin);
	if (!error)
		printf("�������� ������������� �): %s\n", asbin);
	else {
		printf("���-�� ����� �� ���");
		if (error == 1)
			printf(", � ������: ��������� ����� ������\n");
		else if (error == 2)
			printf(". ��� �� ������ �������� ������!\n");
	}

	temp = num;
	if (AsBinary_recursive(&temp, &length, asbin))
		printf("���-�� ����� �� ���, � ������: ��������� ����� ������\n");
	else
		printf("�������� ������������� �): %s\n", asbin);

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
	//printf("��������� �����: 3\n");
	//printf("�������� 1: +1\n");
	//printf("�������� 2: *2\n");
}