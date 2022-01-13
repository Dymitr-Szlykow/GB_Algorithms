#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lesson5.h"
#include "lesson6.h"

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#define bool int
#define true 1
#define false 0

//#pragma warning(disable : 4996)


/// <summary>
/// 1. Реализовать простейшую хеш - функцию. На вход функции подается строка, на выходе сумма кодов символов.
/// </summary>
void Task_6_1(void) {

}

/// <summary>
/// 2. Переписать программу, реализующую двоичное дерево поиска.
///    а) Добавить в него обход дерева различными способами;
///    б) Реализовать поиск в двоичном дереве поиска;
///    в)* Добавить в программу обработку командной строки, с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.
/// </summary>
void Task_6_2(void) {

}

/// <summary>
/// 3. * Разработать базу данных студентов из полей «Имя», «Возраст», «Табельный номер», в которой использовать все знания, полученные на уроках.
///    Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных (возраст, вес).
/// </summary>
void Task_6_3(void) {

}


// - - - - - - - - - - - - - - - -
//   g e n e r i c  e l e m e n t s


/// <summary>вывод значения обобщенного элемента как int</summary>
void PrintValue_ToInt(const void* value) {
	printf("%d", ToInt(value));
}

/// <summary>вывод значения обобщенного элемента как int с пробелами</summary>
void PrintValue_ToInt_withSpaces(const void* value) {
	printf("  %2d", ToInt(value));
}

/// <summary>запись значения обобщенного элемента как int</summary>
int WriteIntValue(const void* value, char* targetString) {
	return fprintf(targetString, "%d", *((int*)value));
}


// - - - - - - - - - - - - - - - -
//   T R E E  N O D E


/// <summary>создает узел дерева в динамической памяти</summary>
TreeNode* NewTreeNode(const void* value, size_t valSize) {
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
	if (res) {
		res->valSize = valSize;
		res->left = res->right = NULL;
		res->value = malloc(valSize);
		AssignValue(res->value, value, valSize);
	}
	return res;
}

/// <summary>возвращает высоту ветви дерева</summary>
/// <returns>высота дерева; -1, если дерево пустое</returns>
int Subtree_GetTreeHeight(TreeNode* root) {
	if (!root) return -1;
	else {
		int leftSubtreeHeight = Subtree_GetTreeHeight(root->left),
			rightSubtreeHeight = Subtree_GetTreeHeight(root->right);
		return leftSubtreeHeight > rightSubtreeHeight ? leftSubtreeHeight + 1 : rightSubtreeHeight + 1;
	}
}

/// <summary>проход по дереву depth-first, preorder (root-left-right)</summary>
/// <param name="action">действие с данными узлов</param>
void Subtree_TraversalPreorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		action(root->value);
		Subtree_TraversalPreorder(root->left, action);
		Subtree_TraversalPreorder(root->right, action);
	}
}

/// <summary>проход по дереву depth-first, inorder (left-root-right)</summary>
/// <param name="action">действие с данными узлов</param>
void Subtree_TraversalInorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		Subtree_TraversalInorder(root->left, action);
		action(root->value);
		Subtree_TraversalInorder(root->right, action);
	}
}

/// <summary>проход по дереву depth-first, postorder (left-right-root)</summary>
/// <param name="action">действие с данными узлов</param>
void Subtree_TraversalPostorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		Subtree_TraversalPostorder(root->left, action);
		Subtree_TraversalPostorder(root->right, action);
		action(root->value);
	}
}

/// <summary>проход по дереву bredth-first</summary>
/// <param name="action">действие с данными узлов</param>
void Subtree_TraversalLevelorder(TreeNode* root, void (*action)(void*)) {
	if (root == NULL) return;
	Queue* queue = NewQueue(sizeof(TreeNode*));  // см. lesson5.c, строка 788
	if (queue == NULL) return;

	TreeNode* current = root;
	bool stop = false;

	while (!stop) {
		if (current->left) Queue_Enqueue(queue, &(current->left));
		if (current->right) Queue_Enqueue(queue, &(current->right));
		action(current->value);
		stop = Queue_Dequeue(queue, &current);
	}

	Queue_Dispose(queue);
}

