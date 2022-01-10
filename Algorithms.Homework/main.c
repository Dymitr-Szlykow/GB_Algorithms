#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include "lesson1.h"
#include "lesson2.h"
#include "lesson3.h"
#include "lesson4.h"
#include "lesson5.h"
#include "lesson6.h"
#include "main.h"


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	//OldMenu_CommandLine(NewMainMenu());
	MenuLoop(NewMainMenu());
	//scanf("");
	return 0;
}

/// <summary>�������� ���� ����</summary>
/// <param name="StartMenu">��������� ��������� ����</param>
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
				RunningMenu.Enter(&RunningMenu);
			else if (RunningMenu.code == 0)
				break;
			else
				RunningMenu = NewMainMenu();
		}
	} while (1);

	printf("\n");
}

/// <summary>������������ ������� �� ���� � ������������� �������</summary>
void RunTask(void (*task)(void), char* header) {
	system("cls");
	printf("\t%s\n\n", header);
	task();
	printf("\n\n������� ����� �������, ����� ����������...");
	getch();
}


/// <summary>������� ������� ����</summary>
Menu NewMainMenu() {
	Menu res;
	res.code = 0;
	res.selected = 1;
	res.Enter = SwitchLessons;
	res.MenuLines[0] = "������������ ����� �����:";
	res.MenuLines[1] = "������� 1. ������� ���������.";
	res.MenuLines[2] = "������� 2. ��������������� ���������. ��������.";
	res.MenuLines[3] = "������� 3. ����� � �������. ������� ����������.";
	res.MenuLines[4] = "������� 4. ������������ ����������������. ����� ���������.";
	res.MenuLines[5] = "������� 5. ������������ ��������� ������.";
	//res.MenuLines[6] = "������� 6. �������.";
	//res.MenuLines[7] = "������� 7. �����. ��������� �� ������.";
	//res.MenuLines[8] = "������� 8. ������� ����������.";
	res.MenuLines[6] = "�����.";
	res.lastline = 6;
	return res;
}
/// <summary>������������ �� �������� ����</summary>
void SwitchLessons(Menu* running) {
	switch (running->selected) {
	case 1: TurnMenu_lesson1(running); break;
	case 2: TurnMenu_lesson2(running); break;
	case 3: RunTask(RunLesson3, running->MenuLines[running->selected]); break;
	case 4: TurnMenu_lesson4(running); break;
	case 5: TurnMenu_lesson5(running); break;
		//case 6: TurnMenu_lesson6(running); break;
		//case 7: TurnMenu_lesson7(running); break;
		//case 8: TurnMenu_lesson8(running); break;
	}
}

/// <summary>����������� �� ���� ������� �����</summary>
void TurnMenu_lesson1(Menu* obj) {
	obj->code = 1;
	obj->selected = 1;
	obj->Enter = Switch_Lesson1;
	obj->MenuLines[0] = "������� ������:";
	obj->MenuLines[1] = "1-1. ������ ����� ����.";
	obj->MenuLines[2] = "1-2. ������������ �� ������� �����.";
	obj->MenuLines[3] = "1-3. ����� �������������� ����������.";
	obj->MenuLines[4] = "1-4. ������� ����������� ���������.";
	obj->MenuLines[5] = "1-7. ����� ��������� ������.";
	obj->MenuLines[6] = "1-13. ��������� ����� �� ������ �� ���.";
	obj->MenuLines[7] = "1-14. ����������� �����.";
	obj->MenuLines[8] = "����� � ������� ����.";
	obj->lastline = 8;
}
/// <summary>������������ ������� �� ���� ������� �����</summary>
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

/// <summary>����������� �� ���� ������� �����</summary>
void TurnMenu_lesson2(Menu* obj) {
	obj->code = 2;
	obj->selected = 1;
	obj->Enter = Switch_Lesson2;
	obj->MenuLines[0] = "������� ������:";
	obj->MenuLines[1] = "2-1. ������� �� ���������� ������� � ��������.";
	obj->MenuLines[2] = "2-2. ���������� ����� a � ������� b.";
	//obj->MenuLines[3] = "2-3. ����������� �����������.";
	obj->MenuLines[3] = "����� � ������� ����.";
	obj->lastline = 3;
}
/// <summary>������������ ������� �� ���� ������� �����</summary>
void Switch_Lesson2(Menu* running) {
	switch (running->selected) {
	case 1: RunTask(Task_2_1, running->MenuLines[running->selected]); break;
	case 2: RunTask(Task_2_2, running->MenuLines[running->selected]); break;
	case 3: RunTask(Task_2_3, running->MenuLines[running->selected]); break;
	}
}

