#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#pragma warning(disable : 4996)

#define bool int
#define true 1
#define false 0


inline void Task_1_1(void);

inline void Task_1_2(void);
inline void Task_1_2a(void);
inline void Task_1_2b(void);
inline double GreatestOfFour_ReverseTree(double a, double b, double c, double d);
inline double GreatestOfFour_HeadOn(double a, double b, double c, double d);
inline void ReadGreaterNum(char* message, double* res);

inline void Task_1_3(void);
inline void Swap_withTemp(int* x, int* y);
inline void Swap_sum(int* x, int* y);
inline void SwapIntegers_binary(int* x, int* y);

inline void Task_1_4(void);
typedef struct coefs Coefs;
inline char* SqEquation_print(Coefs c);
inline int SqEquation_solve(Coefs c, double* x1, double* x2, double* D);

inline void Task_1_7(void);
typedef struct chessCell ChessCell;
inline ChessCell NewCell(unsigned int rank, unsigned int file);
inline ChessCell ReadCell(char* message);
inline char* CellColor_ToString(ChessCell c);

inline void Task_1_13(void);
inline void Task_1_13a(int count);
inline void Task_1_13b(int count);
inline int GetSystemRand(int digits);
inline void BootMyRand(unsigned int starter);
inline int GetMyRand(void);

inline void Task_1_14(void);
inline bool IsAutomorph(int num);


struct coefs {
	double A, B, C;
};

struct chessCell {
	unsigned char rank, file;
	bool IsWhite;
};

// 1. Ввести вес и рост человека.Рассчитать и вывести индекс массы тела по формуле I = m / (h * h); где m - масса тела в килограммах, h - рост в метрах.
// 2. Найти максимальное из четырех чисел.Массивы не использовать.
// 3. Написать программу обмена значениями двух целочисленных переменных :
//    a. с использованием третьей переменной;
//    b.* без использования третьей переменной.
// 4. Написать программу нахождения корней заданного квадратного уравнения.
// 5. С клавиатуры вводится номер месяца.Требуется определить, к какому времени года он относится.
// 6. Ввести возраст человека(от 1 до 150 лет) и вывести его вместе с последующим словом «год», «года» или «лет».
// 7. С клавиатуры вводятся числовые координаты двух полей шахматной доски(x1, y1, x2, y2).Требуется определить, относятся поля к одному цвету или нет.
// 8. Ввести a и b и вывести квадраты и кубы чисел от a до b.
// 9. Даны целые положительные числа N и K.Используя только операции сложения и вычитания, найти частное от деления нацело N на K, а также остаток от этого деления.
// 10. Дано целое число N(> 0).С помощью операций деления нацело и взятия остатка от деления определить, имеются ли в записи числа N нечетные цифры. Если имеются, то вывести True, если нет — вывести False.
// 11. С клавиатуры вводятся числа, пока не будет введен 0. Подсчитать среднее арифметическое всех положительных четных чисел, оканчивающихся на 8.
// 12. Написать функцию нахождения максимального из трех чисел.
// 13. * Написать функцию, генерирующую случайное число от 1 до 100.
//     а) с использованием стандартной функции rand()
//     б) без использования стандартной функции rand()
// 14. * Автоморфные числа.Натуральное число называется автоморфным, если оно равно последним цифрам своего квадрата.Например, 252 = 625.
//     Напишите программу, которая вводит натуральное число N и выводит на экран все автоморфные числа, не превосходящие N.
// Достаточно решить 3 задачи.Записывайте в начало программы условие и свою фамилию.Все решения создавайте в одной программе.Задачи со звездочками выполняйте в том случае, если решили базовые.Снабдите программу меню. 123


/// <summary>
/// 1. Ввести вес и рост человека. Рассчитать и вывести индекс массы тела по формуле I=m/(h*h); где m-масса тела в килограммах, h - рост в метрах.
/// </summary>
void Task_1_1() {
	double bodyHeight, bodyWeight, temp;

	printf("Введите массу тела: ");
	scanf("%lf", &bodyWeight);

	printf("Введите рост: ");
	scanf("%lf", &bodyHeight);
	if (bodyHeight > 50) bodyHeight /= 100;

	temp = pow(bodyHeight, 2);
	double bmIndex = bodyWeight / temp;
	double reqWeightMin = 18.5 * temp;
	double reqWeightMax = 25 * temp;

	printf("При массе %.2lf кг и росте %.2lf м, индекс массы тела - %.2lf,", bodyWeight, bodyHeight, bmIndex);

	if (bmIndex <= 18.5) {
		if (bmIndex <= 16)
			printf(" выраженный дефицит массы тела.");
		else
			printf(" указывает на недостаточную (дефицит) массу тела.");
		printf("\nДля вас желательная масса тела от %.2lf до %.2lf кг. Вам следует поправиться на %.2lf кг.\n", reqWeightMin, reqWeightMax, reqWeightMin - bodyWeight);
	}
	else if (bmIndex <= 25)
		printf(" в норме.\n");
	else {
		if (bmIndex <= 30)
			printf(" указывает на избыточную массу тела (предожирение).");
		else if (bmIndex <= 35)
			printf(" ожирение 1 степени.");
		else if (bmIndex <= 40)
			printf(" ожирение 2 степени.");
		else
			printf(" ожирение 3 степени.");
		printf("\nДля вас желательная масса тела от %.2lf до %.2lf кг. Вам следует похудеть на %.2lf кг.\n", reqWeightMin, reqWeightMax, bodyWeight - reqWeightMax);
	}
}