/// <summary>вывод дерева в "скобочной форме"</summary>
/// <param name="printValueMethod">метод вывода значения обобщенного элемента</param>
void Subtree_PrintParenthesesForm(TreeNode* obj, void (*printValueMethod)(const void*)) {
	if (obj) {
		printValueMethod(obj->value);
		if (obj->left || obj->right) {
			printf("(");
			Subtree_PrintParenthesesForm(obj->left, printValueMethod);
			printf(",");
			Subtree_PrintParenthesesForm(obj->right, printValueMethod);
			printf(")");
		}
	}
	else printf("NULL");
}

/// <summary>запись дерева в "скобочной форме"</summary>
/// <param name="printValueMethod">метод записи значения обобщенного элемента</param>
void Subtree_WriteParenthesesForm(TreeNode* obj, int (*writeValueMethod)(const void*, char*), char** targetString) {
	int shift;
	if (obj) {
		if (shift = writeValueMethod(obj->value, *targetString) > 0) *targetString += shift;
		if (obj->left || obj->right) {
			fprintf((*targetString)++, "(");
			Subtree_WriteParenthesesForm(obj->left, writeValueMethod, &targetString); // char***
			fprintf((*targetString)++, ",");
			Subtree_WriteParenthesesForm(obj->right, writeValueMethod, targetString); // УКАЗАТЕЛЬ на переменную первично вызвавшей
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
	// TODO
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

void Tree_Dispose(Tree* obj) {
	if (obj->root) Subtree_Dispose(obj->root);
	free(obj);
}


// - - - - - - - - - - - - - - - -
//   B I N A R Y  S E A R C H  T R E E


int BST_Insert(Tree* obj, const void* newValue, int(*compareMethod)(const void*, const void*)) {
	if (obj == NULL) return 1;
	TreeNode* temp = BSSubtree_Add(obj->root, newValue, obj->valSize, compareMethod);
	if (temp == NULL) return 1;
	else obj->root = temp;
	return 0;
}

/// <summary>добавляет элемент в ветвь дерева на нижнем уровне, не сохраняет уравновешенность дерева</summary>
/// <param name="compareMethod">метод сравнения значений элементов</param>
/// <returns></returns>
TreeNode* BSSubtree_Add(TreeNode* root, const void* newValue, size_t valSize, int(*compareMethod)(const void*, const void*)) {
	if (root == NULL) {
		root = NewTreeNode(newValue, valSize);
	}
	else if (compareMethod(root->value, newValue) > 0) {
		root->right = BSSubtree_Add(root->right, newValue, valSize, compareMethod);
	}
	else {
		root->left = BSSubtree_Add(root->left, newValue, valSize, compareMethod);
	}
	return root;
}

/// <summary>поиск элемента по значению</summary>
/// <param name="compareMethod">метод сравнения значений элементов</param>
/// <returns>указатель на верхний элемент с искомым значением</returns>
TreeNode* BST_Search(TreeNode* root, const void* searchValue, int(*compareMethod)(const void*, const void*)) {
	if (root) {
		switch (compareMethod(root->value, searchValue)) {
		case 0: return root;
		case 1: return BST_Search(root->right, searchValue, compareMethod);
		case -1: return BST_Search(root->left, searchValue, compareMethod);
		}
	}
	return NULL;
}

/// <returns>указатель на наименьший элемент в бинарном дереве поиска</returns>
TreeNode* BSSubtree_GetMinElement(TreeNode* root) {
	while (root != NULL) {
		root = root->left;
	}
	return root;
}

/// <returns>указатель на натбольший элемент в бинарном дереве поиска</returns>
TreeNode* BSSubtree_GetMaxElement(TreeNode* root) {
	while (root != NULL) {
		root = root->right;
	}
	return root;
}