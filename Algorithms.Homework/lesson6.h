#pragma once

#define bool int
#define true 1
#define false 0


typedef struct treeNode {
	void* value;
	size_t valSize;
	struct treeNode* left;
	struct treeNode* right;
	struct treeNode* parent;
} TreeNode;

typedef struct tree {
	struct treeNode* root;
	size_t val_size;
} Tree;


void Task_6_1(void);

void Task_6_2(void);

void Task_6_3(void);


// g e n e r i c  e l e m e n t s
void PrintValue_ToInt(const void* value);
void WriteIntValue(const void* value, char* targetString);

// T R E E  N O D E
TreeNode* NewTreeNode(const void* value, size_t valSize);
void Subtree_PrintParentheses(TreeNode* obj, void (*printValueMethod)(const void*));
void Subtree_WriteParenthesesForm(TreeNode* obj, void (*writeValueMethod)(const void*, char*), char** targetString);
TreeNode* Subtree_ReadParenthesesForm(char* sourceString, void (*readValueMethod)(const void*));