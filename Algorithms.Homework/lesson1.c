#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#pragma warning(disable : 4996)

#define bool int
#define true 1
#define false 0


inline void Task_1_1(void);

inline void Task_1_2(void);
inline void Task_1_2a(void);
inline void Task_1_2b(void);
inline double GreatestOfFour_ReverseTree(double a, double b, double c, double d);
inline double GreatestOfFour_HeadOn(double a, double b, double c, double d);
inline void ReadGreaterNum(char* message, double* res);

inline void Task_1_3(void);
inline void Swap_withTemp(int* x, int* y);
inline void Swap_sum(int* x, int* y);
inline void SwapIntegers_binary(int* x, int* y);

inline void Task_1_4(void);
typedef struct coefs Coefs;
inline char* SqEquation_print(Coefs c);
inline int SqEquation_solve(Coefs c, double* x1, double* x2, double* D);

inline void Task_1_7(void);
typedef struct chessCell ChessCell;
inline ChessCell NewCell(unsigned int rank, unsigned int file);
inline ChessCell ReadCell(char* message);
inline char* CellColor_ToString(ChessCell c);

inline void Task_1_13(void);
inline void Task_1_13a(int count);
inline void Task_1_13b(int count);
inline int GetSystemRand(int digits);
inline void BootMyRand(unsigned int starter);
inline int GetMyRand(void);

inline void Task_1_14(void);
inline bool IsAutomorph(int num);


struct coefs {
	double A, B, C;
};

struct chessCell {
	unsigned char rank, file;
	bool IsWhite;
};

// 1. ������ ��� � ���� ��������.���������� � ������� ������ ����� ���� �� ������� I = m / (h * h); ��� m - ����� ���� � �����������, h - ���� � ������.
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
// ���������� ������ 3 ������.����������� � ������ ��������� ������� � ���� �������.��� ������� ���������� � ����� ���������.������ �� ����������� ���������� � ��� ������, ���� ������ �������.�������� ��������� ����. 123


/// <summary>
/// 1. ������ ��� � ���� ��������. ���������� � ������� ������ ����� ���� �� ������� I=m/(h*h); ��� m-����� ���� � �����������, h - ���� � ������.
/// </summary>
void Task_1_1() {
	double bodyHeight, bodyWeight, temp;

	printf("������� ����� ����: ");
	scanf("%lf", &bodyWeight);

	printf("������� ����: ");
	scanf("%lf", &bodyHeight);
	if (bodyHeight > 50) bodyHeight /= 100;

	temp = pow(bodyHeight, 2);
	double bmIndex = bodyWeight / temp;
	double reqWeightMin = 18.5 * temp;
	double reqWeightMax = 25 * temp;

	printf("��� ����� %.2lf �� � ����� %.2lf �, ������ ����� ���� - %.2lf,", bodyWeight, bodyHeight, bmIndex);

	if (bmIndex <= 18.5) {
		if (bmIndex <= 16)
			printf(" ���������� ������� ����� ����.");
		else
			printf(" ��������� �� ������������� (�������) ����� ����.");
		printf("\n��� ��� ����������� ����� ���� �� %.2lf �� %.2lf ��. ��� ������� ����������� �� %.2lf ��.\n", reqWeightMin, reqWeightMax, reqWeightMin - bodyWeight);
	}
	else if (bmIndex <= 25)
		printf(" � �����.\n");
	else {
		if (bmIndex <= 30)
			printf(" ��������� �� ���������� ����� ���� (������������).");
		else if (bmIndex <= 35)
			printf(" �������� 1 �������.");
		else if (bmIndex <= 40)
			printf(" �������� 2 �������.");
		else
			printf(" �������� 3 �������.");
		printf("\n��� ��� ����������� ����� ���� �� %.2lf �� %.2lf ��. ��� ������� �������� �� %.2lf ��.\n", reqWeightMin, reqWeightMax, bodyWeight - reqWeightMax);
	}
}


/// <summary>
/// 2. ����� ������������ �� ������� �����. ������� �� ������������.
/// </summary>
void Task_1_2() {
	Task_1_2a();
	getch();
	printf("\n");
	Task_1_2b();
}

