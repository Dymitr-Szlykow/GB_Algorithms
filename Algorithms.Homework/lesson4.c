#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>


inline void Task_4_1(void);
inline int* ClarifyObstacles(int rows, int columns);
inline void SolvePaths(int* field, int* obstacles, int rows, int columns);
inline void PrintMap(int* field, int* obstacles, int rows, int columns);

inline void Task_4_2(void);
inline char* RandomString(int* out_length);
inline char* LongestCommonSubsequence(char* string1, int length1, char* string2, int length2, int* solution);
inline void PrintSolution(char* string1, int length1, char* string2, int length2, int* solution);

inline void test_PointerAriphmetics(void);

// ЗАДАНИЯ к занятию №4.
// 1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.
//    Например, карта 3х3:
//    1 1 1
//    0 1 0
//    0 1 0
// 2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.
// 3. * **Требуется обойти конем шахматную доску размером NxM, пройдя через все поля доски по одному разу.
//    Здесь алгоритм решения такой же, как в задаче о 8 ферзях. Разница только в проверке положения коня.


/// <summary>
/// 1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количества маршрутов.
/// </summary>
void Task_4_1(void) {
	int rows = 8, columns = 8;

	int* field = (int*)malloc(rows * columns * sizeof(int));
	int* obstacles = ClarifyObstacles(rows, columns);

	SolvePaths(field, obstacles, rows, columns);
	printf("\n");
	PrintMap(field, obstacles, rows, columns);

	free(field);
	free(obstacles);
}

/// <summary>создает карту препятствий</summary>
int* ClarifyObstacles(int rows, int columns) {
	int* res = (int*)malloc(rows * columns * sizeof(int));

	if (res != NULL) {
		srand(time(NULL));

		int i, j, maxObstacles = (rows + columns - 4) / 2;

		for (i = 0; i < rows; i++) {
			*(res + i * columns) = 0; // res[i][0] = 0;
			*(res + (i + 1) * columns - 1) = 0; // res[i][columns - 1] = 0;
		}
		for (j = 1; j < columns - 1; j++) {
			*(res + j) = 0; // res[0][j] = 0;
			*(res + (rows - 1) * columns + j) = 0; // res[rows - 1][j] = 0;
		}

		for (i = 1; i < rows - 1; i++) {
			for (j = 1; j < columns - 1; j++) {
				if (maxObstacles > 0) {
					if (rand() % 3 == 0) {
						*(res + i * columns + j) = 1;// res[i][j] = 1;
						maxObstacles--;
					}
					else *(res + i * columns + j) = 0; // res[i][j] = 0;
				}
				else *(res + i * columns + j) = 0; // res[i][j] = 0;
			}
		}
	}

	return res;
}

void SolvePaths(int* field, int* obstacles, int rows, int columns) {
	int i, j;
	for (j = 0; j < columns; j++) {
		if (*(obstacles + j)) *(field + j) = 0; // if (obstacles[0][j]) field[0][j] = 0;
		else *(field + j) = 1; // else field[0][j] = 1;
	}
	for (i = 1; i < rows; i++) {
		if (*(obstacles + i * columns)) *(field + i * columns) = 0; // if (obstacles[i][0]) field[i][0] = 0;
		else *(field + i * columns) = *(field + (i - 1) * columns); // else field[i][0] = field[i - 1][0];

		for (j = 1; j < columns; j++) {
			if (*(obstacles + i * columns + j)) *(field + i* columns + j) = 0; // if (obstacles[i][j]) field[i][j] = 0;
			else *(field + i * columns + j) = *(field + (i - 1) * columns + j) + *(field + i * columns + j - 1); // else field[i][j] = field[i - 1][j] + field[i][j - 1];
		}
	}
}

void PrintMap(int* field, int* obstacles, int rows, int columns) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			if (*(obstacles + i * columns + j)) printf("  XX "); // if (obstacles[i][j])
			else printf(" %3d ", *(field + i * columns + j)); // field[i][j]
		}
		printf("\n");
	}
}

/// <summary>
/// 2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.
/// </summary>
void Task_4_2(void) {
	srand(time(NULL));
	int length1, length2;
	char* str1 = RandomString(&length1);
	char* str2 = RandomString(&length2);
	int* solution = (int*)malloc((length1 + 1) * (length2 + 1) * sizeof(int));

	printf("строка 1: \"%s\", длина %d\n", str1, length1);
	printf("строка 2: \"%s\", длина %d\n\n", str2, length2);

	char* ex = LongestCommonSubsequence(str1, length1, str2, length2, solution);
	PrintSolution(str1, length1, str2, length2, solution);
	printf("Пример наибольшей общей последовательности: \"%s\"\n", ex);

	free(str1);
	free(str2);
	free(solution);
	free(ex);
}

