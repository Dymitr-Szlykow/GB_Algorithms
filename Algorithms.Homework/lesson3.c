#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lesson1.c"

#define bool int
#define true 1
#define false 0

#define _ArraySize 11
#define _DoExplicit true

typedef struct observeParams ObserveParams;
inline void ResetObserveParams(void);
inline void NotchObserveParams(void);
inline void ReportObserveParams(ObserveParams* obs);
inline void CurrentReport(int* arr, int count);

inline void RunLesson3(void);
inline ObserveParams RunSorting(int (*sorting)(int*,int,int(*)(int,int)));
inline int* InitNewArray(int count);
inline int* GetArrayCopy(int* source, int count);
inline void PrintArray(char* presentation, int* arr, int count);

inline int compare_asc(int left, int right);
inline int compare_desc(int left, int right);

inline void sort_bubble_simple(int* arr, int count, int (*predicate)(int,int));
inline void sort_shaker_simple(int* arr, int count, int (*predicate)(int, int));


struct observeParams {
	int compareCounter, swapCounter,
		compareLast, swapLast,
		outerCycleCounter, innerCycleConter;
	char* FuncPresentation;
};


int* _SourceArray;
ObserveParams _observer;


// ЗАДАНИЯ.
// 1.  Попробовать оптимизировать пузырьковую сортировку.
//     Сравнить количество операций сравнения оптимизированной и не оптимизированной программы.
//     Написать функции сортировки, которые возвращают количество операций.
// 2*. Реализовать шейкерную сортировку.
// 3.  Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
//     Функция возвращает индекс найденного элемента или -1, если элемент не найден.
// 4*. Подсчитать количество операций для каждой из сортировок и сравнить его с асимптотической сложностью алгоритма.


/// <summary>lesson 3 submain function</summary>
void RunLesson3() {
	_SourceArray = InitNewArray(_ArraySize);
	PrintArray("Исходный массив \t", _SourceArray, _ArraySize);

	ObserveParams
		observer1 = RunSorting(sort_bubble_simple),
		observer2 = RunSorting(sort_shaker_simple);
	//	observer3 = RunSorting(Task_3_3);

	ReportObserveParams(&observer1);
	ReportObserveParams(&observer2);
	//ReportObserveParams(&observer3);

	free(_SourceArray);
}

/// <summary>обнуляет параметры глобального "наблюдателя"</summary>
void ResetObserveParams() {
	_observer.compareCounter = 0;
	_observer.compareLast = 0;
	_observer.swapCounter = 0;
	_observer.swapLast = 0;
	_observer.outerCycleCounter = 0;
	_observer.innerCycleConter = 0;
}

/// <summary>"зарубка"</summary>
void NotchObserveParams() {
	_observer.compareLast = _observer.compareCounter;
	_observer.swapLast = _observer.swapCounter;
}

/// <summary>выводит отчет по параметрам наблюдения</summary>
/// <param name="obs">- пакет параметров наблюдения</param>
void ReportObserveParams(ObserveParams* obs) {
	printf("\n%s.\n", obs->FuncPresentation);
	printf("    сравнений произведено: %d\n", obs->compareCounter);
	printf("    обменов произведено:   %d\n", obs->swapCounter);
}

/// <summary>копирует глобальный массив и производит сортировку</summary>
/// <param name="task">- функция сортировки</param>
/// <param name="presentation">- сообщение для представления массива при выводе</param>
/// <returns>параметры наблюдения для оценок сортировки</returns>
ObserveParams RunSorting(int (*sorting)(int*,int,int(*)(int,int))) {
	ResetObserveParams();
	int* runningArr = GetArrayCopy(_SourceArray, _ArraySize);

	sorting(runningArr, _ArraySize, compare_asc);

	free(runningArr);
	return _observer;
}

/// <summary>создает массив в динамической памяти и инициализирует случайными значениями</summary>
/// <param name="count">- длина массива</param>
/// <returns>указатель на массив в куче</returns>
int* InitNewArray(int count) {
	int* res = (int*)malloc(count * sizeof(int));

	if (res != NULL) {
		int i;
		srand(time(NULL));
		for (i = 0; i < count; i++) {
			*(res + i) = rand() % 100;
		}
	}
	return res;
}