/// <summary>
/// 2. Найти максимальное из четырех чисел. Массивы не использовать.
/// </summary>
void Task_1_2() {
	Task_1_2a();
	getch();
	printf("\n");
	Task_1_2b();
}

void Task_1_2a() {
	double a, b, c, d;
	printf("Введите четыре числа: ");
	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
	printf("Наибольшее из них: %.2lf\n", GreatestOfFour_ReverseTree(a, b, c, d));
	printf("Другим способом: %.2lf\n", GreatestOfFour_HeadOn(a, b, c, d));
}

void Task_1_2b() {
	double res;

	printf("Введите первое число: ");
	scanf("%lf", &res);
	
	ReadGreaterNum("Введите второе число: ", &res);
	ReadGreaterNum("Введите третье число: ", &res);
	ReadGreaterNum("Введите четвертое число: ", &res);
	printf("Наибольшее из них: %.2lf\n", res);
}

double GreatestOfFour_ReverseTree(double a, double b, double c, double d) {
	if (a > b) b = a;
	if (c > d) d = c;
	if (b > d) return b;
	else return d;
}

double GreatestOfFour_HeadOn(double a, double b, double c, double d) {
	return
		a > b
		? (a > c
			? (a > d ? a : d)
			: (c > d ? c : d))
		: (b > c
			? (b > d ? b : d)
			: (c > d ? c : d));
}

void ReadGreaterNum(char* message, double* res) {
	double a;
	printf("%s", message);
	scanf("%lf", &a);
	if (a > *res) *res = a;
}


/// <summary>
/// 3. Написать программу обмена значениями двух целочисленных переменных:
/// a) с использованием третьей переменной;
/// b) *без использования третьей переменной.
/// </summary>
void Task_1_3() {
	int a, b;
	printf("Введите два целых числа: ");
	scanf("%d %d", &a, &b);

	Swap_withTemp(&a, &b);
	printf("Один способ:\t%d  %d\n", a, b);

	Swap_sum(&a, &b);
	printf("Обратно:\t%d  %d\n", a, b);

	SwapIntegers_binary(&a, &b);
	printf("И снова:\t%d  %d\n", a, b);
}

