#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lesson1.h"
#include "lesson3.h"

#define _ArraySize 15
#define _DoExplicit true

// ������� � ������� �3.
// 1.  ����������� �������������� ����������� ����������.
//     �������� ���������� �������� ��������� ���������������� � �� ���������������� ���������.
//     �������� ������� ����������, ������� ���������� ���������� ��������.
// 2*. ����������� ��������� ����������.
// 3.  ����������� �������� �������� ������ � ���� �������, ������� ���������� ��������������� ������.
//     ������� ���������� ������ ���������� �������� ��� -1, ���� ������� �� ������.
// 4*. ���������� ���������� �������� ��� ������ �� ���������� � �������� ��� � ��������������� ���������� ���������.
// 5**. ����������� ���������� ���������, ��������� �������� �����.


int* _SourceArray;
ObserveParams _observer;


/// <summary>lesson 3 submain function</summary>
void RunLesson3() {
	srand(time(NULL));
	_SourceArray = InitNewArray(_ArraySize);

	Lesson3_part1_simpleSorting();
	printf("\n������� ����� ������, ����� ����������... ");
	getch();

	system("cls");
	Lesson3_part2_insertion();

	free(_SourceArray);
}

/// <summary>��������� ����������, ������ ��������� ����������</summary>
void Lesson3_part1_simpleSorting() {
	PrintArray("�������� ������ \t", _SourceArray, _ArraySize);
	printf("\n");

	ObserveParams
		observer1 = RunSorting(sort_bubble_simple_observed),
		observer2 = RunSorting(sort_shaker_simple_observed),
		observer3 = RunSorting(sort_bubble_trail_observed),
		observer4 = RunSorting(sort_shaker_trail_observed),
		observer5 = RunSorting(sort_selection_observed);

	if (_DoExplicit) {
		printf("=========================================================\n");
		printf("1. %s\n", observer1.SortFuncPresentation);
		printf("2. %s\n", observer2.SortFuncPresentation);
		printf("3. %s\n", observer3.SortFuncPresentation);
		printf("4. %s\n", observer4.SortFuncPresentation);
		printf("5. %s\n", observer5.SortFuncPresentation);
	}

	printf("\n��� ������� %4d\t\t%6d. %6d. %6d. %6d. %6d.\n", _ArraySize, 1, 2, 3, 4, 5);
	printf("  �������� �������\t\t%7d %7d %7d %7d %7d\n",
		observer1.sorting_OuterCycleCounter, observer2.sorting_OuterCycleCounter, observer3.sorting_OuterCycleCounter, observer4.sorting_OuterCycleCounter, observer5.sorting_OuterCycleCounter);
	printf("  �������� ����������\t\t%7d %7d %7d %7d %7d\n",
		observer1.sorting_InnerCycleConter, observer2.sorting_InnerCycleConter, observer3.sorting_InnerCycleConter, observer4.sorting_InnerCycleConter, observer5.sorting_InnerCycleConter);
	printf("  ��������� ���������\t\t%7d %7d %7d %7d %7d\n",
		observer1.compareCounter, observer2.compareCounter, observer3.compareCounter, observer4.compareCounter, observer5.compareCounter);
	printf("  ������� ���������\t\t%7d %7d %7d %7d %7d\n",
		observer1.swapCounter, observer2.swapCounter, observer3.swapCounter, observer4.swapCounter, observer5.swapCounter);
	printf("  ����� ��������\t\t%7d %7d %7d %7d %7d\n",
		observer1.ifCounter, observer2.ifCounter, observer3.ifCounter, observer4.ifCounter, observer5.ifCounter);
	printf("  ��������������� ������������\t%7d %7d %7d %7d %7d\n",
		observer1.assignCounter, observer2.assignCounter, observer3.assignCounter, observer4.assignCounter, observer5.assignCounter);

	printf("  ������ ��������� O(%i)\t%7d %7d %7d %7d %7d\n", _ArraySize,
		observer1.O, observer2.O, observer3.O, observer4.O, observer5.O);
	printf("  ��������� ���������\t\t%6d%% %6d%% %6d%% %6d%% %6d%%\n",
		100 * observer1.sorting_InnerCycleConter / observer1.O,
		100 * observer2.sorting_InnerCycleConter / observer2.O,
		100 * observer3.sorting_InnerCycleConter / observer3.O,
		100 * observer4.sorting_InnerCycleConter / observer4.O,
		100 * observer5.sorting_InnerCycleConter / observer5.O);
}


