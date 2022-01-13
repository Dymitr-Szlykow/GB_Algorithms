#ifndef LESSON4_H
#define LESSON4_H

// ������� � ������� �4.
// 1. *���������� ��������� � �������������. ����������� ������ ������� � ������������ � ���������� ���������� ���������.
//    ��������, ����� 3�3:
//    1 1 1
//    0 1 0
//    0 1 0
// 2. ������ ������ � ���������� ����� ������������ ������������������ � ������� �������.
// 3. * **��������� ������ ����� ��������� ����� �������� NxM, ������ ����� ��� ���� ����� �� ������ ����.
//    ����� �������� ������� ����� ��, ��� � ������ � 8 ������. ������� ������ � �������� ��������� ����.

void Task_4_1(void);
int* ClarifyObstacles(int rows, int columns); // = O( rows * columns + rows + columns ) = O(rows * columns)  ~ O(n^2)
void SolvePaths(int* field, int* obstacles, int rows, int columns); // = O(rows * columns + columns - rows) = O(rows * columns)  ~ O(n^2)
void PrintMap(int* field, int* obstacles, int rows, int columns); // = O(rows * columns) ~ O(n^2)

void Task_4_2(void);
char* RandomString(int* out_length); // time = const
char* LongestCommonSubsequence(char* string1, int length1, char* string2, int length2, int* solution); // = O(length1 * length2 + length1 + length2) = O(length1 * length2)  ~ O(n^2)
void PrintSolution(char* string1, int length1, char* string2, int length2, int* solution); // = O(length1 * length2)  ~ O(n^2)

void test_PointerAriphmetics(void);

#endif