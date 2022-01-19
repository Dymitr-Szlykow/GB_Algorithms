#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lesson3.h"
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
/// <param name="action">- �������� � ������� �����</param>
void Subtree_TraversalPreorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		action(root->value);
		Subtree_TraversalPreorder(root->left, action);
		Subtree_TraversalPreorder(root->right, action);
	}
}

/// <summary>������ �� ������ depth-first, inorder (left-root-right)</summary>
/// <param name="action">- �������� � ������� �����</param>
void Subtree_TraversalInorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		Subtree_TraversalInorder(root->left, action);
		action(root->value);
		Subtree_TraversalInorder(root->right, action);
	}
}

/// <summary>������ �� ������ depth-first, postorder (left-right-root)</summary>
/// <param name="action">- �������� � ������� �����</param>
void Subtree_TraversalPostorder(TreeNode* root, void (*action)(void*)) {
	if (root) {
		Subtree_TraversalPostorder(root->left, action);
		Subtree_TraversalPostorder(root->right, action);
		action(root->value);
	}
}

/// <summary>������ �� ������ bredth-first</summary>
/// <param name="action">- �������� � ������� �����</param>
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

	Queue_Dispose(queue, NULL);
}

/// <summary>���������� ���������, ���������� �� �������� ��������� �� �������� ������������</summary>
/// <param name="lowerBound">- ��� ��������� ������ - �� ������ ����������� ���������� �������� ���������</param>
/// <param name="upperBound">- ��� ��������� ������ - �� ������ ����������� ���������� �������� ���������</param>
/// <param name="compare">- ������� ��������� ���������� ���������</param>
bool Subtree_ISBinarySearchTree(TreeNode* root, void* lowerBound, void* upperBound, int (*compare)(const void*,const void*)) {
	if (root == NULL) return true;

	if (compare(root->value, lowerBound) == 1) return false;
	if (compare(upperBound, root->value) > -1) return false;

	return
		Subtree_ISBinarySearchTree(root->left, lowerBound, root->value, compare) &&
		Subtree_ISBinarySearchTree(root->right, root->value, upperBound, compare);
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


/// <summary>����� ������ � "��������� �����"</summary>
/// <param name="printValueMethod">- ����� ������ �������� ����������� ��������</param>
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
/// <param name="printValueMethod">- ����� ������ �������� ����������� ��������</param>
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


// - - - - - - - - - - - - - - - -
//   B I N A R Y  T R E E


/// <summary>������������ ������ � ���� ������ �� ����</summary>
/// <param name="accessCode">- ������-��� ������� - ���������������� �������� �� ������: 0 - ������, 1 - �������</param>
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

bool Tree_IsBinarySearchTree_Int(Tree* obj) {
	if (obj == NULL) return true;
	int min = INT_MIN, max = INT_MAX;
	return Subtree_ISBinarySearchTree(obj->root, &min, &max, compare_int_asc);
}

void Tree_Dispose(Tree* obj) {
	if (obj->root) Subtree_Dispose(obj->root);
	free(obj);
}


// - - - - - - - - - - - - - - - -
//   B I N A R Y  S E A R C H  T R E E


int BST_Insert(Tree* obj, const void* newValue, int(*compare)(const void*, const void*)) {
	if (obj == NULL) return 1;
	TreeNode* temp = BSSubtree_Add(obj->root, newValue, obj->valSize, compare);
	if (temp == NULL) return 1;
	else obj->root = temp;
	return 0;
}

/// <summary>��������� ������� � ����� ������ �� ������ ������, �� ��������� ���������������� ������</summary>
/// <param name="compare">- ��������� �������� ���������� ���������</param>
/// <returns>������ ������</returns>
TreeNode* BSSubtree_Add(TreeNode* root, const void* newValue, size_t valSize, int(*compare)(const void*, const void*)) {
	if (root == NULL) {
		root = NewTreeNode(newValue, valSize);
	}
	else if (compare(root->value, newValue) > 0) {
		root->right = BSSubtree_Add(root->right, newValue, valSize, compare);
	}
	else {
		root->left = BSSubtree_Add(root->left, newValue, valSize, compare);
	}
	return root;
}

/// <summary>����� �������� �� ��������</summary>
/// <param name="compare">- ��������� �������� ���������� ���������</param>
/// <returns>��������� �� ������� ������� � ������� ���������</returns>
TreeNode* BSSubtree_Search(TreeNode* root, const void* searchValue, int(*compare)(const void*,const void*)) {
	if (root) {
		switch (compare(root->value, searchValue)) {
		case 0: return root;
		case 1: return BSSubtree_Search(root->right, searchValue, compare);
		case -1: return BSSubtree_Search(root->left, searchValue, compare);
		}
	}
	return NULL;
}

/// <summary>������� ���� ��������� ������ ������ �� �������� �� ��������� ���������</summary>
/// <param name="compare">- ��������� �������� ���������� ���������</param>
/// <returns>��������� �� ��������� ����</returns>
TreeNode* BSSubtree_GetInorderSuccessor_2(TreeNode* root, const void* value, int(*compare)(const void*,const void*)) {
	TreeNode* successor = root;
	while (root) {
		switch (compare(value, root->value)) {
		case 1:
			root = root->right;
			break;
		case -1:
			successor = root;
			root = root->left;
			break;
		case 0:
			if (root->right) return BSSubtree_GetMinElement(root->right);
			else return successor;
		}
	}
	return NULL;
}
TreeNode* BSSubtree_GetInorderSuccessor_1(TreeNode* root, const void* value, int(*compare)(const void*,const void*)) {
	TreeNode* current = BSSubtree_Search(root, value, compare);
	if (current == NULL) return NULL;
	else if (current->right != NULL) return BSSubtree_GetMinElement(current->right);
	else {
		TreeNode* successor = NULL;
		TreeNode* ancestor = root;
		while (ancestor != current) {
			if (compare(current->value, ancestor->value) == -1) {
				successor = ancestor;
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}

/// <summary>������� ���������� ������ ����������� ���� ��������� �� �� ���������</summary>
/// <param name="compare">- ��������� �������� ���������� ���������</param>
/// <returns>
/// ��������� �� ����-�����������;
/// �� ���� �� ���������, ���� �� �������� ������������ �������;
/// ���� �������� ����� - ��������� �� ������� � ������ ���������;
/// NULL, ���� ���� �� ���� �������� � ������ ����������
/// </returns>
TreeNode* BSSubtree_GetClosestMutualAncestor_1(TreeNode* root, const void* one, const void* another, int(*compare)(const void*, const void*)) {
	TreeNode* ancestor = root;
	int one_LeftEqualRight, another_LeftEqualRight;
	while (root) {
		one_LeftEqualRight = compare(one, root->value);
		another_LeftEqualRight = compare(another, root->value);

		if (one_LeftEqualRight + another_LeftEqualRight == 2) root = root->right;
		else if (one_LeftEqualRight + another_LeftEqualRight == -2) root = root->left;

		else if (one_LeftEqualRight == 1 && another_LeftEqualRight == -1) {
			if (BSSubtree_Search(root->right, one, compare) &&
				BSSubtree_Search(root->left, another, compare))
				return root;
			else return NULL;
		}
		else if (one_LeftEqualRight == -1 && another_LeftEqualRight == 1) {
			if (BSSubtree_Search(root->left, one, compare) &&
				BSSubtree_Search(root->right, another, compare))
				return root;
			else return NULL;
		}

		else if (one_LeftEqualRight == 0) {
			switch (another_LeftEqualRight) {
			case -1:
				if (BSSubtree_Search(root->left, another, compare)) return root;
				else return NULL;
			case 0: return root;
			case 1:
				if (BSSubtree_Search(root->right, another, compare)) return root;
				else return NULL;
			}
		}
		else if (another_LeftEqualRight == 0) {
			switch (one_LeftEqualRight) {
			case -1:
				if (BSSubtree_Search(root->left, one, compare)) return root;
				else return NULL;
				//case 0: return root; // ������������ ������
			case 1:
				if (BSSubtree_Search(root->right, one, compare)) return root;
				else return NULL;
			}
		}
	}
	return NULL;
}
TreeNode* BSSubtree_GetClosestMutualAncestor_2(TreeNode* root, const void* one, const void* another, int(*compare)(const void*, const void*)) {
	int one_LeftEqualRight, another_LeftEqualRight;
	while (root) {
		one_LeftEqualRight = compare(one, root->value);
		another_LeftEqualRight = compare(another, root->value);

		switch (one_LeftEqualRight) {
		case -1:
			switch (another_LeftEqualRight) {
			case -1:
				root = root->left;
				break;
			case 0:
				if (BSSubtree_Search(root->left, one, compare)) return root;
				else return NULL;
			case 1:
				if (BSSubtree_Search(root->left, one, compare) &&
					BSSubtree_Search(root->right, another, compare))
					return root;
				else return NULL;
			}

		case 0:
			switch (another_LeftEqualRight) {
			case -1:
				if (BSSubtree_Search(root->left, another, compare)) return root;
				else return NULL;
			case 0:
				return root;
			case 1:
				if (BSSubtree_Search(root->right, another, compare)) return root;
				else return NULL;
			}

		case 1:
			switch (another_LeftEqualRight) {
			case -1:
				if (BSSubtree_Search(root->right, one, compare) &&
					BSSubtree_Search(root->left, another, compare))
					return root;
				else return NULL;
			case 0:
				if (BSSubtree_Search(root->right, one, compare)) return root;
				else return NULL;
			case 1:
				root = root->right;
				break;
			}
		}
	}
	return NULL;
}

/// <summary>������� ������� �� ��������</summary>
/// <param name="compare">- ��������� �������� ���������� ���������</param>
/// <returns>������ ������</returns>
TreeNode* BSSubtree_DeleteElement(TreeNode* root, const void* value, int (*compare)(const void*,const void*)) {
	if (root == NULL) return NULL;

	TreeNode *nongratus = root, *temp;
	switch (compare(value, root->value)) {
	case 1: root->right = BSSubtree_DeleteElement(root->right, value, compare); break;
	case -1: root->left = BSSubtree_DeleteElement(root->left, value, compare); break;
	case 0:
		if (root->left == NULL && root->right == NULL) root = NULL;
		else if (root->left == NULL) root = root->right;
		else if (root->right == NULL) root = root->left;
		else {
			temp = BSSubtree_GetMinElement(root->right);
			AssignValue(root->value, temp->value, root->valSize);
			root->right = BSSubtree_DeleteElement(root->right, temp->value, compare);
		}
		free(nongratus->value);
		free(nongratus);
	}
	return root;
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