/// <summary>создает копию указанного массива в динамической памяти</summary>
/// <param name="source">- массив-источник копирования</param>
/// <param name="count">- длина массива-источника и, соответственно, копии</param>
/// <returns>указатель на копированный массив в куче</returns>
int* GetArrayCopy(int* source, int count) {
	int* res = (int*)malloc(count * sizeof(int));

	if (res != NULL) {
		int i;
		for (i = 0; i < count; i++) {
			*(res + i) = *(source + i);
		}
	}
	return res;
}

/// <summary>выводит до 40 первых членов массива</summary>
/// <param name="presentation">- сообщение для представления массива</param>
/// <param name="arr">- массив целых чисел</param>
/// <param name="count">- длина массива</param>
void PrintArray(char* presentation, int* arr, int count) {
	printf("%s\t", presentation);
	int i;
	for (i = 0; i < count && i < 40; i++) {
		printf("%3d ", *(arr + i));
	}
	if (i == 30) printf("...\n");
	else printf("\n");
}


/// <summary>текущий отчет во время сортировки</summary>
void CurrentReport(int* arr, int count) {
	printf("  ход %2d-%2d,", _observer.outerCycleCounter, _observer.innerCycleConter);
	printf(" сравн %2d,", _observer.compareCounter - _observer.compareLast);
	printf(" обм %2d", _observer.swapCounter - _observer.swapLast);
	PrintArray("", arr, count);
}


/// <summary>сравнеие восходящее</summary>
/// <returns>&gt;0 - левое больше - менять;&#10;0 - равны;&#10;&lt;0 - правое больше - пропустить</returns>
int compare_asc(int left, int right) {
	return left - right;
}

/// <summary>сравнеие нисходящее</summary>
/// <returns>&gt;0 - правое больше - менять;&#10;0 - равны;&#10;&lt;0 - левое больше - пропустить</returns>
int compare_desc(int left, int right) {
	return right - left;
}

/// <summary>простая сортировка пузырьком</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_bubble_simple(int* arr, int count, int (*predicate)(int,int)) {
	_observer.FuncPresentation = "простой пузырек \t"; // объявляет себя наблюдателю
	if (_DoExplicit) {
		printf("\n");
		PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив
	}

	int startIndex = 0,
		endIndex = count - 1,
		pos;

	while (startIndex != endIndex) {
		_observer.outerCycleCounter++;

		for (pos = startIndex; pos < endIndex; pos++) {
			_observer.compareCounter++;
			if (predicate(arr[pos], arr[pos + 1]) > 0) {
				_observer.swapCounter++;
				SwapIntegers_binary(arr + pos, arr + pos + 1); // см. "lesson1.c"
			}
		}
		endIndex--;

		if (_DoExplicit) CurrentReport(arr, count);
		NotchObserveParams();
	}

	if (_DoExplicit) printf("  всего      сравн %2d, обм %2d\n", _observer.compareCounter, _observer.swapCounter);
}

/// <summary>сортировка типа shaker</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_shaker_simple(int* arr, int count, int (*predicate)(int, int)) {
	_observer.FuncPresentation = "shaker\t\t\t"; // объявляет себя наблюдателю
	if (_DoExplicit) {
		printf("\n");
		PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив
	}

	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex;

	while (leftIndex != rightIndex) {
		_observer.outerCycleCounter++;

		if (pos == leftIndex) {
			while (1) {
				_observer.compareCounter++;
				if (predicate(arr[pos], arr[pos + 1]) > 0) {
					_observer.swapCounter++;
					SwapIntegers_binary(arr + pos, arr + pos + 1); // см. "lesson1.c"
				}
				if (pos == rightIndex - 1) break;
				else pos++;
			}
			rightIndex--;
		}
		else if (pos == rightIndex) {
			while (1) {
				_observer.compareCounter++;
				if (predicate(arr[pos - 1], arr[pos]) > 0) {
					_observer.swapCounter++;
					SwapIntegers_binary(arr + pos - 1, arr + pos); // см. "lesson1.c"
				}
				if (pos == leftIndex + 1) break;
				else pos--;
			}
			leftIndex++;
		}

		if (_DoExplicit) CurrentReport(arr, count);
		NotchObserveParams();
	}

	if (_DoExplicit) printf("  всего      сравн %2d, обм %2d\n", _observer.compareCounter, _observer.swapCounter);
}

// 1. Попробовать оптимизировать пузырьковую сортировку.
// Сравнить количество операций сравнения оптимизированной и не оптимизированной программы.
// Написать функции сортировки, которые возвращают количество операций.
// 
// 2. *Реализовать шейкерную сортировку.
// 
// 3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
// Функция возвращает индекс найденного элемента или -1, если элемент не найден.