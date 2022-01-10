#pragma once

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
void CurrentReport(int* arr, int count);

void RunLesson3(void);
void Lesson3_part1_simpleSorting(void);
void Lesson3_part2_insertion(void);
ObserveParams RunSorting(int (*sorting)(int*, int, int(*)(const void*, const void*)));
void RunSearchTest(int* arr, int count, int search, int(*SearchMethod)(int*, int, int));

int* InitNewArray(int count);
int* GetArrayCopy(int* source, int count);
void PrintArray(char* presentation, int* arr, int count);

int compare_int_asc(const void* left, const void* right);
int compare_int_desc(const void* left, const void* right);
void swap_bytewise(void* arr, int index1, int index2, size_t elSize);

void sort_bubble_simple_observed(int* arr, int count, int (*predicate)(int, int));
void sort_shaker_simple_observed(int* arr, int count, int (*predicate)(int, int));
void sort_bubble_trail_observed(int* arr, int count, int (*predicate)(int, int));
void sort_shaker_trail_observed(int* arr, int count, int (*predicate)(int, int));
void sort_selection_observed(int* arr, int count, int (*predicate)(int, int));

void sort_bubble_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
void sort_shaker_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
void sort_bubble_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
void sort_shaker_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));
void sort_selection(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*));

int search_binary(int* arr, int count, int search);

void merge_BinaryInsertionSort(int** arr, int length, int* newValues, int count);
void BinaryInsertionSort(int* arr, int length);
int search_insertPosition_binary(int* arr, int count, const int value);
int GoRightTilDifferent(int* fromPos, int edge);