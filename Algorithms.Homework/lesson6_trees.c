#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lesson5.h"
#include "lesson6.h"

#define bool int
#define true 1
#define false 0

//#pragma warning(disable : 4996)


// ������� � ������� �6.
// 1. ����������� ���������� ��� - �������. �� ���� ������� �������� ������, �� ������ ����� ����� ��������.
// 2. ���������� ���������, ����������� �������� ������ ������.
//    �) �������� � ���� ����� ������ ���������� ���������;
//    �) ����������� ����� � �������� ������ ������;
//    �)* �������� � ��������� ��������� ��������� ������, � ������� ������� ����� ���������, �� ������ ����� ��������� ������, ����� ������� �������� ������.
// 3. * ����������� ���� ������ ��������� �� ����� �����, ��������, ���������� �����, � ������� ������������ ��� ������, ���������� �� ������.
//    �������� ������ � �������� ������ ������. ���������� ����� �� ������-������ ���� ���� ������ (�������, ���).


/// <summary>
/// 1. ����������� ���������� ��� - �������.�� ���� ������� �������� ������, �� ������ ����� ����� ��������.
/// </summary>
void Task_6_1(void) {

}

void Task_6_2(void) {

}

void Task_6_3(void) {

}


// - - - - - - - - - - - - - - - -
//   g e n e r i c  e l e m e n t s


/// <summary>����� �������� ����������� �������� ��� int</summary>
void PrintValue_ToInt(const void* value) {
	printf("%d", ToInt(value));
}

/// <summary>������ �������� ����������� �������� ��� int</summary>
void WriteIntValue(const void* value, char* targetString) {
	return fprintf(targetString, "%d", *((int*)value));
}


// - - - - - - - - - - - - - - - -
//   T R E E  N O D E


/// <summary>������� ���� ������ � ������������ ������</summary>
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

/// <summary>����� ������ � "��������� �����"</summary>
/// <param name="printValueMethod">����� ������ �������� ����������� ��������</param>
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

/// <summary>������ ������ � "��������� �����"</summary>
/// <param name="printValueMethod">����� ������ �������� ����������� ��������</param>
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