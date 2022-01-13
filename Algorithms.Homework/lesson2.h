#ifndef LESSON2_H
#define LESSON2_H

// ЗАДАНИЯ к занятию №2.
// 1. Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
// 2. Реализовать функцию возведения числа a в степень b :
//    a.без рекурсии;
//    b.рекурсивно;
//    c.* рекурсивно, используя свойство четности степени.
// 3. * *Исполнитель Калькулятор преобразует целое число, записанное на экране.
//    У исполнителя две команды, каждой команде присвоен номер: Прибавь 1, Умножь на 2.
//    Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза.
//    Сколько существует программ, которые число 3 преобразуют в число 20 ?

void Task_2_1(void);
int AsBinary_HeadOn_loop(int number, unsigned int maxlength, char* out); // = O(2 * log number) = O(log number), см. тело
int AsBinary_recursive(int* number, unsigned int* maxlength, char* out); // = O(log number)

void Task_2_2(void);
int Multiply_loop(int first, int second); // = O(n), n = first < second ? first : second  ;  сложность по времени зависит от меньшего из аргументов, см. тело, строка 142
double Power_loop(double number, unsigned int power); // = O(power), см. тело
	// O(Power_loop(_,power))  формально эквивалентен  O(log power) + O(power)
	// в действительности power сокращается логарифмически пока четное, после чего сокращается линейно
	// худший случай для первого цикла - степень двойки, тогда второй цикл проходит 0-1 раз  =>  O(Power_loop(_,power)) ~ O(log power)
	// худший случай для второго цикла - power нечетное, тогда тело первого цикла не выполняется  =>  O(Power_loop(_,power)) ~ O(power)
double Power_recursive(double number, unsigned int power); // = O(power)
	// тот же алгоритм, что Power_loop(), рекурсивное исполнение

void Task_2_3(void); // not implemented

#endif