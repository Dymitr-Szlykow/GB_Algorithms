#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lesson1.c"

#define bool int
#define true 1
#define false 0

#define _ArraySize 15
#define _DoExplicit true

typedef struct observeParams ObserveParams;
inline void ResetObserveParams(void);
inline void CurrentReport(int* arr, int count);

inline void RunLesson3(void);
inline ObserveParams RunSorting(int (*sorting)(int*,int,int(*)(int,int)));
inline int* InitNewArray(int count);
inline int* GetArrayCopy(int* source, int count);
inline void PrintArray(char* presentation, int* arr, int count);

inline int compare_asc(const void* left, const void* right);
inline int compare_desc(const void* left, const void* right);
inline void swap_bytewise(void* arr, int index1, int index2, size_t elSize);

inline void sort_bubble_simple_observed(int* arr, int count, int (*predicate)(int,int));
inline void sort_shaker_simple_observed(int* arr, int count, int (*predicate)(int,int));
inline void sort_bubble_trail_observed(int* arr, int count, int (*predicate)(int,int));
inline void sort_shaker_trail_observed(int* arr, int count, int (*predicate)(int,int));
inline void sort_selection_observed(int* arr, int count, int (*predicate)(int,int));

inline void sort_bubble_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
inline void sort_shaker_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
inline void sort_bubble_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
inline void sort_shaker_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
inline void sort_selection(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));


struct observeParams {
	int compareCounter, swapCounter,
		compareLast, swapLast,
		ifCounter, assignCounter,
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
	printf("\n");

	ObserveParams
		observer1 = RunSorting(sort_bubble_simple_observed),
		observer2 = RunSorting(sort_shaker_simple_observed),
		observer3 = RunSorting(sort_bubble_trail_observed),
		observer4 = RunSorting(sort_shaker_trail_observed),
		observer5 = RunSorting(sort_selection_observed);

	if (_DoExplicit) {
		printf("=========================================================\n");
		printf("1. %s\n", observer1.FuncPresentation);
		printf("2. %s\n", observer2.FuncPresentation);
		printf("3. %s\n", observer3.FuncPresentation);
		printf("4. %s\n", observer4.FuncPresentation);
		printf("5. %s\n", observer5.FuncPresentation);
	}

	printf("\nДля размера %4d\t\t%6d. %6d. %6d. %6d. %6d.\n", _ArraySize, 1, 2, 3, 4, 5);
	printf("  проходов внешних\t\t%7d %7d %7d %7d %7d\n",
		observer1.outerCycleCounter, observer2.outerCycleCounter, observer3.outerCycleCounter, observer4.outerCycleCounter, observer5.outerCycleCounter);
	printf("  проходов внутренних\t\t%7d %7d %7d %7d %7d\n",
		observer1.innerCycleConter, observer2.innerCycleConter, observer3.innerCycleConter, observer4.innerCycleConter, observer5.innerCycleConter);
	printf("  сравнений элементов\t\t%7d %7d %7d %7d %7d\n",
		observer1.compareCounter, observer2.compareCounter, observer3.compareCounter, observer4.compareCounter, observer5.compareCounter);
	printf("  обменов элементов\t\t%7d %7d %7d %7d %7d\n",
		observer1.swapCounter, observer2.swapCounter, observer3.swapCounter, observer4.swapCounter, observer5.swapCounter);
	printf("  всего проверок\t\t%7d %7d %7d %7d %7d\n",
		observer1.ifCounter, observer2.ifCounter, observer3.ifCounter, observer4.ifCounter, observer5.ifCounter);
	printf("  вспомогательных присваиваний\t%7d %7d %7d %7d %7d\n",
		observer1.assignCounter, observer2.assignCounter, observer3.assignCounter, observer4.assignCounter, observer5.assignCounter);

	free(_SourceArray);
}

/// <summary>обнуляет параметры глобального "наблюдателя"</summary>
void ResetObserveParams() {
	_observer.compareCounter = 0;
	_observer.compareLast = 0;
	_observer.swapCounter = 0;
	_observer.swapLast = 0;
	_observer.ifCounter = 0;
	_observer.assignCounter = 0;
	_observer.outerCycleCounter = 0;
	_observer.innerCycleConter = 0;
}

