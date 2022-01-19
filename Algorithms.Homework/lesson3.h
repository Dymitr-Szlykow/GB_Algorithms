#ifndef LESSON3_H
#define LESSON3_H

// ЗАДАНИЯ к занятию №3.
// 1.  Попробовать оптимизировать пузырьковую сортировку.
//     Сравнить количество операций сравнения оптимизированной и не оптимизированной программы.
//     Написать функции сортировки, которые возвращают количество операций.
// 2*. Реализовать шейкерную сортировку.
// 3.  Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
//     Функция возвращает индекс найденного элемента или -1, если элемент не найден.
// 4*. Подсчитать количество операций для каждой из сортировок и сравнить его с асимптотической сложностью алгоритма.
// 5**. Реализовать сортировку вставками, используя бинарный посик.

typedef struct observeParams {
	int compareCounter, swapCounter,
		compareLast, swapLast,
		ifCounter, assignCounter,
		sorting_OuterCycleCounter, sorting_InnerCycleConter,
		search_CycleCounter, search_result,
		O;
	char* SortFuncPresentation;
	char* SearchFuncPresentation;
} ObserveParams;

void ResetObserveParams(void);
void CurrentReport(int* arr, int count); // = O(1)

void RunLesson3(void);
void Lesson3_part1_simpleSorting(void);
void Lesson3_part2_insertion(void);
ObserveParams RunSorting(void (*sorting)(int*, int, int(*)(const void*, const void*))); // = O(sorting()), см. тело
void RunSearchTest(int* arr, int count, int search, int(*SearchMethod)(int*, int, int)); // ~ O(SearchMethod(_, count, _))

int* InitNewArray(int count); // = O(count)
int* GetArrayCopy(int* source, int count); // = O(count)
void PrintArray(char* presentation, int* arr, int count); // = O(count) при count <= 40 ; = O(1) при count > 40

int compare_int_asc(const void* left, const void* right); // = O(1)
int compare_int_desc(const void* left, const void* right); // = O(1)
void swap_bytewise(void* arr, int index1, int index2, size_t elSize); // = O(elSize)

void sort_bubble_simple_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_shaker_simple_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_bubble_trail_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_shaker_trail_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_selection_observed(int* arr, int count, int (*predicate)(const void*, const void*));

void sort_bubble_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), см. тело
void sort_shaker_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), см. тело
void sort_bubble_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), см. тело и ниже
void sort_shaker_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), см. тело и ниже
void sort_selection(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), см. тело

// т.к. переставляются только соседние элементы, для первых четырех методов количество перестановок одинаково и зависит от начальной частичной отсортированности массива;
// в методах _trail три уровня вложенных циклов, при этом количество проходов внешнего цикла не будет превышать количества разных значений входящих в массив:
//    в данной программме значения элементов равны rand()%100 (от 0 до 99) - количество проходов внешного цикла не превышает 100;

int search_binary(int* arr, int count, int search); // = O(log count), см. тело

void merge_BinaryInsertionSort(int** arr, int length, int* newValues, int count); // = O(count)
void BinaryInsertionSort(int* arr, int length); // = O(length * log length) + O(length) = O(length * log length), см. тело
int search_insertPosition_binary(int* arr, int count, const int value); // = O(count * log count), см. тело
int GoRightTilDifferent(int* fromPos, int edge); // = O(edge)

#endif