void Task_1_2a() {
	double a, b, c, d;
	printf("������� ������ �����: ");
	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
	printf("���������� �� ���: %.2lf\n", GreatestOfFour_ReverseTree(a, b, c, d));
	printf("������ ��������: %.2lf\n", GreatestOfFour_HeadOn(a, b, c, d));
}

void Task_1_2b() {
	double res;

	printf("������� ������ �����: ");
	scanf("%lf", &res);
	
	ReadGreaterNum("������� ������ �����: ", &res);
	ReadGreaterNum("������� ������ �����: ", &res);
	ReadGreaterNum("������� ��������� �����: ", &res);
	printf("���������� �� ���: %.2lf\n", res);
}

double GreatestOfFour_ReverseTree(double a, double b, double c, double d) {
	if (a > b) b = a;
	if (c > d) d = c;
	if (b > d) return b;
	else return d;
}

double GreatestOfFour_HeadOn(double a, double b, double c, double d) {
	return
		a > b
		? (a > c
			? (a > d ? a : d)
			: (c > d ? c : d))
		: (b > c
			? (b > d ? b : d)
			: (c > d ? c : d));
}

void ReadGreaterNum(char* message, double* res) {
	double a;
	printf("%s", message);
	scanf("%lf", &a);
	if (a > *res) *res = a;
}


/// <summary>
/// 3. �������� ��������� ������ ���������� ���� ������������� ����������:
/// a) � �������������� ������� ����������;
/// b) *��� ������������� ������� ����������.
/// </summary>
void Task_1_3() {
	int a, b;
	printf("������� ��� ����� �����: ");
	scanf("%d %d", &a, &b);

	Swap_withTemp(&a, &b);
	printf("���� ������:\t%d  %d\n", a, b);

	Swap_sum(&a, &b);
	printf("�������:\t%d  %d\n", a, b);

	SwapIntegers_binary(&a, &b);
	printf("� �����:\t%d  %d\n", a, b);
}