/// <summary>копирует глобальный массив и производит сортировку</summary>
/// <param name="task">- функция сортировки</param>
/// <param name="presentation">- сообщение для представления массива при выводе</param>
/// <returns>параметры наблюдения для оценок сортировки</returns>
ObserveParams RunSorting(int (*sorting)(int*,int,int(*)(int,int))) {
	ResetObserveParams();
	int* runningArr = GetArrayCopy(_SourceArray, _ArraySize);

	//sort_selection(runningArr, _ArraySize, sizeof(int), compare_asc); // для проверки и отладки собранных методов

	sorting(runningArr, _ArraySize, compare_asc);
	if (_DoExplicit) printf("  всего       сравн %3d, обм %2d\n\n", _observer.compareCounter, _observer.swapCounter);
	else PrintArray(_observer.FuncPresentation, runningArr, _ArraySize);

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
	for (i = 0; i < count; i++) {
		if (i > 40) {
			printf("...");
			break;
		}
		else printf("%3d ", *(arr + i));
	}
	printf("\n");
}


/// <summary>текущий отчет во время сортировки</summary>
void CurrentReport(int* arr, int count) {
	printf("  ход %2d-%3d,", _observer.outerCycleCounter, _observer.innerCycleConter);
	printf(" сравн %2d,", _observer.compareCounter - _observer.compareLast);
	printf(" обм %2d", _observer.swapCounter - _observer.swapLast);
	PrintArray("", arr, count);
	_observer.compareLast = _observer.compareCounter;
	_observer.swapLast = _observer.swapCounter;
}


/// <summary>сравнение восходящее</summary>
/// <returns>&gt;0 - левое больше - менять;&#10;0 - равны;&#10;&lt;0 - правое больше - пропустить</returns>
int compare_asc(const void* left, const void* right) {
	int temp = *(int*)left - *(int*)right;
	if (temp > 0) return 1;
	else if (temp == 0) return 0;
	else return -1;
}

/// <summary>сравнение нисходящее</summary>
/// <returns>&gt;0 - правое больше - менять;&#10;0 - равны;&#10;&lt;0 - левое больше - пропустить</returns>
int compare_desc(const void* left, const void* right) {
	int temp = *(int*)right - *(int*)left;
	if (temp > 0) return 1;
	else if (temp == 0) return 0;
	else return -1;
}

/// <summary>побайтовая перестановка элементов</summary>
void swap_bytewise(void* arr, int index1, int index2, size_t elSize) {
	int byte;
	for (byte = 0; byte < elSize; byte++) {
		*((unsigned char*)arr + index1 * elSize + byte) ^= *((unsigned char*)arr + index2 * elSize + byte);
		*((unsigned char*)arr + index2 * elSize + byte) ^= *((unsigned char*)arr + index1 * elSize + byte);
		*((unsigned char*)arr + index1 * elSize + byte) ^= *((unsigned char*)arr + index2 * elSize + byte);
	}
}


/// <summary>простая сортировка пузырьком</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_bubble_simple_observed(int* arr, int count, int (*predicate)(int,int)) {
	_observer.FuncPresentation = "простой пузырек \t"; // объявляет себя наблюдателю
	if (_DoExplicit) PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив

	int startIndex = 0,
		endIndex = count - 1,
		pos;

	while (1) { // разобранный for(startIndex=0; startIndex!=endIndex; endIndex--)
		_observer.outerCycleCounter++;

		_observer.assignCounter++;
		pos = startIndex;
		while (1) { // разобранный for(pos=startIndex; pos<endIndex; pos++)
			_observer.innerCycleConter++;

			_observer.compareCounter++;
			_observer.ifCounter++;
			if (predicate(arr[pos], arr[pos + 1]) > 0) {
				_observer.swapCounter++;
				SwapIntegers_binary(arr + pos, arr + pos + 1); // см. "lesson1.c"
			}
			_observer.assignCounter++;
			pos++;
			_observer.ifCounter++;
			if (pos == endIndex) break;
		}
		_observer.assignCounter++;
		endIndex--;

		if (_DoExplicit) CurrentReport(arr, count);

		_observer.ifCounter++;
		if (startIndex >= endIndex) break;
	}

	if (!_DoExplicit) printf("1. ");
}

