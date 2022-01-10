#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lesson5.h"
#include "lesson6.h"

#define bool int
#define true 1
#define false 0

//#pragma warning(disable : 4996)


// ЗАДАНИЯ к занятию №6.
// 1. Реализовать простейшую хеш - функцию. На вход функции подается строка, на выходе сумма кодов символов.
// 2. Переписать программу, реализующую двоичное дерево поиска.
//    а) Добавить в него обход дерева различными способами;
//    б) Реализовать поиск в двоичном дереве поиска;
//    в)* Добавить в программу обработку командной строки, с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.
// 3. * Разработать базу данных студентов из полей «Имя», «Возраст», «Табельный номер», в которой использовать все знания, полученные на уроках.
//    Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных (возраст, вес).


/// <summary>
/// 1. Реализовать простейшую хеш - функцию.На вход функции подается строка, на выходе сумма кодов символов.
/// </summary>
void Task_6_1(void) {

}

void Task_6_2(void) {

}

void Task_6_3(void) {

}


// - - - - - - - - - - - - - - - -
//   g e n e r i c  e l e m e n t s


/// <summary>вывод значения обобщенного элемента как int</summary>
void PrintValue_ToInt(const void* value) {
	printf("%d", ToInt(value));
}

/// <summary>запись значения обобщенного элемента как int</summary>
void WriteIntValue(const void* value, char* targetString) {
	return fprintf(targetString, "%d", *((int*)value));
}


// - - - - - - - - - - - - - - - -
//   T R E E  N O D E


/// <summary>создает узел дерева в динамической памяти</summary>
TreeNode* NewTreeNode(const void* value, size_t valSize) {
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
	if (res) {
		res->valSize = valSize;
		res->left = res->right = res->parent = NULL;
		res->value = malloc(valSize);
		AssignValue(res->value, value, valSize);
	}
	return res;
}

/// <summary>вывод дерева в "скобочной форме"</summary>
/// <param name="printValueMethod">метод вывода значения обобщенного элемента</param>
void Subtree_PrintParentheses(TreeNode* obj, void (*printValueMethod)(const void*)) {
	if (obj) {
		printValueMethod(obj->value);
		if (obj->left || obj->right) {
			printf("(");
			Subtree_PrintParentheses(obj->left, printValueMethod);
			printf(",");
			Subtree_PrintParentheses(obj->right, printValueMethod);
			printf(")");
		}
	}
	else printf("NULL");
}

/// <summary>запись дерева в "скобочной форме"</summary>
/// <param name="printValueMethod">метод записи значения обобщенного элемента</param>
void Subtree_WriteParenthesesForm(TreeNode* obj, void (*writeValueMethod)(const void*, char*), char** targetString) {
	int shift;
	if (obj) {
		if (shift = printValueMethod(obj->value, *targetString) > 0) *targetString += shift;
		if (obj->left || obj->right) {
			fprintf((*targetString)++, "(");
			Subtree_WriteParenthesesForm(obj->left, writeValueMethod, &targetString);
			fprintf((*targetString)++, ",");
			Subtree_WriteParenthesesForm(obj->right, writeValueMethod, &targetString);
			fprintf((*targetString)++, ")");
		}
	}
	else {
		fprintf((*targetString), "NULL");
		*targetString += 4;
	}
}

TreeNode* Subtree_ReadParenthesesForm(char* sourceString, void (*readValueMethod)(const void*)) {
	TreeNode* res = malloc(sizeof(TreeNode));

}

/// <summary>высвобождает память всех следующих на ветвях узлов</summary>
void Subtree_DisposeBranches(TreeNode* node) {
	if (node->left) {
		Subtree_DisposeBranches(node->left);
		free(node->left->value);
		free(node->left);
	}
	if (node->right) {
		Subtree_DisposeBranches(node->right);
		free(node->right->value);
		free(node->right);
	}
}

/// <summary>высвобождает память всех следующих и текущего узла</summary>
void Subtree_Dispose(TreeNode* node) {
	if (node->left) Subtree_Dispose(node->left);
	if (node->right) Subtree_Dispose(node->right);
	free(node->value);
	free(node);
}


// - - - - - - - - - - - - - - - -
//   B I N A R Y  T R E E


/// <summary>осуществляет доступ к узлу дерева по коду</summary>
/// <param name="accessCode">строка-код доступа - последовательные повороты по ветвям: 0 - налево, 1 - направо</param>
/// <returns>указатель на искомый узел; NULL, если его нет, или некорректный код доступа</returns>
TreeNode* Tree_AccessNode(Tree* tree, char* accessCode) {
	TreeNode* res = tree->root;

	while (*accessCode != '\0') {
		switch (*accessCode) {
		case '0':
			if (res->left) res = res->left;
			else return NULL;
			accessCode++;
			break;
		case '1':
			if (res->right) res = res->right;
			else return NULL;
			accessCode++;
			break;
		default:
			return NULL;
			break;
		}
	}
	return res;
}