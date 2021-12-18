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

void OldMenu_Lesson1(void);
void OldMenu_Lesson1_print(void);


struct menu {
	int lastline, selected, ReadyToTerminate;
	char* MenuLines[16];
};


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	//OldMenu_Lesson1();
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
	//switch (*selected) {
	//case 1: Task_2_1(); break;
	//case 2: Task_2_2(); break;
	//case 3: Task_2_3(); break;
	//}
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
	this->lastline = 1;
	this->MenuLines[0] = "Занятие второе:";
	//this->MenuLines[1] = "2-1. .";
	//this->MenuLines[2] = "2-2. .";
	//this->MenuLines[3] = "2-3. .";
	this->MenuLines[1] = "Назад в главное меню.";
}



void OldMenu_Lesson1_print() {
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

void OldMenu_Lesson1() {
	int sel;
	do {
		OldMenu_Lesson1_print();
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