/// <summary>создает случайную строку 15-40 символов + '\0'</summary>
/// <param name="out_length">выводит длину строки</param>
/// <returns>указатель на строку в динамической памяти</returns>
char* RandomString(int* out_length) {
	*out_length = (rand() % 26) + 15;
	char* res = (char*)malloc((*out_length + 1) * sizeof(char));

	int i;
	for (i = 0; i < *out_length; i++) {
		res[i] = (rand() % 11)
			? ((rand() % ('z' - 'a')) + 'a') // (rand() % 26) + 97
			: ' ';
	}
	res[(*out_length)++] = '\0';

	return res;
}

char* LongestCommonSubsequence(char* string1, int length1, char* string2, int length2, int* solution) {
	int i, j, pos;
	char* path = (char*)malloc(length1 * length2 * sizeof(char));
	for (i = 0; i < length1; i++) *(solution + i * length2) = 0;
	for (j = 1; j < length2; j++) *(solution + j) = 0;

	for (i = 1; i < length1; i++) {
		for (j = 1; j < length2; j++) {

			if (*(string1 + i - 1) == *(string2 + j - 1)) {
				*(solution + i * length2 + j) = *(solution + (i - 1) * length2 + j - 1) + 1;
				*(path + i * length2 + j) = 'c';
			}
			else if (*(solution + (i - 1) * length2 + j) >= *(solution + i * length2 + j - 1)) {
				*(solution + i * length2 + j) = *(solution + (i - 1) * length2 + j);
				*(path + i * length2 + j) = 'u';
			}
			else {
				*(solution + i * length2 + j) = *(solution + i * length2 + j - 1);
				*(path + i * length2 + j) = 'l';
			}
		}
	}

	//int k, l;
	//printf("\n");
	//for (k = 0; k < length1; k++) {
	//	for (l = 0; l < length2; l++) {
	//		printf("%2c  ", *(path + k * length2 + l));
	//	}
	//	printf("\n");
	//}
	//printf("\n");

	pos = *(solution + --i * length2 + --j);
	char* res = (char*)malloc((pos + 1) * sizeof(char));
	*(res + pos) = '\0';
	pos--;

	while (pos >= 0) {
		switch (*(path + i * length2 + j)) {
		case 'c':
			*(res + pos) = *(string1 + i - 1);
			pos--;
			i--;
			j--;
			break;
		case 'l': j--; break;
		case 'u': i--; break;
		}
	}

	free(path);
	return res;
}

void PrintSolution(char* string1, int length1, char* string2, int length2, int* solution) {
	int i, j;
	printf("\t");
	for (j = 0; j < length2; j++) printf("%3c ", *(string2 + j) == ' ' ? '_' : *(string2 + j));
	printf("\n\n");

	for (i = 1; i < length1; i++) {
		printf("    %c\t", *(string1 + i - 1) == ' ' ? '_' : *(string1 + i - 1));
		for (j = 1; j < length2; j++) {
			printf("%3d ", *(solution + i * length2 + j));
		}
		printf("\n");
	}
	printf("\n");
}


