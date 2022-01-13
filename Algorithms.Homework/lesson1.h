#ifndef LESSON1_H
#define LESSON1_H

#define bool int
#define true 1
#define false 0

// ������� � ������� �1.
// 1. ������ ��� � ���� ��������. ���������� � ������� ������ ����� ���� �� ������� I = m / (h * h); ��� m - ����� ���� � �����������, h - ���� � ������.
// 2. ����� ������������ �� ������� �����.������� �� ������������.
// 3. �������� ��������� ������ ���������� ���� ������������� ���������� :
//    a. � �������������� ������� ����������;
//    b.* ��� ������������� ������� ����������.
// 4. �������� ��������� ���������� ������ ��������� ����������� ���������.
// 5. � ���������� �������� ����� ������.��������� ����������, � ������ ������� ���� �� ���������.
// 6. ������ ������� ��������(�� 1 �� 150 ���) � ������� ��� ������ � ����������� ������ ����, ����� ��� ����.
// 7. � ���������� �������� �������� ���������� ���� ����� ��������� �����(x1, y1, x2, y2).��������� ����������, ��������� ���� � ������ ����� ��� ���.
// 8. ������ a � b � ������� �������� � ���� ����� �� a �� b.
// 9. ���� ����� ������������� ����� N � K.��������� ������ �������� �������� � ���������, ����� ������� �� ������� ������ N �� K, � ����� ������� �� ����� �������.
// 10. ���� ����� ����� N(> 0).� ������� �������� ������� ������ � ������ ������� �� ������� ����������, ������� �� � ������ ����� N �������� �����. ���� �������, �� ������� True, ���� ��� � ������� False.
// 11. � ���������� �������� �����, ���� �� ����� ������ 0. ���������� ������� �������������� ���� ������������� ������ �����, �������������� �� 8.
// 12. �������� ������� ���������� ������������� �� ���� �����.
// 13. * �������� �������, ������������ ��������� ����� �� 1 �� 100.
//     �) � �������������� ����������� ������� rand()
//     �) ��� ������������� ����������� ������� rand()
// 14. * ����������� �����.����������� ����� ���������� �����������, ���� ��� ����� ��������� ������ ������ ��������.��������, 252 = 625.
//     �������� ���������, ������� ������ ����������� ����� N � ������� �� ����� ��� ����������� �����, �� ������������� N.
// ���������� ������ 3 ������. ����������� � ������ ��������� ������� � ���� �������. ��� ������� ���������� � ����� ���������. ������ �� ����������� ���������� � ��� ������, ���� ������ �������. �������� ��������� ����.

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
double GreatestOfFour_ReverseTree(double a, double b, double c, double d); // = O(1)
double GreatestOfFour_HeadOn(double a, double b, double c, double d); // = O(1)
void ReadGreaterNum(char* message, double* res); // = O(scanf(message.length)) = O(message.length)  ~ O(n)

void Task_1_3(void);
inline void Swap_withTemp(int* x, int* y); // = O(1)
inline void Swap_sum(int* x, int* y); // = O(1)
inline void SwapIntegers_binary(int* x, int* y); // = O(1)

void Task_1_4(void);
void SqEquation_print(Coefs c); // = O(1)
int SqEquation_solve(Coefs c, double* out_x1, double* out_x2, double* out_D); // = O(sqrt())

void Task_1_7(void);
ChessCell NewCell(unsigned int rank, unsigned int file); // = O(1)
ChessCell ReadCell(char* message); // = O(1), �� �������������, �.�. ���� ����������� ��� ������������ �����
inline char* CellColor_ToString(ChessCell c); // = O(1)

void Task_1_13(void);
void Task_1_13a(int count); // = O(count)
void Task_1_13b(int count); // = O(count)
int GetSystemRand(int digits); // = O(digits)
void BootMyRand(unsigned int starter); // = O(1)
int GetMyRand(void);

void Task_1_14(void);
bool IsAutomorph(int num); // = O(lg num) = O(log num)

#endif