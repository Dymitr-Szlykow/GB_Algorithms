#ifndef LESSON1_H
#define LESSON1_H

#define bool int
#define true 1
#define false 0

// ЗАДАНИЯ к занятию №1.
// 1. Ввести вес и рост человека. Рассчитать и вывести индекс массы тела по формуле I = m / (h * h); где m - масса тела в килограммах, h - рост в метрах.
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
// Достаточно решить 3 задачи. Записывайте в начало программы условие и свою фамилию. Все решения создавайте в одной программе. Задачи со звездочками выполняйте в том случае, если решили базовые. Снабдите программу меню.

typedef struct coefs {
	double A, B, C;
} Coefs;

typedef struct chessCell {
	unsigned char rank, file;
	bool IsWhite;
} ChessCell;

void Task_1_1(void);

void Task_1_2(void);
void Task_1_2a(void);
void Task_1_2b(void);
double GreatestOfFour_ReverseTree(double a, double b, double c, double d); // = O(1)
double GreatestOfFour_HeadOn(double a, double b, double c, double d); // = O(1)
void ReadGreaterNum(char* message, double* res); // = O(scanf(message.length)) = O(message.length)  ~ O(n)

void Task_1_3(void);
inline void Swap_withTemp(int* x, int* y); // = O(1)
inline void Swap_sum(int* x, int* y); // = O(1)
inline void SwapIntegers_binary(int* x, int* y); // = O(1)

void Task_1_4(void);
void SqEquation_print(Coefs c); // = O(1)
int SqEquation_solve(Coefs c, double* out_x1, double* out_x2, double* out_D); // = O(sqrt())

void Task_1_7(void);
ChessCell NewCell(unsigned int rank, unsigned int file); // = O(1)
ChessCell ReadCell(char* message); // = O(1), до бесконечности, т.к. цикл повторяется при некорректном вводе
inline char* CellColor_ToString(ChessCell c); // = O(1)

void Task_1_13(void);
void Task_1_13a(int count); // = O(count)
void Task_1_13b(int count); // = O(count)
int GetSystemRand(int digits); // = O(digits)
void BootMyRand(unsigned int starter); // = O(1)
int GetMyRand(void);

void Task_1_14(void);
bool IsAutomorph(int num); // = O(lg num) = O(log num)

#endif