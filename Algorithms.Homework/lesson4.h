#pragma once

void Task_4_1(void);
int* ClarifyObstacles(int rows, int columns);
void SolvePaths(int* field, int* obstacles, int rows, int columns);
void PrintMap(int* field, int* obstacles, int rows, int columns);

void Task_4_2(void);
char* RandomString(int* out_length);
char* LongestCommonSubsequence(char* string1, int length1, char* string2, int length2, int* solution);
void PrintSolution(char* string1, int length1, char* string2, int length2, int* solution);

void test_PointerAriphmetics(void);