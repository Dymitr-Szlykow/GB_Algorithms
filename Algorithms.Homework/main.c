#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include "lesson1.c"
#include "lesson2.c"
#include "lesson3.c"

#define bool int
#define true 1
#define false 0


typedef struct menu Menu;
void MenuLoop(Menu StartMenu);
void MenuEnter(Menu* running);
inline void SwitchLessons(Menu* running);
inline void Switch_Lesson1(Menu* running);
inline void Switch_Lesson2(Menu* running);
void RunTask(void (*task)(void), char* header);

Menu NewMainMenu();
void TurnMenu_lesson1(Menu* this);
void TurnMenu_lesson2(Menu* this);
void TurnMenu_lesson4(Menu* this);
void TurnMenu_lesson5(Menu* this);
void TurnMenu_lesson6(Menu* this);
void TurnMenu_lesson7(Menu* this);
void TurnMenu_lesson8(Menu* this);

void OldMenu_CommandLine(Menu StartMenu);
void OldMenu_print(Menu* running);
void OldMenu_Lessons_print(void);
void OldMenu_Lesson1_print(void);
void OldMenu_Lesson2_print(void);


struct menu {
	int lastline, selected, code;
	char* MenuLines[16];
};


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	//OldMenu_CommandLine(NewMainMenu());
	MenuLoop(NewMainMenu());
	//scanf("");
	return 0;
}

/// <summary>основной цикл меню</summary>
/// <param name="StartMenu">начальные параметры меню</param>
void MenuLoop(Menu StartMenu) {
	int i;
	char input;
	Menu RunningMenu = StartMenu;

	do {
		system("cls");
		printf(RunningMenu.MenuLines[0]);
		for (i = 1; i <= RunningMenu.lastline; i++) {
			printf("\n%s%s", RunningMenu.selected == i ? "  --> " : "      ", RunningMenu.MenuLines[i]);
		}

		input = getch();

		if (input == -32 || input == 0 || input == 224) {
			input = getch();
			if (input == 72) {
				if (RunningMenu.selected > 1) RunningMenu.selected--;
				else RunningMenu.selected = RunningMenu.lastline;
			}
			else if (input == 80) {
				if (RunningMenu.selected < RunningMenu.lastline) RunningMenu.selected++;
				else RunningMenu.selected = 1;
			}
		}
		else if (input == '\r') {
			if (RunningMenu.selected != RunningMenu.lastline)
				MenuEnter(&RunningMenu);
			else if (RunningMenu.code == 0)
				break;
			else
				RunningMenu = NewMainMenu();
		}
	} while (1);

	printf("\n");
}

/// <summary>переключение при нажатии Enter</summary>
void MenuEnter(Menu* running) {
	switch (running->code) {
	case 0: SwitchLessons(running); break;
	case 1: Switch_Lesson1(running); break;
	case 2: Switch_Lesson2(running); break;
	}
}

/// <summary>переключение из главного меню</summary>
void SwitchLessons(Menu* running) {
	switch (running ->selected) {
	case 1: TurnMenu_lesson1(running); break;
	case 2: TurnMenu_lesson2(running); break;
	case 3: RunTask(RunLesson3, running->MenuLines[running->selected]); break;
	//case 4: TurnMenu_lesson4(running); break;
	//case 5: TurnMenu_lesson5(running); break;
	//case 6: TurnMenu_lesson6(running); break;
	//case 7: TurnMenu_lesson7(running); break;
	//case 8: TurnMenu_lesson8(running); break;
	}
}

/// <summary>переключение задания из меню первого урока</summary>
void Switch_Lesson1(Menu* running) {
	switch (running->selected) {
	case 1: RunTask(Task_1_1, running->MenuLines[running->selected]); break;
	case 2: RunTask(Task_1_2, running->MenuLines[running->selected]); break;
	case 3: RunTask(Task_1_3, running->MenuLines[running->selected]); break;
	case 4: RunTask(Task_1_4, running->MenuLines[running->selected]); break;
	case 5: RunTask(Task_1_7, running->MenuLines[running->selected]); break;
	case 6: RunTask(Task_1_13, running->MenuLines[running->selected]); break;
	case 7: RunTask(Task_1_14, running->MenuLines[running->selected]); break;
	}
}

/// <summary>переключение задания из меню второго урока</summary>
void Switch_Lesson2(Menu* running) {
	switch (running->selected) {
	case 1: RunTask(Task_2_1, running->MenuLines[running->selected]); break;
	case 2: RunTask(Task_2_2, running->MenuLines[running->selected]); break;
	case 3: RunTask(Task_2_3, running->MenuLines[running->selected]); break;
	}
}

/// <summary>осуществляет переход от меню к представлению задания</summary>
void RunTask(void (*task)(void), char* header) {
	system("cls");
	printf("\t%s\n\n", header);
	task();
	printf("\n\nНажмите любую клавишу, чтобы продолжить...");
	getch();
}