void Lesson3_part2_insertion() {
	int legthBefore = 19, add = 5;
	int* arraySort, arrayNew;

	arraySort = InitNewArray(legthBefore);
	PrintArray("�������� ������ \t", arraySort, legthBefore);

	sort_bubble_trail(arraySort, legthBefore, sizeof(int), compare_int_asc);
	PrintArray("������������� ������\t", arraySort, legthBefore);

	arrayNew = InitNewArray(add);
	PrintArray("������ ����� ��������\t", arrayNew, add);

	merge_BinaryInsertionSort(&arraySort, legthBefore, arrayNew, add);
	PrintArray("������ �� ���������\t", arraySort, legthBefore + add);

	free(arraySort);
	free(arrayNew);
}


/// <summary>�������� ��������� ����������� "�����������"</summary>
void ResetObserveParams() {
	_observer.compareCounter = 0;
	_observer.compareLast = 0;
	_observer.swapCounter = 0;
	_observer.swapLast = 0;
	_observer.ifCounter = 0;
	_observer.assignCounter = 0;
	_observer.sorting_OuterCycleCounter = 0;
	_observer.sorting_InnerCycleConter = 0;
	_observer.search_CycleCounter = 0;
	_observer.search_result = 0;
	_observer.O = 0;
}

/// <summary>�������� ���������� ������ � ���������� ����������</summary>
/// <param name="task">- ������� ����������</param>
/// <param name="presentation">- ��������� ��� ������������� ������� ��� ������</param>
/// <returns>��������� ���������� ��� ������ ����������</returns>
ObserveParams RunSorting(int (*sorting)(int*,int,int(*)(const void*, const void*))) {
	ResetObserveParams();
	int* runningArr = GetArrayCopy(_SourceArray, _ArraySize);
	int searchtest = rand() % 100;

	sorting(runningArr, _ArraySize, compare_int_asc);
	if (_DoExplicit) printf("  �����   ����� %3d, ��� %2d\n", _observer.compareCounter, _observer.swapCounter);
	else PrintArray(_observer.SortFuncPresentation, runningArr, _ArraySize);

	RunSearchTest(runningArr, _ArraySize, searchtest, search_binary);
	printf("\n");

	free(runningArr);
	return _observer;
}

/// <summary>��������� �����, ������� ��������� ����������</summary>
/// <param name="searchValue">- ������� ��������</param>
/// <param name="SearchMethod">- ������� ��� ������</param>
void RunSearchTest(int* arr, int count, int searchValue, int(*SearchMethod)(int*,int,int)) {
	_observer.search_result = SearchMethod(arr, count, searchValue);
	printf("   %s\t- �������� %2d ", _observer.SearchFuncPresentation, searchValue);
	if (_observer.search_result < 0) printf("�� ���������� (�������� ������ %d)\n", _observer.search_CycleCounter);
	else printf("������� �� ������� %d (������ ������ %d)\n", _observer.search_result, _observer.search_CycleCounter);

	_observer.search_CycleCounter = 0;
	_observer.search_result = 0;
}


/// <summary>������� ������ � ������������ ������ � �������������� ���������� ����������</summary>
/// <returns>��������� �� ������ � ����</returns>
int* InitNewArray(int count) {
	int* res = (int*)malloc(count * sizeof(int));

	if (res != NULL) {
		int i;
		for (i = 0; i < count; i++) {
			*(res + i) = rand() % 100;
		}
	}
	return res;
}

/// <summary>������� ����� ���������� ������� � ������������ ������</summary>
/// <param name="source">- ������-�������� �����������</param>
/// <param name="count">- ����� �������-��������� �, ��������������, �����</param>
/// <returns>��������� �� ������������ ������ � ����</returns>
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

/// <summary>������� �� 40 ������ ������ �������</summary>
/// <param name="presentation">- ��������� ��� ������������� �������</param>
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


/// <summary>������� ����� �� ����� ����������</summary>
void CurrentReport(int* arr, int count) {
	printf("  ��� %2d,", _observer.sorting_OuterCycleCounter);
	printf(" ����� %3d,", _observer.compareCounter - _observer.compareLast);
	printf(" ��� %2d", _observer.swapCounter - _observer.swapLast);
	PrintArray("", arr, count);
	_observer.compareLast = _observer.compareCounter;
	_observer.swapLast = _observer.swapCounter;
}