/// <summary>простая сортировка пузырьком (собранный вариант)</summary>
void sort_bubble_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int startIndex = 0,
		endIndex = count - 1,
		pos;

	for (startIndex = 0; startIndex != endIndex; endIndex--) {
		for (pos = startIndex; pos < endIndex; pos++) {
			if (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize) > 0)
				swap_bytewise(arr, pos, pos + 1, elSize);
		}
	}
}


/// <summary>сортировка типа shaker: обходит массив змейкой</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_shaker_simple_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.FuncPresentation = "shaker  \t\t"; // объявляет себя наблюдателю
	if (_DoExplicit) PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив

	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex;

	while (1) {
		_observer.outerCycleCounter++;

		// проход вправо
		_observer.ifCounter++;
		if (pos == leftIndex) {
			while (1) {
				_observer.innerCycleConter++;

				_observer.compareCounter++;
				_observer.ifCounter++;
				if (predicate(arr[pos], arr[pos + 1]) > 0) {
					_observer.swapCounter++;
					SwapIntegers_binary(arr + pos, arr + pos + 1); // см. "lesson1.c"
				}
				_observer.ifCounter++;
				if (pos == rightIndex - 1) break;
				else {
					_observer.assignCounter++;
					pos++;
				}
			}
			_observer.assignCounter++;
			rightIndex--;
		}
		// проход влево
		else {
			_observer.ifCounter++;
			if (pos == rightIndex) {
				while (1) {
					_observer.innerCycleConter++;

					_observer.compareCounter++;
					_observer.ifCounter++;
					if (predicate(arr[pos - 1], arr[pos]) > 0) {
						_observer.swapCounter++;
						SwapIntegers_binary(arr + pos - 1, arr + pos); // см. "lesson1.c"
					}
					_observer.ifCounter++;
					if (pos == leftIndex + 1) break;
					else {
						_observer.assignCounter++;
						pos--;
					}
				}
				_observer.assignCounter++;
				leftIndex++;
			}
		}

		if (_DoExplicit) CurrentReport(arr, count);

		_observer.ifCounter++;
		if (leftIndex >= rightIndex) break;
	}

	if (!_DoExplicit) printf("2. ");
}

/// <summary>сортировка типа shaker (собранный вариант)</summary>
void sort_shaker_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex;

	while (leftIndex < rightIndex) {
		if (pos == leftIndex) {
			for (; pos < rightIndex; pos++) {
				if (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize) > 0) {
					swap_bytewise(arr, pos, pos + 1, elSize);
				}
			}
			pos = --rightIndex;
		}

		else if (pos == rightIndex) {
			for (; pos > leftIndex; pos--) {
				if (predicate((char*)arr + (pos - 1) * elSize, (char*)arr + pos * elSize) > 0) {
					swap_bytewise(arr, pos - 1, pos, elSize);
				}
			}
			pos = ++leftIndex;
		}
	}
}


