#ifndef LESSON3_H
#define LESSON3_H

// ������� � ������� �3.
// 1.  ����������� �������������� ����������� ����������.
//     �������� ���������� �������� ��������� ���������������� � �� ���������������� ���������.
//     �������� ������� ����������, ������� ���������� ���������� ��������.
// 2*. ����������� ��������� ����������.
// 3.  ����������� �������� �������� ������ � ���� �������, ������� ���������� ��������������� ������.
//     ������� ���������� ������ ���������� �������� ��� -1, ���� ������� �� ������.
// 4*. ���������� ���������� �������� ��� ������ �� ���������� � �������� ��� � ��������������� ���������� ���������.
// 5**. ����������� ���������� ���������, ��������� �������� �����.

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
ObserveParams RunSorting(void (*sorting)(int*, int, int(*)(const void*, const void*))); // = O(sorting()), ��. ����
void RunSearchTest(int* arr, int count, int search, int(*SearchMethod)(int*, int, int)); // ~ O(SearchMethod(_, count, _))

int* InitNewArray(int count); // = O(count)
int* GetArrayCopy(int* source, int count); // = O(count)
void PrintArray(char* presentation, int* arr, int count); // = O(count) ��� count <= 40 ; = O(1) ��� count > 40

int compare_int_asc(const void* left, const void* right); // = O(1)
int compare_int_desc(const void* left, const void* right); // = O(1)
void swap_bytewise(void* arr, int index1, int index2, size_t elSize); // = O(elSize)

void sort_bubble_simple_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_shaker_simple_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_bubble_trail_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_shaker_trail_observed(int* arr, int count, int (*predicate)(const void*, const void*));
void sort_selection_observed(int* arr, int count, int (*predicate)(const void*, const void*));

void sort_bubble_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), ��. ����
void sort_shaker_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), ��. ����
void sort_bubble_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), ��. ���� � ����
void sort_shaker_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), ��. ���� � ����
void sort_selection(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)); // = O(count^2) * O(elSize)  ~ O(count^2), ��. ����

// �.�. �������������� ������ �������� ��������, ��� ������ ������� ������� ���������� ������������ ��������� � ������� �� ��������� ��������� ����������������� �������;
// � ������� _trail ��� ������ ��������� ������, ��� ���� ���������� �������� �������� ����� �� ����� ��������� ���������� ������ �������� �������� � ������:
//    � ������ ���������� �������� ��������� ����� rand()%100 (�� 0 �� 99) - ���������� �������� �������� ����� �� ��������� 100;

int search_binary(int* arr, int count, int search); // = O(log count), ��. ����

void merge_BinaryInsertionSort(int** arr, int length, int* newValues, int count); // = O(count)
void BinaryInsertionSort(int* arr, int length); // = O(length * log length) + O(length) = O(length * log length), ��. ����
int search_insertPosition_binary(int* arr, int count, const int value); // = O(count * log count), ��. ����
int GoRightTilDifferent(int* fromPos, int edge); // = O(edge)

#endif