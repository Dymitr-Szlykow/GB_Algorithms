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


// �������.
// 1.  ����������� �������������� ����������� ����������.
//     �������� ���������� �������� ��������� ���������������� � �� ���������������� ���������.
//     �������� ������� ����������, ������� ���������� ���������� ��������.
// 2*. ����������� ��������� ����������.
// 3.  ����������� �������� �������� ������ � ���� �������, ������� ���������� ��������������� ������.
//     ������� ���������� ������ ���������� �������� ��� -1, ���� ������� �� ������.
// 4*. ���������� ���������� �������� ��� ������ �� ���������� � �������� ��� � ��������������� ���������� ���������.


/// <summary>lesson 3 submain function</summary>
void RunLesson3() {
	_SourceArray = InitNewArray(_ArraySize);
	PrintArray("�������� ������ \t", _SourceArray, _ArraySize);

	ObserveParams
		observer1 = RunSorting(sort_bubble_simple),
		observer2 = RunSorting(sort_shaker_simple);
	//	observer3 = RunSorting(Task_3_3);

	ReportObserveParams(&observer1);
	ReportObserveParams(&observer2);
	//ReportObserveParams(&observer3);

	free(_SourceArray);
}

/// <summary>�������� ��������� ����������� "�����������"</summary>
void ResetObserveParams() {
	_observer.compareCounter = 0;
	_observer.compareLast = 0;
	_observer.swapCounter = 0;
	_observer.swapLast = 0;
	_observer.outerCycleCounter = 0;
	_observer.innerCycleConter = 0;
}

/// <summary>"�������"</summary>
void NotchObserveParams() {
	_observer.compareLast = _observer.compareCounter;
	_observer.swapLast = _observer.swapCounter;
}

/// <summary>������� ����� �� ���������� ����������</summary>
/// <param name="obs">- ����� ���������� ����������</param>
void ReportObserveParams(ObserveParams* obs) {
	printf("\n%s.\n", obs->FuncPresentation);
	printf("    ��������� �����������: %d\n", obs->compareCounter);
	printf("    ������� �����������:   %d\n", obs->swapCounter);
}

/// <summary>�������� ���������� ������ � ���������� ����������</summary>
/// <param name="task">- ������� ����������</param>
/// <param name="presentation">- ��������� ��� ������������� ������� ��� ������</param>
/// <returns>��������� ���������� ��� ������ ����������</returns>
ObserveParams RunSorting(int (*sorting)(int*,int,int(*)(int,int))) {
	ResetObserveParams();
	int* runningArr = GetArrayCopy(_SourceArray, _ArraySize);

	sorting(runningArr, _ArraySize, compare_asc);

	free(runningArr);
	return _observer;
}

/// <summary>������� ������ � ������������ ������ � �������������� ���������� ����������</summary>
/// <param name="count">- ����� �������</param>
/// <returns>��������� �� ������ � ����</returns>
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
/// <param name="arr">- ������ ����� �����</param>
/// <param name="count">- ����� �������</param>
void PrintArray(char* presentation, int* arr, int count) {
	printf("%s\t", presentation);
	int i;
	for (i = 0; i < count && i < 40; i++) {
		printf("%3d ", *(arr + i));
	}
	if (i == 30) printf("...\n");
	else printf("\n");
}


/// <summary>������� ����� �� ����� ����������</summary>
void CurrentReport(int* arr, int count) {
	printf("  ��� %2d-%2d,", _observer.outerCycleCounter, _observer.innerCycleConter);
	printf(" ����� %2d,", _observer.compareCounter - _observer.compareLast);
	printf(" ��� %2d", _observer.swapCounter - _observer.swapLast);
	PrintArray("", arr, count);
}


/// <summary>�������� ����������</summary>
/// <returns>&gt;0 - ����� ������ - ������;&#10;0 - �����;&#10;&lt;0 - ������ ������ - ����������</returns>
int compare_asc(int left, int right) {
	return left - right;
}

/// <summary>�������� ����������</summary>
/// <returns>&gt;0 - ������ ������ - ������;&#10;0 - �����;&#10;&lt;0 - ����� ������ - ����������</returns>
int compare_desc(int left, int right) {
	return right - left;
}

/// <summary>������� ���������� ���������</summary>
/// <param name="arr">- ������ ��� ����������</param>
/// <param name="count">- ������ �������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_bubble_simple(int* arr, int count, int (*predicate)(int,int)) {
	_observer.FuncPresentation = "������� ������� \t"; // ��������� ���� �����������
	if (_DoExplicit) {
		printf("\n");
		PrintArray(_observer.FuncPresentation, arr, count); // ������� �������� ������
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
				SwapIntegers_binary(arr + pos, arr + pos + 1); // ��. "lesson1.c"
			}
		}
		endIndex--;

		if (_DoExplicit) CurrentReport(arr, count);
		NotchObserveParams();
	}

	if (_DoExplicit) printf("  �����      ����� %2d, ��� %2d\n", _observer.compareCounter, _observer.swapCounter);
}

/// <summary>���������� ���� shaker</summary>
/// <param name="arr">- ������ ��� ����������</param>
/// <param name="count">- ������ �������</param>
/// <param name="predicate">- ������������ ��� ���������� ������� ���������</param>
void sort_shaker_simple(int* arr, int count, int (*predicate)(int, int)) {
	_observer.FuncPresentation = "shaker\t\t\t"; // ��������� ���� �����������
	if (_DoExplicit) {
		printf("\n");
		PrintArray(_observer.FuncPresentation, arr, count); // ������� �������� ������
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
					SwapIntegers_binary(arr + pos, arr + pos + 1); // ��. "lesson1.c"
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
					SwapIntegers_binary(arr + pos - 1, arr + pos); // ��. "lesson1.c"
				}
				if (pos == leftIndex + 1) break;
				else pos--;
			}
			leftIndex++;
		}

		if (_DoExplicit) CurrentReport(arr, count);
		NotchObserveParams();
	}

	if (_DoExplicit) printf("  �����      ����� %2d, ��� %2d\n", _observer.compareCounter, _observer.swapCounter);
}

// 1. ����������� �������������� ����������� ����������.
// �������� ���������� �������� ��������� ���������������� � �� ���������������� ���������.
// �������� ������� ����������, ������� ���������� ���������� ��������.
// 
// 2. *����������� ��������� ����������.
// 
// 3. ����������� �������� �������� ������ � ���� �������, ������� ���������� ��������������� ������.
// ������� ���������� ������ ���������� �������� ��� -1, ���� ������� �� ������.