/// <summary>создает главное меню</summary>
/// <returns>главное меню</returns>
Menu NewMainMenu() {
	Menu res;
	res.code = 0;
	res.selected = 1;
	res.lastline = 4;
	res.MenuLines[0] = "Практическая часть курса:";
	res.MenuLines[1] = "Занятие 1. Простые алгоритмы.";
	res.MenuLines[2] = "Занятие 2. Асимптотическая сложность. Рекурсия.";
	res.MenuLines[3] = "Занятие 3. Поиск в массиве. Простые сортировки.";
	//res.MenuLines[4] = "Занятие 4. Динамическое программирование. Поиск возвратом.";
	//res.MenuLines[5] = "Занятие 5. Динамические структуры данных.";
	//res.MenuLines[6] = "Занятие 6. Деревья.";
	//res.MenuLines[7] = "Занятие 7. Графы. Алгоритмы на графах.";
	//res.MenuLines[8] = "Занятие 8. Сложные сортировки.";
	res.MenuLines[4] = "Выход.";
	return res;
}

/// <summary>переключает на меню первого урока</summary>
void TurnMenu_lesson1(Menu* this) {
	this->code = 1;
	this->selected = 1;
	this->lastline = 8;
	this->MenuLines[0] = "Занятие первое:";
	this->MenuLines[1] = "1-1. Индекс массы тела.";
	this->MenuLines[2] = "1-2. Максимальное из четырех чисел.";
	this->MenuLines[3] = "1-3. Обмен целочисленными значениями.";
	this->MenuLines[4] = "1-4. Решение квадратного уравнения.";
	this->MenuLines[5] = "1-7. Цвета шахматных клеток.";
	this->MenuLines[6] = "1-13. Случайные числа от одного до ста.";
	this->MenuLines[7] = "1-14. Автоморфные числа.";
	this->MenuLines[8] = "Назад в главное меню.";
}

/// <summary>переключает на меню второго урока</summary>
void TurnMenu_lesson2(Menu* this) {
	this->code = 2;
	this->selected = 1;
	this->lastline = 3;
	this->MenuLines[0] = "Занятие второе:";
	this->MenuLines[1] = "2-1. Перевод из десятичной системы в двоичную.";
	this->MenuLines[2] = "2-2. Возведение числа a в степень b.";
	//this->MenuLines[3] = "2-3. Исполнитель Калькулятор.";
	this->MenuLines[3] = "Назад в главное меню.";
}

void TurnMenu_lesson4(Menu* this) {}
void TurnMenu_lesson5(Menu* this) {}
void TurnMenu_lesson6(Menu* this) {}
void TurnMenu_lesson7(Menu* this) {}
void TurnMenu_lesson8(Menu* this) {}


/// <summary>главный цикл первой версии меню (командная строка)</summary>
/// <param name="StartMenu">начальные параметры меню</param>
void OldMenu_CommandLine(Menu StartMenu) {
	int input;
	Menu RunningMenu = StartMenu;

	do {
		system("cls");
		OldMenu_print(&RunningMenu);
		scanf("%i", &input);

		if (0 < input && input <= RunningMenu.lastline) {
			RunningMenu.selected = input;
			MenuEnter(&RunningMenu);
		}
		else if (input == 0) {
			if (RunningMenu.code == 0)
				break;
			else
				RunningMenu = NewMainMenu();
		}
		else {
			printf("ошибка ввода\n");
		}

	} while (1);

	printf("завершение работы\n");
}

void OldMenu_print(Menu* running) {
	switch (running->code) {
	case 0: OldMenu_Lessons_print();
	case 1: OldMenu_Lesson1_print();
	case 2: OldMenu_Lesson2_print();
	}
}

void OldMenu_Lessons_print() {
	printf("Практическая часть курса:");
	printf("\n  Занятие 1. Простые алгоритмы.");
	printf("\n  Занятие 2. Асимптотическая сложность. Рекурсия.");
	printf("\n  Занятие 3. Поиск в массиве. Простые сортировки.");
	printf("\nВведите номер занятия (\'0\' - выход): ");
}

void OldMenu_Lesson1_print() {
	printf("Практическая часть первого занятия:");
	printf("\n  1) индекс массы тела;");
	printf("\n  2) максимальное из четырех чисел;");
	printf("\n  3) обмен целочисленными значениями;");
	printf("\n  4) решение квадратного уравнения;");
	printf("\n  5) цвета шахматных клеток;");
	printf("\n  6) случайные числа от одного до ста;");
	printf("\n  7) автоморфные числа.");
	printf("\nВведите номер задания (\'0\' - назад): ");
}

void OldMenu_Lesson2_print() {
	printf("Практическая часть второго занятия:");
	printf("\n  1) перевод из десятичной системы в двоичную;");
	printf("\n  2) возведение числа a в степень b;");
	//printf("\n  3) исполнитель Калькулятор;");
	printf("\nВведите номер задания (\'0\' - назад): ");
}