/// <summary>сортировка пузырьком со "слипанием": протягивает одинаковые значения группой</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_bubble_trail_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.FuncPresentation = "пузырек со слипанием\t"; // объявляет себя наблюдателю
	if (_DoExplicit) PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив

	int startIndex = 0,
		endIndex = count - 1,
		pos, trail, comparison, i;

	while (1) {
		_observer.outerCycleCounter++;

		_observer.assignCounter += 2;
		pos = startIndex;
		trail = 0;
		while (1) { // разобранный for(pos=startIndex; pos<endIndex; pos++)
			_observer.innerCycleConter++;

			_observer.compareCounter++;
			comparison = predicate(arr[pos], arr[pos + 1]);

			_observer.ifCounter++;
			if (comparison > 0) {
				_observer.assignCounter += 2;
				i = 0;
				while (1) { // разобранный for(i=0; i<=trail; i++)
					_observer.swapCounter++;
					SwapIntegers_binary(arr + pos - i, arr + pos - i + 1); // см. "lesson1.c"

					_observer.assignCounter++;
					i++;

					_observer.ifCounter++;
					if (i > trail) break;
				}
				pos++;
			}
			else {
				_observer.ifCounter++;
				if (comparison == 0) {
					_observer.assignCounter += 2;
					trail++;
					pos++;
				}
				else {
					_observer.assignCounter += 2;
					trail = 0;
					pos++;
				}
			}

			_observer.ifCounter++;
			if (pos == endIndex) break;
		}
		_observer.assignCounter++;
		endIndex = endIndex - 1 - trail;

		if (_DoExplicit) CurrentReport(arr, count);

		_observer.ifCounter++;
		if (startIndex >= endIndex) break;
	}

	if (!_DoExplicit) printf("3. ");
}

/// <summary>сортировка пузырьком со "слипанием" (собранный вариант)</summary>
void sort_bubble_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int startIndex = 0,
		endIndex = count - 1,
		pos, trail, i;

	while (startIndex < endIndex) {
		trail = 0;
		for (pos = startIndex; pos < endIndex; pos++) {
			switch (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize)) {
			case 1:
				for (i = 0; i <= trail; i++)
					swap_bytewise(arr, pos - i, pos - i + 1, elSize);
				break;
			case 0:
				trail++;
				break;
			case -1:
				trail = 0;
				break;
			}
		}
		endIndex = endIndex - 1 - trail;
	}
}


/// <summary>сортировка типа shaker со "слипанием": обходит массив змейкой, протягивает одинаковые значения группой</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_shaker_trail_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.FuncPresentation = "shaker со слипанием \t"; // объявляет себя наблюдателю
	if (_DoExplicit) PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив

	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex, trail, comparison, i;

	while (1) {
		_observer.outerCycleCounter++;

		_observer.assignCounter++;
		trail = 0;

		// проход вправо
		_observer.ifCounter++;
		if (pos == leftIndex) {
			while (1) {
				_observer.innerCycleConter++;

				_observer.compareCounter++;
				comparison = predicate(arr[pos], arr[pos + 1]);

				_observer.ifCounter++;
				if (comparison > 0) {  // разобранный switch
					_observer.assignCounter += 2;
					i = 0;
					while (1) { // разобранный for(i=0; i<=trail; i++)
						_observer.swapCounter++;
						SwapIntegers_binary(arr + pos - i, arr + pos - i + 1); // см. "lesson1.c"

						_observer.assignCounter++;
						i++;

						_observer.ifCounter++;
						if (i > trail) break;
					}
					pos++;
				}
				else {
					_observer.ifCounter++;
					if (comparison == 0) {
						_observer.assignCounter += 2;
						trail++;
						pos++;
					}
					else {
						_observer.assignCounter += 2;
						trail = 0;
						pos++;
					}
				}
				_observer.ifCounter++;
				if (pos == rightIndex) {
					_observer.assignCounter += 2;
					pos = rightIndex = rightIndex - 1 - trail;
					break;
				}
			}
		}
		// проход влево
		else {
			_observer.ifCounter++;
			if (pos == rightIndex) {
				while (1) {
					_observer.innerCycleConter++;
					_observer.compareCounter++;
					comparison = predicate(arr[pos - 1], arr[pos]);

					_observer.ifCounter++;
					if (comparison > 0) {  // разобранный switch
						_observer.assignCounter += 2;
						i = 0;
						while (1) { // разобранный for(i=0; i<=trail; i++)
							_observer.swapCounter++;
							SwapIntegers_binary(arr + pos + i - 1, arr + pos + i); // см. "lesson1.c"

							_observer.assignCounter++;
							i++;

							_observer.ifCounter++;
							if (i > trail) break;
						}
						pos--;
					}
					else {
						_observer.ifCounter++;
						if (comparison == 0) {
							_observer.assignCounter += 2;
							trail++;
							pos--;
						}
						else {
							_observer.assignCounter += 2;
							trail = 0;
							pos--;
						}
					}
					_observer.ifCounter++;
					if (pos == leftIndex) {
						_observer.assignCounter += 2;
						pos = leftIndex = leftIndex + 1 + trail;
						break;
					}
				}
			}
		}

		if (_DoExplicit) CurrentReport(arr, count);

		_observer.ifCounter++;
		if (leftIndex >= rightIndex) break;
	}

	if(!_DoExplicit) printf("4. ");
}

