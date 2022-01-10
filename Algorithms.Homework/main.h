#pragma once

typedef struct menu {
	int lastline, selected, code;
	char* MenuLines[16];
	void (*Enter)(Menu* running);
} Menu;


void MenuLoop(Menu StartMenu);
void SwitchLessons(Menu* running);
void Switch_Lesson1(Menu* running);
void Switch_Lesson2(Menu* running);
void Switch_Lesson4(Menu* running);
void Switch_Lesson5(Menu* running);
void RunTask(void (*task)(void), char* header);

Menu NewMainMenu();
void TurnMenu_lesson1(Menu* obj);
void TurnMenu_lesson2(Menu* obj);
void TurnMenu_lesson4(Menu* obj);
void TurnMenu_lesson5(Menu* obj);
void TurnMenu_lesson6(Menu* obj);
void TurnMenu_lesson7(Menu* obj);
void TurnMenu_lesson8(Menu* obj);

void OldMenu_CommandLine(Menu StartMenu);
void OldMenu_print(Menu* running);
void OldMenu_Lessons_print(void);
void OldMenu_Lesson1_print(void);
void OldMenu_Lesson2_print(void);