/// <summary>
/// тест: арифметика указателей
/// </summary>
void test_PointerAriphmetics() {
	int locArr[5][3], i, j, next = 9, rows = 5, cols = 3;
	int(*rowPointerLoc)[3] = locArr;
	int* dynArr = (int*)malloc(rows * cols * sizeof(int));
	int(*rowPointerDyn)[3] = dynArr;

	printf("Sizeof(int):              %d\n", sizeof(int));				// 4
	printf("Sizeof(int*):             %d\n", sizeof(int*));				// 4
	printf("Sizeof(void*):            %d\n", sizeof(void*));			// 4
	printf("Sizeof(int[3]):           %d\n", sizeof(int[3]));			// 12
	printf("Sizeof(locArr):           %d\n", sizeof(locArr));			// 60 - массив int[5][3]
	printf("Sizeof(locArr[0]):        %d\n", sizeof(locArr[0]));		// 12 - массив int[3]
	printf("Sizeof(dynArr):           %d\n", sizeof(dynArr));			// 4  - сам указатель
	printf("Sizeof(dynArr[0]):        %d\n", sizeof(dynArr[0]));		// 4  - int
	printf("Sizeof(rowPointerLoc):    %d\n", sizeof(rowPointerLoc));	// 4  - сам указатель
	printf("Sizeof(*rowPointerLoc):   %d\n", sizeof(*rowPointerLoc));	// 12 - массив int[3]
	printf("Sizeof(rowPointerDyn):    %d\n", sizeof(rowPointerDyn));	// 4  - сам указатель
	printf("Sizeof(*rowPointerDyn):   %d\n", sizeof(*rowPointerDyn));	// 12 - массив int[3]
	printf("\n");

	if (dynArr != NULL) {

		printf("Значения\t\tАдреса\n");
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 3; j++) {
				locArr[i][j] = next++;
				printf(" %4d", locArr[i][j]);
			}
			printf("\t\t");
			for (j = 0; j < 3; j++) {
				printf(" %4d", &locArr[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				*(dynArr + i * cols + j) = locArr[i][j];
				printf(" %4d", *(dynArr + i * cols + j));
			}
			printf("\t\t");
			for (j = 0; j < cols; j++) {
				printf(" %4d", dynArr + i * cols + j);
			}
			printf("\n");
		}
		printf("\n");

		printf("\t\t\tадрес\t\tзначение\n\n");
		printf("locArr:             \t%d  \t%d\n", locArr, **locArr);
		printf("locArr + 1:         \t%d  \t%d\n", locArr + 1, **(locArr + 1));
		printf("*locArr + 1:        \t%d  \t%d\n", *locArr + 1, *(*locArr + 1));
		printf("*(locArr + 1):      \t%d  \t%d\n", *(locArr + 1), *(*(locArr + 1)));
		printf("*(locArr + 1) + 1:  \t%d  \t%d\n", *(locArr + 1) + 1, *(*(locArr + 1) + 1));
		printf("locArr[0]:          \t%d  \t%d\n", locArr[0], *locArr[0]);
		printf("locArr[1]:          \t%d  \t%d\n", locArr[1], *locArr[1]);
		printf("locArr[0] + 1:      \t%d  \t%d\n", locArr[0] + 1, *(locArr[0] + 1));
		printf("locArr[1] + 1:      \t%d  \t%d\n", locArr[1] + 1, *(locArr[1] + 1));
		printf("*locArr[0] + 1:     \t--\t\t%d\n", *locArr[0] + 1);
		printf("*locArr[1] + 1:     \t--\t\t%d\n", *locArr[1] + 1);
		printf("rowPointerLoc:      \t%d  \t%d\n", rowPointerLoc, **rowPointerLoc);
		printf("rowPointerLoc + 1:  \t%d  \t%d\n", rowPointerLoc + 1, **(rowPointerLoc + 1));
		printf("*rowPointerLoc + 1: \t%d  \t%d\n", *rowPointerLoc + 1, *(*rowPointerLoc + 1));
		printf("rowPointerLoc + 2:  \t%d  \t%d\n", rowPointerLoc + 2, **(rowPointerLoc + 2));
		printf("*(rowPointerLoc +1) +1:\t%d  \t%d\n", *(rowPointerLoc + 1) + 1, *(*(rowPointerLoc + 1) + 1));
		printf("\n");
		printf("dynArr:             \t%d  \t%d\n", dynArr, *dynArr);
		printf("dynArr + 1:         \t%d  \t%d\n", dynArr + 1, *(dynArr + 1));
		printf("dynArr + cols:      \t%d  \t%d\n", dynArr + cols, *(dynArr + cols));
		printf("dynArr + cols + 1:  \t%d  \t%d\n", dynArr + cols + 1, *(dynArr + cols + 1));
		printf("dynArr + 2 * cols:  \t%d  \t%d\n", dynArr + 2 * cols, *(dynArr + 2 * cols));
		printf("dynArr + 2 * cols + 1:\t%d  \t%d\n", dynArr + 2 * cols + 1, *(dynArr + 2 * cols + 1));
		printf("rowPointerDyn:      \t%d  \t%d\n", rowPointerDyn, **rowPointerDyn);
		printf("rowPointerDyn + 1:  \t%d  \t%d\n", rowPointerDyn + 1, **(rowPointerDyn + 1));
		printf("rowPointerDyn + 2:  \t%d  \t%d\n", rowPointerDyn + 2, **(rowPointerDyn + 2));
		printf("\n");

		int temp;
		for (i = 0, j = rows * cols; i < j; i++) {
			printf(" %4d", *(dynArr + i));
			if ((i + 1) % cols == 0) printf("\n");
		}

		free(dynArr);
	}
	else printf("FatAl erRoR! DoWNloAd mOre RAM.\n");
}