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
/// 1. ����������� ���������� ��� - �������. �� ���� ������� �������� ������, �� ������ ����� ����� ��������.
/// </summary>
void Task_6_1(void) {

}

/// <summary>
/// 2. ���������� ���������, ����������� �������� ������ ������.
///    �) �������� � ���� ����� ������ ���������� ���������;
///    �) ����������� ����� � �������� ������ ������;
///    �)* �������� � ��������� ��������� ��������� ������, � ������� ������� ����� ���������, �� ������ ����� ��������� ������, ����� ������� �������� ������.
/// </summary>
void Task_6_2(void) {

}

/// <summary>
/// 3. * ����������� ���� ������ ��������� �� ����� �����, ��������, ���������� �����, � ������� ������������ ��� ������, ���������� �� ������.
///    �������� ������ � �������� ������ ������. ���������� ����� �� ������-������ ���� ���� ������ (�������, ���).
/// </summary>
void Task_6_3(void) {

}


// - - - - - - - - - - - - - - - -
//   g e n e r i c  e l e m e n t s


/// <summary>����� �������� ����������� �������� ��� int</summary>
void PrintValue_ToInt(const void* value) {
	printf("%d", ToInt(value));
}

/// <summary>����� �������� ����������� �������� ��� int � ���������</summary>
void PrintValue_ToInt_withSpaces(const void* value) {
	printf("  %2d", ToInt(value));
}

/// <summary>������ �������� ����������� �������� ��� int</summary>
int WriteIntValue(const void* value, char* targetString) {
	return fprintf(targetString, "%d", *((int*)value));
}


// - - - - - - - - - - - - - - - -
//   T R E E  N O D E


/// <summary>������� ���� ������ � ������������ ������</summary>
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

/// <summary>���������� ������ ����� ������</summary>
/// <returns>������ ������; -1, ���� ������ ������</returns>
int Subtree_GetTreeHeight(TreeNode* root) {
	if (!root) return -1;
	else {
		int leftSubtreeHeight = Subtree_GetTreeHeight(root->left),
			rightSubtreeHeight = Subtree_GetTreeHeight(root->right);
		return leftSubtreeHeight > rightSubtreeHeight ? leftSubtreeHeight + 1 : rightSubtreeHeight + 1;
	}
}

/// <summary>������ �� ������ depth-first, preorder (root-left-right)</summary>
/// <param name="action">�������� � ������� �����</param>
void Subtree_TraversalPreorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		action(root->value);
		Subtree_TraversalPreorder(root->left, action);
		Subtree_TraversalPreorder(root->right, action);
	}
}

/// <summary>������ �� ������ depth-first, inorder (left-root-right)</summary>
/// <param name="action">�������� � ������� �����</param>
void Subtree_TraversalInorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		Subtree_TraversalInorder(root->left, action);
		action(root->value);
		Subtree_TraversalInorder(root->right, action);
	}
}

/// <summary>������ �� ������ depth-first, postorder (left-right-root)</summary>
/// <param name="action">�������� � ������� �����</param>
void Subtree_TraversalPostorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		Subtree_TraversalPostorder(root->left, action);
		Subtree_TraversalPostorder(root->right, action);
		action(root->value);
	}
}

/// <summary>������ �� ������ bredth-first</summary>
/// <param name="action">�������� � ������� �����</param>
void Subtree_TraversalLevelorder(TreeNode* root, void (*action)(void*)) {
	if (root == NULL) return;
	Queue* queue = NewQueue(sizeof(TreeNode*));  // ��. lesson5.c, ������ 788
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

/// <summary>����� ������ � "��������� �����"</summary>
/// <param name="printValueMethod">����� ������ �������� ����������� ��������</param>
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

/// <summary>������ ������ � "��������� �����"</summary>
/// <param name="printValueMethod">����� ������ �������� ����������� ��������</param>
void Subtree_WriteParenthesesForm(TreeNode* obj, int (*writeValueMethod)(const void*, char*), char** targetString) {
	int shift;
	if (obj) {
		if (shift = writeValueMethod(obj->value, *targetString) > 0) *targetString += shift;
		if (obj->left || obj->right) {
			fprintf((*targetString)++, "(");
			Subtree_WriteParenthesesForm(obj->left, writeValueMethod, &targetString); // char***
			fprintf((*targetString)++, ",");
			Subtree_WriteParenthesesForm(obj->right, writeValueMethod, targetString); // ��������� �� ���������� �������� ���������
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

/// <summary>������������ ������ ���� ��������� �� ������ �����</summary>
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

/// <summary>������������ ������ ���� ��������� � �������� ����</summary>
void Subtree_Dispose(TreeNode* node) {
	if (node->left) Subtree_Dispose(node->left);
	if (node->right) Subtree_Dispose(node->right);
	free(node->value);
	free(node);
}


// - - - - - - - - - - - - - - - -
//   B I N A R Y  T R E E


/// <summary>������������ ������ � ���� ������ �� ����</summary>
/// <param name="accessCode">������-��� ������� - ���������������� �������� �� ������: 0 - ������, 1 - �������</param>
/// <returns>��������� �� ������� ����; NULL, ���� ��� ���, ��� ������������ ��� �������</returns>
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

/// <summary>��������� ������� � ����� ������ �� ������ ������, �� ��������� ���������������� ������</summary>
/// <param name="compareMethod">����� ��������� �������� ���������</param>
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

/// <summary>����� �������� �� ��������</summary>
/// <param name="compareMethod">����� ��������� �������� ���������</param>
/// <returns>��������� �� ������� ������� � ������� ���������</returns>
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

/// <returns>��������� �� ���������� ������� � �������� ������ ������</returns>
TreeNode* BSSubtree_GetMinElement(TreeNode* root) {
	while (root != NULL) {
		root = root->left;
	}
	return root;
}

/// <returns>��������� �� ���������� ������� � �������� ������ ������</returns>
TreeNode* BSSubtree_GetMaxElement(TreeNode* root) {
	while (root != NULL) {
		root = root->right;
	}
	return root;
}