void Swap_withTemp(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Swap_sum(int* x, int* y) {
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void SwapIntegers_binary(int* x, int* y) {
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}


/// <summary>
/// 4. �������� ��������� ���������� ������ ��������� ����������� ���������.
/// </summary>
void Task_1_4() {
	double x1, x2, D;
	Coefs c;
	int hasRoots;

	printf("���������� ��������� ������ ����:  A * x^2 + B * x + C = 0.\n");
	printf("������� ������������:\n  A = ");
	scanf("%lf", &c.A);
	if (c.A == 0) {
		printf("��� ������������ A = 0 ��������� �������� ��������. ������� �����������.");
		return;
	}

	printf("  B = ");
	scanf("%lf", &c.B);

	printf("  C = ");
	scanf("%lf", &c.C);

	printf("%s", SqEquation_print(c));
	hasRoots = SqEquation_solve(c, &x1, &x2, &D);

	printf("������������ ����� %.3lf. ", D);
	if (hasRoots == 1) {
		if (c.B == 0)
			printf("��������� ����� ��� �����: +/- %lf.\n", fabs(x1)); //�
		else
			printf("��������� ����� ��� �����: %lf � %lf.\n", x1, x2);
	}
	else if (hasRoots == 0)
		printf("��������� ����� ���� ������: %lf.\n", x1);
	else
		printf("��������� �� ����� ������.\n");
}

char* SqEquation_print(Coefs c) {
	char res[64] = "", temp[16];

	sprintf(res, "%.2lf*x^2", c.A);

	if (c.B != 0) {
		strcat(res, c.B < 0 ? " - " : " + ");
		if (c.B == 1 || c.B == -1)
			sprintf(temp, "x");
		else
			sprintf(temp, "%.2lfx", fabs(c.B));
		strcat(res, temp);
	}

	if (c.C != 0) {
		sprintf(temp, "%s%.2lf", c.C < 0 ? " - " : " + ", fabs(c.C));
		strcat(res, temp);
	}
	strcat(res, " = 0\n");
	return res;
}

int SqEquation_solve(Coefs c, double* x1, double* x2, double* D)
{
	*D = c.B * c.B - 4 * c.A * c.C;

	if (D < 0) {
		return -1;
	}
	else if (D > 0) {
		*x1 = (-c.B - sqrt(*D)) / 2 / c.A;
		*x2 = (-c.B + sqrt(*D)) / 2 / c.A;
		return 1;
	}
	else {
		*x1 = -c.B / 2 / c.A;
		*x2 = *x1;
		return 0;
	}
}


/// <summary>
/// 7. � ���������� �������� �������� ���������� ���� ����� ��������� ����� (x1,y1,x2,y2).
/// ��������� ����������, ��������� ���� � ������ ����� ��� ���.
/// </summary>
void Task_1_7() {
	ChessCell c1 = ReadCell("������ ������");
	ChessCell c2 = ReadCell("������ ������");

	if (c1.IsWhite == c2.IsWhite) {
		printf("��� ������ %s.", CellColor_ToString(c1));
	}
	else {
		printf("������ ������ ������ ������. ������ - %s, ������ - %s.", CellColor_ToString(c1), CellColor_ToString(c2));
	}
}

ChessCell NewCell(unsigned int rank, unsigned int file) {
	ChessCell res;
	res.rank = (unsigned char)rank;
	res.file = (unsigned char)file;
	if ((rank % 2) + (file % 2) == 1) res.IsWhite = true;
	else res.IsWhite = false;
	return res;
}

char* CellColor_ToString(ChessCell c) {
	return c.IsWhite ? "������ �����" : "������� �����";
}

ChessCell ReadCell(char* message) {
	unsigned int rankInput, fileInput;
	unsigned char temp;
	bool ok = false;

	do {
		printf("������� ������ (a-h) � ��� (1-8) %s ����� ������: ", message);
		if (scanf("%c%lu", &temp, &rankInput) == 2) {
			if ('a' <= temp && temp <= 'h' && 1 <= rankInput && rankInput <= 8) {
				ok = true;
				fileInput = (unsigned int)temp - 96;
			}
			else {
				printf("������������ ��������\n");
			}
		}
		else {
			printf("������ ������\n");
		}
	} while (!ok);
	return NewCell(rankInput, fileInput);
}


/// <summary>
/// 13. �������� �������, ������������ ��������� ����� �� 1 �� 100.
/// �) � �������������� ����������� ������� rand()
/// �) ��� ������������� ����������� ������� rand()
/// </summary>
void Task_1_13() {
	Task_1_13a(25);
	Task_1_13b(25);
}

void Task_1_13a(int count) {
	if (count == 0) return;
	int i;
	srand(time(NULL));
	for (i = 0; i < count; i++) {
		printf("%3d ", GetSystemRand(2) + 1);
	}
	printf("\n");
}

void Task_1_13b(int count) {
	if (count == 0) return;
	int i;
	BootMyRand(7);
	for (i = 0; i < count; i++) {
		printf("%3d ", (GetMyRand() % 100) + 1);
	}
	printf("\n");
}

int GetSystemRand(int digits) {
	int i, base = 1;
	for (int i = 1; i <= digits; i++) {
		base *= 10;
	}
	return (rand() % base);
}

unsigned long int Xn, A, C, Mod;
void BootMyRand(unsigned int starter) {
	Xn = starter;
	A = 1103515245;
	C = 12345;
	Mod = 32768;
}
int GetMyRand() {
	if (Xn == NULL || A == NULL || C == NULL || Mod == NULL) BootMyRand(33);
	Xn = (A * Xn + C) % Mod;
	return (unsigned int)Xn;
}


/// <summary>
/// 14. ����������� �����. ����������� ����� ���������� �����������, ���� ��� ����� ��������� ������ ������ ��������. ��������, 252 = 625.
/// �������� ���������, ������� ������ ����������� ����� N � ������� �� ����� ��� ����������� �����, �� ������������� N.
/// </summary>
void Task_1_14() {
	unsigned int upto, num;
	printf("������� ����������� �����: ");
	scanf("%lu", &upto);

	printf("����������� ����� ������ ����������:\n");
	for (num = 1; num < upto; num++) {
		if (IsAutomorph(num))
			printf(" %lu ^2 = %.0lf \n", num, pow(num, 2));
	}
}

bool IsAutomorph(int num) {
	long int sq;
	sq = pow(num, 2);
	while (num) {
		if (num % 10 != sq % 10) return false;
		else {
			num /= 10;
			sq /= 10;
		}
	}
	return true;
}