/// <summary>����������� �� ���� ���������� �����</summary>
void TurnMenu_lesson4(Menu* obj) {
	obj->code = 4;
	obj->selected = 1;
	obj->Enter = Switch_Lesson4;
	obj->MenuLines[0] = "������� ���������:";
	obj->MenuLines[1] = "4-1. ������� ���������� ��������� � �������������.";
	obj->MenuLines[2] = "4-2. ���������� ����� ������������ ������������������.";
	//obj->MenuLines[3] = "4-3. ...";
	obj->MenuLines[3] = "test. ���������� ����������.";
	obj->MenuLines[4] = "����� � ������� ����.";
	obj->lastline = 4;
}
/// <summary>������������ ������� �� ���� ���������� �����</summary>
void Switch_Lesson4(Menu* running) {
	switch (running->selected) {
	case 1: RunTask(Task_4_1, running->MenuLines[running->selected]); break;
	case 2: RunTask(Task_4_2, running->MenuLines[running->selected]); break;
	case 3: RunTask(test_PointerAriphmetics, running->MenuLines[running->selected]); break;
		//case 3: RunTask(Task_2_3, running->MenuLines[running->selected]); break; // not implemmented
	}
}

/// <summary>����������� �� ���� ������ �����</summary>
void TurnMenu_lesson5(Menu* obj) {
	obj->code = 5;
	obj->selected = 1;
	obj->Enter = Switch_Lesson5;
	obj->MenuLines[0] = "������� �����:";
	obj->MenuLines[1] = "5-1. ������� � �������� ������� � �������������� �����.";
	obj->MenuLines[2] = "5-3. �������� ��������� ������������������.";
	obj->MenuLines[3] = "5-4. Test: linked list, ����������� ������������ ������.";
	obj->MenuLines[4] = "5-5. ������� �� ��������� ������ ��������������� ��������� � �����������.";
	obj->MenuLines[5] = "5-6. Test: queue, �� ������ �������� ������.";
	obj->MenuLines[6] = "5-6. Test: queue, �� ������ �������.";
	obj->MenuLines[7] = "test: List (dynamic array).";
	obj->MenuLines[8] = "����� � ������� ����.";
	obj->lastline = 8;
}
/// <summary>������������ ������� �� ���� ������ �����</summary>
void Switch_Lesson5(Menu* running) {
	switch (running->selected) {
	case 1: RunTask(Task_5_1, running->MenuLines[running->selected]); break;
	case 2: RunTask(Task_5_3, running->MenuLines[running->selected]); break;
	case 3: RunTask(Task_5_4, running->MenuLines[running->selected]); break;
	case 4: RunTask(Task_5_5, running->MenuLines[running->selected]); break;
	case 5: RunTask(test_QueueLinked, running->MenuLines[running->selected]); break;
	case 6: RunTask(test_QueueArray, running->MenuLines[running->selected]); break;
	case 7: RunTask(test_DynamicList, running->MenuLines[running->selected]); break;
	}
}

void TurnMenu_lesson6(Menu* obj) {}
void TurnMenu_lesson7(Menu* obj) {}
void TurnMenu_lesson8(Menu* obj) {}


/// <summary>������� ���� ������ ������ ���� (��������� ������)</summary>
/// <param name="StartMenu">��������� ��������� ����</param>
void OldMenu_CommandLine(Menu StartMenu) {
	int input;
	Menu RunningMenu = StartMenu;

	do {
		system("cls");
		OldMenu_print(&RunningMenu);
		scanf("%i", &input);

		if (0 < input && input <= RunningMenu.lastline) {
			RunningMenu.selected = input;
			RunningMenu.Enter(&RunningMenu);
		}
		else if (input == 0) {
			if (RunningMenu.code == 0)
				break;
			else
				RunningMenu = NewMainMenu();
		}
		else {
			printf("������ �����\n");
		}

	} while (1);

	printf("���������� ������\n");
}

void OldMenu_print(Menu* running) {
	switch (running->code) {
	case 0: OldMenu_Lessons_print(); break;
	case 1: OldMenu_Lesson1_print(); break;
	case 2: OldMenu_Lesson2_print(); break;
	}
	printf("\n������� ����� ������� (\'0\' - �����): ");
}

void OldMenu_Lessons_print() {
	printf("������������ ����� �����:");
	printf("\n  ������� 1. ������� ���������.");
	printf("\n  ������� 2. ��������������� ���������. ��������.");
	printf("\n  ������� 3. ����� � �������. ������� ����������.");
}

void OldMenu_Lesson1_print() {
	printf("������������ ����� ������� �������:");
	printf("\n  1) ������ ����� ����;");
	printf("\n  2) ������������ �� ������� �����;");
	printf("\n  3) ����� �������������� ����������;");
	printf("\n  4) ������� ����������� ���������;");
	printf("\n  5) ����� ��������� ������;");
	printf("\n  6) ��������� ����� �� ������ �� ���;");
	printf("\n  7) ����������� �����.");
}

void OldMenu_Lesson2_print() {
	printf("������������ ����� ������� �������:");
	printf("\n  1) ������� �� ���������� ������� � ��������;");
	printf("\n  2) ���������� ����� a � ������� b;");
	//printf("\n  3) ����������� �����������;");
}