/// <summary>сортировка "встряхиванием" со "слипанием" (собранный вариант)</summary>
void sort_shaker_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex, trail, i;

	while (leftIndex < rightIndex) {
		trail = 0;

		// проход вправо
		if (pos == leftIndex) {
			for (; pos < rightIndex; pos++) {
				switch (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize)) {
				case 1:
					for (i = 0; i <= trail; i++)
						swap_bytewise(arr, pos - i, pos - i + 1, elSize);
					break;
				case 0:
					trail++;
					break;
				case -1:
					trail = 0;
					break;
				}
			}
			pos = rightIndex = rightIndex - 1 - trail;
		}

		// проход влево
		else if (pos == rightIndex) {
			for (; pos > leftIndex; pos--) {
				switch (predicate((char*)arr + (pos - 1) * elSize, (char*)arr + pos * elSize)) {
				case 1:
					for (i = 0; i <= trail; i++)
						swap_bytewise(arr, pos + i - 1, pos + i, elSize);
					break;
				case 0:
					trail++;
					break;
				case -1:
					trail = 0;
				}
			}
			pos = leftIndex = leftIndex + 1 + trail;
		}
	}
}


/// <summary>сортировка перебором</summary>
/// <param name="arr">- массив для сортировки</param>
/// <param name="count">- размер массива</param>
/// <param name="predicate">- используемая при сортировке функция сравнения</param>
void sort_selection_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.FuncPresentation = "перебор \t\t"; // объявляет себя наблюдателю
	if (_DoExplicit) PrintArray(_observer.FuncPresentation, arr, count); // выводит исходный массив

	int startIndex = 0,
		endIndex = count - 1,
		pos, tempIndex;

	while (1) { // разобранный for(startIndex=0; startIndex!=endIndex; startIndex++)
		_observer.outerCycleCounter++;

		_observer.assignCounter += 2;
		tempIndex = pos = startIndex;
		while (1) { // разобранный for(tempIndex=pos=startIndex; pos<endIndex; pos++)
			_observer.innerCycleConter++;

			_observer.compareCounter++;
			_observer.ifCounter++;
			if (predicate(arr[tempIndex], arr[pos]) > 0) {
				_observer.assignCounter++;
				tempIndex = pos;
			}
			_observer.assignCounter++;
			pos++;
			_observer.ifCounter++;
			if (pos == endIndex) break;
		}
		_observer.ifCounter++;
		if (startIndex != tempIndex) {
			_observer.swapCounter++;
			SwapIntegers_binary(arr + startIndex, arr + tempIndex); // см. "lesson1.c"
		}
		_observer.assignCounter++;
		startIndex++;

		if (_DoExplicit) CurrentReport(arr, count);

		_observer.ifCounter++;
		if (startIndex == endIndex) break;
	}

	if (!_DoExplicit) printf("5. ");
}

/// <summary>сортировка перебором (собранный вариант)</summary>
void sort_selection(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int startIndex,
		endIndex = count - 1,
		pos, tempIndex;

	for (startIndex = 0; startIndex < endIndex; startIndex++) {
		for (tempIndex = pos = startIndex; pos <= endIndex; pos++) {
			if (predicate((char*)arr + tempIndex * elSize, (char*)arr + pos * elSize) > 0) {
				tempIndex = pos;
			}
		}
		if (startIndex != tempIndex) swap_bytewise(arr, startIndex, tempIndex, elSize);
	}
}

// 3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
// Функция возвращает индекс найденного элемента или -1, если элемент не найден.