/// <summary>��������� ����������</summary>
/// <returns>+1: ����� ������ - ������;&#10;0: �����;&#10;-1: ������ ������ - ����������</returns>
int compare_int_asc(const void* left, const void* right) {
	int temp = *(int*)left - *(int*)right;
	if (temp > 0) return 1;
	else if (temp == 0) return 0;
	else return -1;
}

/// <summary>��������� ����������</summary>
/// <returns>+1 - ������ ������ - ������;&#10;0 - �����;&#10;-1 - ����� ������ - ����������</returns>
int compare_int_desc(const void* left, const void* right) {
	int temp = *(int*)right - *(int*)left;
	if (temp > 0) return 1;
	else if (temp == 0) return 0;
	else return -1;
}

/// <summary>���������� ������������ ���������</summary>
void swap_bytewise(void* arr, int index1, int index2, size_t elSize) {
	int byte;
	for (byte = 0; byte < elSize; byte++) {
		*((char*)arr + index1 * elSize + byte) ^= *((char*)arr + index2 * elSize + byte);
		*((char*)arr + index2 * elSize + byte) ^= *((char*)arr + index1 * elSize + byte);
		*((char*)arr + index1 * elSize + byte) ^= *((char*)arr + index2 * elSize + byte);
	}
}


/// <summary>������� ���������� ���������</summary>
/// <param name="arr">- ����������� ������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_bubble_simple_observed(int* arr, int count, int (*predicate)(int,int)) {
	_observer.SortFuncPresentation = "������� ������� \t"; // ��������� ���� �����������
	_observer.O = pow(_ArraySize, 2);
	if (_DoExplicit) PrintArray(_observer.SortFuncPresentation, arr, count); // ������� �������� ������

	int startIndex = 0,
		endIndex = count - 1,
		pos, wrongPositions;

	while (1) { // ����������� for(startIndex=0; startIndex!=endIndex; endIndex--)
		_observer.sorting_OuterCycleCounter++;

		_observer.assignCounter += 2;
		wrongPositions = 0;
		pos = startIndex;
		while (1) { // ����������� for(pos=startIndex; pos<endIndex; pos++)
			_observer.sorting_InnerCycleConter++;

			_observer.compareCounter++;
			_observer.ifCounter++;
			if (predicate(arr + pos, arr + pos + 1) == 1) {
				_observer.assignCounter++;
				wrongPositions++;

				_observer.swapCounter++;
				SwapIntegers_binary(arr + pos, arr + pos + 1); // ��. "lesson1.c"
			}
			_observer.assignCounter++;
			pos++;
			_observer.ifCounter++;
			if (pos == endIndex) break;
		}
		_observer.assignCounter++;
		endIndex--;

		if (_DoExplicit) {
			CurrentReport(arr, count);
			if (wrongPositions == 0) printf("  ������������ �� ����������� - ������� ������ �������������\n");
		}

		_observer.ifCounter += 2;
		if (startIndex >= endIndex) break;
		if (wrongPositions == 0) break;
	}

	if (!_DoExplicit) printf("1. ");
}

/// <summary>������� ���������� ��������� (��������� �������)</summary>
void sort_bubble_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int startIndex = 0,
		endIndex = count - 1,
		pos, wrongPositions = -1;

	for (startIndex = 0; startIndex != endIndex && wrongPositions != 0; endIndex--) {
		wrongPositions = 0;
		for (pos = startIndex; pos < endIndex; pos++) {
			if (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize) == 1)
				wrongPositions++;
				swap_bytewise(arr, pos, pos + 1, elSize);
		}
	}
}