void Swap_withTemp(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Swap_sum(int* x, int* y) {
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void SwapIntegers_binary(int* x, int* y) {
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}


/// <summary>
/// 4. Написать программу нахождения корней заданного квадратного уравнения.
/// </summary>
void Task_1_4() {
	double x1, x2, D;
	Coefs c;
	int hasRoots;

	printf("Квадратное уравнение общего вида:  A * x^2 + B * x + C = 0.\n");
	printf("Введите коэффициенты:\n  A = ");
	scanf("%lf", &c.A);
	if (c.A == 0) {
		printf("При коэффициенте A = 0 уравнение является линейным. Решение прерывается.");
		return;
	}

	printf("  B = ");
	scanf("%lf", &c.B);

	printf("  C = ");
	scanf("%lf", &c.C);

	printf("%s", SqEquation_print(c));
	hasRoots = SqEquation_solve(c, &x1, &x2, &D);

	printf("Дескрименант равен %.3lf. ", D);
	if (hasRoots == 1) {
		if (c.B == 0)
			printf("Уравнение имеет два корня: +/- %lf.\n", fabs(x1)); //±
		else
			printf("Уравнение имеет два корня: %lf и %lf.\n", x1, x2);
	}
	else if (hasRoots == 0)
		printf("Уравнение имеет один корень: %lf.\n", x1);
	else
		printf("Уравнение не имеет корней.\n");
}

char* SqEquation_print(Coefs c) {
	char res[64] = "", temp[16];

	sprintf(res, "%.2lf*x^2", c.A);

	if (c.B != 0) {
		strcat(res, c.B < 0 ? " - " : " + ");
		if (c.B == 1 || c.B == -1)
			sprintf(temp, "x");
		else
			sprintf(temp, "%.2lfx", fabs(c.B));
		strcat(res, temp);
	}

	if (c.C != 0) {
		sprintf(temp, "%s%.2lf", c.C < 0 ? " - " : " + ", fabs(c.C));
		strcat(res, temp);
	}
	strcat(res, " = 0\n");
	return res;
}

int SqEquation_solve(Coefs c, double* x1, double* x2, double* D)
{
	*D = c.B * c.B - 4 * c.A * c.C;

	if (D < 0) {
		return -1;
	}
	else if (D > 0) {
		*x1 = (-c.B - sqrt(*D)) / 2 / c.A;
		*x2 = (-c.B + sqrt(*D)) / 2 / c.A;
		return 1;
	}
	else {
		*x1 = -c.B / 2 / c.A;
		*x2 = *x1;
		return 0;
	}
}


/// <summary>
/// 7. С клавиатуры вводятся числовые координаты двух полей шахматной доски (x1,y1,x2,y2).
/// Требуется определить, относятся поля к одному цвету или нет.
/// </summary>
void Task_1_7() {
	ChessCell c1 = ReadCell("первой клетки");
	ChessCell c2 = ReadCell("второй клетки");

	if (c1.IsWhite == c2.IsWhite) {
		printf("Обе клетки %s.", CellColor_ToString(c1));
	}
	else {
		printf("Данные клетки разных цветов. Первая - %s, вторая - %s.", CellColor_ToString(c1), CellColor_ToString(c2));
	}
}

ChessCell NewCell(unsigned int rank, unsigned int file) {
	ChessCell res;
	res.rank = (unsigned char)rank;
	res.file = (unsigned char)file;
	if ((rank % 2) + (file % 2) == 1) res.IsWhite = true;
	else res.IsWhite = false;
	return res;
}

char* CellColor_ToString(ChessCell c) {
	return c.IsWhite ? "белого цвета" : "черного цвета";
}

ChessCell ReadCell(char* message) {
	unsigned int rankInput, fileInput;
	unsigned char temp;
	bool ok = false;

	do {
		printf("Введите колону (a-h) и ряд (1-8) %s через пробел: ", message);
		if (scanf("%c%lu", &temp, &rankInput) == 2) {
			if ('a' <= temp && temp <= 'h' && 1 <= rankInput && rankInput <= 8) {
				ok = true;
				fileInput = (unsigned int)temp - 96;
			}
			else {
				printf("некорректное значение\n");
			}
		}
		else {
			printf("ошибка чтения\n");
		}
	} while (!ok);
	return NewCell(rankInput, fileInput);
}


/// <summary>
/// 13. Написать функцию, генерирующую случайное число от 1 до 100.
/// а) с использованием стандартной функции rand()
/// б) без использования стандартной функции rand()
/// </summary>
void Task_1_13() {
	Task_1_13a(25);
	Task_1_13b(25);
}

void Task_1_13a(int count) {
	if (count == 0) return;
	int i;
	srand(time(NULL));
	for (i = 0; i < count; i++) {
		printf("%3d ", GetSystemRand(2) + 1);
	}
	printf("\n");
}

void Task_1_13b(int count) {
	if (count == 0) return;
	int i;
	BootMyRand(7);
	for (i = 0; i < count; i++) {
		printf("%3d ", (GetMyRand() % 100) + 1);
	}
	printf("\n");
}

int GetSystemRand(int digits) {
	int i, base = 1;
	for (int i = 1; i <= digits; i++) {
		base *= 10;
	}
	return (rand() % base);
}

unsigned long int Xn, A, C, Mod;
void BootMyRand(unsigned int starter) {
	Xn = starter;
	A = 1103515245;
	C = 12345;
	Mod = 32768;
}
int GetMyRand() {
	if (Xn == NULL || A == NULL || C == NULL || Mod == NULL) BootMyRand(33);
	Xn = (A * Xn + C) % Mod;
	return (unsigned int)Xn;
}


/// <summary>
/// 14. Автоморфные числа. Натуральное число называется автоморфным, если оно равно последним цифрам своего квадрата. Например, 252 = 625.
/// Напишите программу, которая вводит натуральное число N и выводит на экран все автоморфные числа, не превосходящие N.
/// </summary>
void Task_1_14() {
	unsigned int upto, num;
	printf("Введите натуральное число: ");
	scanf("%lu", &upto);

	printf("автоморфные числа меньше введенного:\n");
	for (num = 1; num < upto; num++) {
		if (IsAutomorph(num))
			printf(" %lu ^2 = %.0lf \n", num, pow(num, 2));
	}
}

bool IsAutomorph(int num) {
	long int sq;
	sq = pow(num, 2);
	while (num) {
		if (num % 10 != sq % 10) return false;
		else {
			num /= 10;
			sq /= 10;
		}
	}
	return true;
}