#pragma once

#define bool int
#define true 1
#define false 0

typedef struct coefs {
	double A, B, C;
} Coefs;

typedef struct chessCell {
	unsigned char rank, file;
	bool IsWhite;
} ChessCell;

void Task_1_1(void);

void Task_1_2(void);
void Task_1_2a(void);
void Task_1_2b(void);
double GreatestOfFour_ReverseTree(double a, double b, double c, double d);
double GreatestOfFour_HeadOn(double a, double b, double c, double d);
void ReadGreaterNum(char* message, double* res);

void Task_1_3(void);
void Swap_withTemp(int* x, int* y);
void Swap_sum(int* x, int* y);
void SwapIntegers_binary(int* x, int* y);

void Task_1_4(void);
char* SqEquation_print(Coefs c);
int SqEquation_solve(Coefs c, double* x1, double* x2, double* D);

void Task_1_7(void);
ChessCell NewCell(unsigned int rank, unsigned int file);
ChessCell ReadCell(char* message);
char* CellColor_ToString(ChessCell c);

void Task_1_13(void);
void Task_1_13a(int count);
void Task_1_13b(int count);
int GetSystemRand(int digits);
void BootMyRand(unsigned int starter);
int GetMyRand(void);

void Task_1_14(void);
bool IsAutomorph(int num);