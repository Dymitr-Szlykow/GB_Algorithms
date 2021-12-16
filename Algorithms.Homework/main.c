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
			printf("\n\tИндекс массы тела.\n\n");
			Task_1_1();
			break;
		case 2:
			printf("\n\tМаксимальное из четырех чисел.\n\n");
			Task_1_2();
			break;
		case 3:
			printf("\n\tОбмен целочисленными значениями.\n\n");
			Task_1_3();
			break;
		case 4:
			printf("\n\tРешение квадратного уравнения.\n\n");
			Task_1_4();
			break;
		case 7:
			printf("\n\tЦвета шахматных клеток.\n\n");
			Task_1_7();
			break;
		case 13:
			printf("\n\tСлучайные числа от одного до ста.\n\n");
			Task_1_13();
			break;
		case 14:
			printf("\n\tАвтоморфные числа.\n\n");
			Task_1_14();
			break;
		case 0:
			printf("завершение работы");
			break;
		default:
			printf("ошибка ввода");
		}
		getch();
		system("cls");

	} while (sel != 0);
	return 0;
}

void Lesson1(void) {
	printf("Практическая часть первого занятия:");
	printf("\n  1) индекс массы тела;");
	printf("\n  2) максимальное из четырех чисел;");
	printf("\n  3) обмен целочисленными значениями;");
	printf("\n  4) решение квадратного уравнения;");
	printf("\n  7) цвета шахматных клеток;");
	printf("\n 13) случайные числа от одного до ста;");
	printf("\n 14) автоморфные числа.");
	printf("\nВведите номер задания (\'0\' для выхода): ");
}