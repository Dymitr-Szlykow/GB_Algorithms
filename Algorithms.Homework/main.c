#include <conio.h>
#include <locale.h>
#include <stdio.h>

void Lesson1(void);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	int sel;
	do {
		Lesson1();
		scanf("%i", &sel);

		switch (sel) {
		case 1:
			printf("\n\t������ ����� ����.\n\n");
			Task_1_1();
			break;
		case 2:
			printf("\n\t������������ �� ������� �����.\n\n");
			Task_1_2();
			break;
		case 3:
			printf("\n\t����� �������������� ����������.\n\n");
			Task_1_3();
			break;
		case 4:
			printf("\n\t������� ����������� ���������.\n\n");
			Task_1_4();
			break;
		case 7:
			printf("\n\t����� ��������� ������.\n\n");
			Task_1_7();
			break;
		case 13:
			printf("\n\t��������� ����� �� ������ �� ���.\n\n");
			Task_1_13();
			break;
		case 14:
			printf("\n\t����������� �����.\n\n");
			Task_1_14();
			break;
		case 0:
			printf("���������� ������");
			break;
		default:
			printf("������ �����");
		}
		getch();
		system("cls");

	} while (sel != 0);
	return 0;
}

void Lesson1(void) {
	printf("������������ ����� ������� �������:");
	printf("\n  1) ������ ����� ����;");
	printf("\n  2) ������������ �� ������� �����;");
	printf("\n  3) ����� �������������� ����������;");
	printf("\n  4) ������� ����������� ���������;");
	printf("\n  7) ����� ��������� ������;");
	printf("\n 13) ��������� ����� �� ������ �� ���;");
	printf("\n 14) ����������� �����.");
	printf("\n������� ����� ������� (\'0\' ��� ������): ");
}