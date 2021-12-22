#include <conio.h>
#include <locale.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0


typedef struct menu Menu;
void NewMenu(Menu StartMenu);

void MenuEnter(Menu* running);
void SwitchLessons(Menu* running);
void Switch_Lesson1(int selected);
void Switch_Lesson2(int selected);

Menu NewMainMenu();
void TurnMenu_lesson1(Menu* this);
void TurnMenu_lesson2(Menu* this);
void TurnMenu_lesson3(Menu* this);
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
	int lastline, selected, ReadyToTerminate;
	char* MenuLines[16];
};


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	//OldMenu_CommandLine(NewMainMenu());
	NewMenu(NewMainMenu());
	return 0;
}

void NewMenu(Menu StartMenu) {
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
			else if (RunningMenu.ReadyToTerminate)
				break;
			else
				RunningMenu = NewMainMenu();
		}
	} while (1);

	printf("\n");
	//scanf("");
}

void MenuEnter(Menu* running) {
	if (running->MenuLines[0] == "Практическая часть курса:") {
		SwitchLessons(running);
	}
	else {
		system("cls");
		printf("\t%s\n\n", running->MenuLines[running->selected]);

		if (running->MenuLines[0] == "Занятие первое:") { Switch_Lesson1(running->selected); }
		else if (running->MenuLines[0] == "Занятие второе:") { Switch_Lesson2(running->selected); }

		printf("\n\nНажмите любую клавишу, чтобы продолжить...");
		getch();
	}
}

void SwitchLessons(Menu* running) {
	switch (running ->selected) {
	case 1: TurnMenu_lesson1(running); break;
	case 2: TurnMenu_lesson2(running); break;
	//case 3: TurnMenu_lesson3(running); break;
	//case 4: TurnMenu_lesson4(running); break;
	//case 5: TurnMenu_lesson5(running); break;
	//case 6: TurnMenu_lesson6(running); break;
	//case 7: TurnMenu_lesson7(running); break;
	//case 8: TurnMenu_lesson8(running); break;
	}
}

void Switch_Lesson1(int selected) {
	switch (selected) {
	case 1: Task_1_1(); break;
	case 2: Task_1_2(); break;
	case 3: Task_1_3(); break;
	case 4: Task_1_4(); break;
	case 5: Task_1_7(); break;
	case 6: Task_1_13(); break;
	case 7: Task_1_14(); break;
	}
}

void Switch_Lesson2(int selected) {
	switch (selected) {
	case 1: Task_2_1(); break;
	case 2: Task_2_2(); break;
	case 3: Task_2_3(); break;
	}
}


Menu NewMainMenu() {
	Menu res;
	res.ReadyToTerminate = true;
	res.selected = 1;
	res.lastline = 3;
	res.MenuLines[0] = "Практическая часть курса:";
	res.MenuLines[1] = "Занятие 1. Простые алгоритмы.";
	res.MenuLines[2] = "Занятие 2. Асимптотическая сложность. Рекурсия.";
	//res.MenuLines[3] = "Занятие 3. Поиск в массиве.";
	//res.MenuLines[4] = "Занятие 4. Динамическое программирование.";
	//res.MenuLines[5] = "Занятие 5. Динамические структуры данных.";
	//res.MenuLines[6] = "Занятие 6. Деревья.";
	//res.MenuLines[7] = "Занятие 7. Графы.";
	//res.MenuLines[8] = "Занятие 8. Сложные сортировки.";
	res.MenuLines[3] = "Выход.";
	return res;
}

void TurnMenu_lesson1(Menu* this) {
	this->ReadyToTerminate = false;
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

void TurnMenu_lesson2(Menu* this) {
	this->ReadyToTerminate = false;
	this->selected = 1;
	this->lastline = 3;
	this->MenuLines[0] = "Занятие второе:";
	this->MenuLines[1] = "2-1. Перевод из десятичной системы в двоичную.";
	this->MenuLines[2] = "2-2. Возведение числа a в степень b.";
	//this->MenuLines[3] = "2-3. Исполнитель Калькулятор.";
	this->MenuLines[3] = "Назад в главное меню.";
}

void TurnMenu_lesson3(Menu* this) {}
void TurnMenu_lesson4(Menu* this) {}
void TurnMenu_lesson5(Menu* this) {}
void TurnMenu_lesson6(Menu* this) {}
void TurnMenu_lesson7(Menu* this) {}
void TurnMenu_lesson8(Menu* this) {}



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
			if (RunningMenu.ReadyToTerminate)
				break;
			else
				RunningMenu = NewMainMenu();
		}
		else {
			printf("ошибка ввода\n");
		}

	} while (1);

	printf("завершение работы\n");
	return 0;
}

void OldMenu_print(Menu* running) {
	if (running->MenuLines[0] == "Практическая часть курса:") {
		OldMenu_Lessons_print();
	}
	else if (running->MenuLines[0] == "Занятие первое:") {
		OldMenu_Lesson1_print();
	}
	else if (running->MenuLines[0] == "Занятие второе:") {
		OldMenu_Lesson2_print();
	}
	else {
		printf("не разобрал. какое занятие? :(\n");
	}
}

void OldMenu_Lessons_print() {
	printf("Практическая часть курса:");
	printf("\n  Занятие 1. Простые алгоритмы;");
	printf("\n  Занятие 2. Асимптотическая сложность. Рекурсия;");
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