/// <summary>���������� ���� shaker: ������� ������ �������</summary>
/// <param name="arr">- ����������� ������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_shaker_simple_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.SortFuncPresentation = "������������    \t"; // ��������� ���� �����������
	_observer.O = pow(_ArraySize, 2);
	if (_DoExplicit) PrintArray(_observer.SortFuncPresentation, arr, count); // ������� �������� ������

	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex,
		wrongPositions;

	while (1) {
		_observer.sorting_OuterCycleCounter++;

		_observer.assignCounter++;
		wrongPositions = 0;

		// ������ ������
		_observer.ifCounter++;
		if (pos == leftIndex) {
			while (1) {
				_observer.sorting_InnerCycleConter++;

				_observer.compareCounter++;
				_observer.ifCounter++;
				if (predicate(arr + pos, arr + pos + 1) == 1) {
					_observer.assignCounter++;
					wrongPositions++;

					_observer.swapCounter++;
					SwapIntegers_binary(arr + pos, arr + pos + 1); // ��. "lesson1.c"
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
		// ������ �����
		else {
			_observer.ifCounter++;
			if (pos == rightIndex) {
				while (1) {
					_observer.sorting_InnerCycleConter++;

					_observer.compareCounter++;
					_observer.ifCounter++;
					if (predicate(arr + pos - 1, arr + pos) > 0) {
						_observer.assignCounter++;
						wrongPositions++;

						_observer.swapCounter++;
						SwapIntegers_binary(arr + pos - 1, arr + pos); // ��. "lesson1.c"
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

		if (_DoExplicit) {
			CurrentReport(arr, count);
			if (wrongPositions == 0) printf("  ������������ �� ����������� - ������� ������ �������������\n");
		}

		_observer.ifCounter += 2;
		if (leftIndex >= rightIndex) break;
		if (wrongPositions == 0) break;
	}

	if (!_DoExplicit) printf("2. ");
}

/// <summary>���������� ���� shaker (��������� �������)</summary>
void sort_shaker_simple(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex,
		wrongPositions = -1;

	while (leftIndex < rightIndex && wrongPositions != 0) {
		wrongPositions = 0;

		if (pos == leftIndex) {
			for (; pos < rightIndex; pos++) {
				if (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize) > 0) {
					wrongPositions++;
					swap_bytewise(arr, pos, pos + 1, elSize);
				}
			}
			pos = --rightIndex;
		}

		else if (pos == rightIndex) {
			for (; pos > leftIndex; pos--) {
				if (predicate((char*)arr + (pos - 1) * elSize, (char*)arr + pos * elSize) > 0) {
					wrongPositions++;
					swap_bytewise(arr, pos - 1, pos, elSize);
				}
			}
			pos = ++leftIndex;
		}
	}
}


/// <summary>���������� ��������� �� "���������": ����������� ���������� �������� �������</summary>
/// <param name="arr">- ����������� ������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_bubble_trail_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.SortFuncPresentation = "������� �� ���������\t"; // ��������� ���� �����������
	_observer.O = pow(_ArraySize, 2);
	if (_DoExplicit) PrintArray(_observer.SortFuncPresentation, arr, count); // ������� �������� ������

	int startIndex = 0,
		endIndex = count - 1,
		pos, trail, comparison, i, wrongPositions;

	while (1) {
		_observer.sorting_OuterCycleCounter++;

		_observer.assignCounter += 3;
		wrongPositions = 0;
		pos = startIndex;
		trail = 0;
		while (1) { // ����������� for(pos=startIndex; pos<endIndex; pos++)
			_observer.sorting_InnerCycleConter++;

			_observer.compareCounter++;
			comparison = predicate(arr + pos, arr + pos + 1);

			_observer.ifCounter++;
			if (comparison > 0) {
				_observer.assignCounter += 3;
				wrongPositions++;
				i = 0;
				while (1) { // ����������� for(i=0; i<=trail; i++)
					_observer.swapCounter++;
					SwapIntegers_binary(arr + pos - i, arr + pos - i + 1); // ��. "lesson1.c"

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

		if (_DoExplicit) {
			CurrentReport(arr, count);
			if (wrongPositions == 0) printf("  ������������ �� ����������� - ������� ������ �������������\n");
		}

		_observer.ifCounter += 2;
		if (startIndex >= endIndex) break;
		if (wrongPositions == 0) break;
	}

	if (!_DoExplicit) printf("3. ");
}

/// <summary>���������� ��������� �� "���������" (��������� �������)</summary>
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


/// <summary>���������� ������������� �� "���������": ������� ������ �������, ����������� ���������� �������� �������</summary>
/// <param name="arr">- ����������� ������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_shaker_trail_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.SortFuncPresentation = "������������ �� ���������"; // ��������� ���� �����������
	_observer.O = pow(_ArraySize, 2);
	if (_DoExplicit) PrintArray(_observer.SortFuncPresentation, arr, count); // ������� �������� ������

	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex, trail, comparison, i, wrongPositions;

	while (1) {
		_observer.sorting_OuterCycleCounter++;

		_observer.assignCounter += 2;
		trail = 0;
		wrongPositions = 0;

		// ������ ������
		_observer.ifCounter++;
		if (pos == leftIndex) {
			while (1) {
				_observer.sorting_InnerCycleConter++;

				_observer.compareCounter++;
				comparison = predicate(arr + pos, arr + pos + 1);

				_observer.ifCounter++;
				if (comparison > 0) {  // ����������� switch
					_observer.assignCounter += 3;
					wrongPositions++;
					i = 0;
					while (1) { // ����������� for(i=0; i<=trail; i++)
						_observer.swapCounter++;
						SwapIntegers_binary(arr + pos - i, arr + pos - i + 1); // ��. "lesson1.c"

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
		// ������ �����
		else {
			_observer.ifCounter++;
			if (pos == rightIndex) {
				while (1) {
					_observer.sorting_InnerCycleConter++;
					_observer.compareCounter++;
					comparison = predicate(arr + pos - 1, arr + pos);

					_observer.ifCounter++;
					if (comparison > 0) {  // ����������� switch
						_observer.assignCounter += 3;
						wrongPositions++;
						i = 0;
						while (1) { // ����������� for(i=0; i<=trail; i++)
							_observer.swapCounter++;
							SwapIntegers_binary(arr + pos + i - 1, arr + pos + i); // ��. "lesson1.c"

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

		if (_DoExplicit) {
			CurrentReport(arr, count);
			if (wrongPositions == 0) printf("  ������������ �� ����������� - ������� ������ �������������\n");
		}

		_observer.ifCounter += 2;
		if (leftIndex >= rightIndex) break;
		if (wrongPositions == 0) break;
	}

	if(!_DoExplicit) printf("4. ");
}

/// <summary>���������� "�������������" �� "���������" (��������� �������)</summary>
void sort_shaker_trail(void* arr, int count, size_t elSize, int (*predicate)(const void*, const void*)) {
	int leftIndex = 0,
		rightIndex = count - 1,
		pos = leftIndex, trail, i, wrongPositions = -1;

	while (leftIndex < rightIndex && wrongPositions != 0) {
		trail = 0;
		wrongPositions = 0;

		// ������ ������
		if (pos == leftIndex) {
			for (; pos < rightIndex; pos++) {
				switch (predicate((char*)arr + pos * elSize, (char*)arr + (pos + 1) * elSize)) {
				case 1:
					wrongPositions++;
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

		// ������ �����
		else if (pos == rightIndex) {
			for (; pos > leftIndex; pos--) {
				switch (predicate((char*)arr + (pos - 1) * elSize, (char*)arr + pos * elSize)) {
				case 1:
					wrongPositions++;
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


/// <summary>���������� ���������</summary>
/// <param name="arr">- ����������� ������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_selection_observed(int* arr, int count, int (*predicate)(int, int)) {
	_observer.SortFuncPresentation = "������� \t\t"; // ��������� ���� �����������
	_observer.O = pow(_ArraySize, 2);
	if (_DoExplicit) PrintArray(_observer.SortFuncPresentation, arr, count); // ������� �������� ������

	int startIndex = 0,
		endIndex = count - 1,
		pos, tempIndex;

	while (1) { // ����������� for(startIndex=0; startIndex!=endIndex; startIndex++)
		_observer.sorting_OuterCycleCounter++;

		_observer.assignCounter += 2;
		tempIndex = startIndex;
		pos = tempIndex + 1;
		while (1) { // ����������� for(tempIndex=pos=startIndex; pos<endIndex; pos++)
			_observer.sorting_InnerCycleConter++;

			_observer.compareCounter++;
			_observer.ifCounter++;
			if (predicate(arr + tempIndex, arr + pos) == 1) {
				_observer.assignCounter++;
				tempIndex = pos;
			}
			_observer.assignCounter++;
			pos++;
			_observer.ifCounter++;
			if (pos > endIndex) break;
		}
		_observer.ifCounter++;
		if (startIndex != tempIndex) {
			_observer.swapCounter++;
			SwapIntegers_binary(arr + startIndex, arr + tempIndex); // ��. "lesson1.c"
		}
		_observer.assignCounter++;
		startIndex++;

		if (_DoExplicit) CurrentReport(arr, count);

		_observer.ifCounter++;
		if (startIndex == endIndex) break;
	}

	if (!_DoExplicit) printf("5. ");
}

/// <summary>���������� ��������� (��������� �������)</summary>
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


/// <summary>�������� �����</summary>
/// <param name="arr">- ������������� ������</param>
/// <returns>������ ������ �� ��������� �������� ��������; -1, ���� ������� �������� �������� �����������</returns>
int search_binary(int* arr, int count, int searchValue) {
	_observer.SearchFuncPresentation = "�������� �����\t"; // ��������� ���� �����������

	int (*compare)(const void*, const void*);
	if (arr[0] > arr[count - 1]) compare = compare_int_desc;
	else compare = compare_int_asc;

	int leftIndex = 0,
		rightIndex = count - 1,
		midIndex;

	while (leftIndex <= rightIndex) {
		_observer.search_CycleCounter++;
		midIndex = (leftIndex + rightIndex) / 2;

		switch (compare(&searchValue, arr + midIndex)) {
		case 0:
			return midIndex;
		case 1:
			leftIndex = midIndex + 1;
			break;
		case -1:
			rightIndex = midIndex - 1;
			break;
		}
	}
	return -1;
}


/// <summary>����������� ������������� ������ arr, �������� count ����� �������� ������� "Binary insertion sort"</summary>
/// <param name="arr">- ������������� ������</param>
/// <param name="length">- ����� �������������� �������</param>
/// <param name="newValues">- ��������������� ������ ����� ��������</param>
/// <param name="count">- ���������� ����� ��������</param>
void merge_BinaryInsertionSort(int** arr, int length, int* newValues, int count) {
	int* resultArr = (int*)realloc(*arr, (length + count) * sizeof(int));
	if (resultArr != NULL) *arr = resultArr;

	int i;
	for (i = 0; i < count; i++) {
		ResetObserveParams();

		resultArr[length + i] = newValues[i];
		if (_DoExplicit) {
			printf("\n");
			PrintArray("   � ����� ���������:\t", resultArr, length + i + 1);
		}
		BinaryInsertionSort(resultArr, length + i + 1);
		if (_DoExplicit) {
			PrintArray("   ����� �������:\t", resultArr, length + i + 1);
		}
		printf("\t\t\t\t������ ������:       %d\n", _observer.search_CycleCounter);
		printf("\t\t\t\t������� �����������: %d\n", _observer.sorting_InnerCycleConter);
		printf("\n");
	}
}

/// <summary>������� ������ ����� �������� ������� � ������������ ������� ��������������� �������</summary>
/// <param name="arr">- ������ � ������������ ��������� ��������������� ���������</param>
void BinaryInsertionSort(int* arr, int length) {
	int i, newIndex = search_insertPosition_binary(arr, length - 1, arr[length - 1]);
	for (i = length - 1; i > newIndex; i--) {
		_observer.sorting_InnerCycleConter++;

		_observer.swapCounter++;
		SwapIntegers_binary(arr + i - 1, arr + i);
	}
}

/// <summary>�������� ������� ���������� ������ ��� ������� ������ ��������</summary>
/// <param name="arr">- ������������� ���������� ��� ���������� ������</param>
/// <param name="value">- �������������� ��� ������� ��������</param>
/// <returns>������ ������ ���������� ������, �.�. ����� ����� �������</returns>
int search_insertPosition_binary(int* arr, int count, const int value) {
	int (*compare)(const void*, const void*);
	int leftIndex = 0,
		rightIndex = count - 1,
		midIndex = 0;

	if (arr[0] > arr[count - 1]) compare = compare_int_desc;
	else compare = compare_int_asc;

	while (leftIndex <= rightIndex) {
		_observer.search_CycleCounter++;

		midIndex = (leftIndex + rightIndex) / 2;
		switch (compare(&value, arr + midIndex)) {
		case 0:
			return midIndex + GoRightTilDifferent(arr + midIndex, count - midIndex);
			// return midIndex + 1;
			// ���� � ������� ������������ ����� ������ �������� ������� ������, ����������� ������ �� ������������
			// ��� ��� ����� �� ����������: � ���� ������� ����������� ��� ������ (�������� ��������), ��� ��� ������� - �������� ��� ��������
		case 1:
			leftIndex = midIndex + 1;
			break;
		case -1:
			rightIndex = midIndex - 1;
			break;
		}
	}
	return rightIndex + 1;
}

/// <summary>���������� �������� �� ���������� ������, ���� �� ������ �������� ��������</summary>
/// <param name="fromPos">- ����� �������� � ������� ���������� ���������</param>
/// <param name="edge">- ����� �� ����� �������</param>
/// <returns>���������� ����� �� ������� ��������� �������� ��� �� ������� �������� �� ������ �������</returns>
int GoRightTilDifferent(int* fromPos, int edge) {
	int i = 0;
	do i++;
	while (fromPos[i - 1] == fromPos[i] && i < edge);
	return i;
}