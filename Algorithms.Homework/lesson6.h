#ifndef LESSON6_H
#define LESSON6_H

#define bool int
#define true 1
#define false 0

// ЗАДАНИЯ к занятию №6.
// 1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
// 2. Переписать программу, реализующую двоичное дерево поиска.
//    а) Добавить в него обход дерева различными способами;
//    б) Реализовать поиск в двоичном дереве поиска;
//    в)* Добавить в программу обработку командной строки, с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.
// 3. * Разработать базу данных студентов из полей «Имя», «Возраст», «Табельный номер», в которой использовать все знания, полученные на уроках.
//    Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных (возраст, вес).


typedef struct treeNode {
	void* value;
	size_t valSize;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	struct treeNode* root;
	size_t valSize;
} Tree;


void Task_6_1(void);

void Task_6_2(void);

void Task_6_3(void);


// g e n e r i c  e l e m e n t s
inline void PrintValue_ToInt(const void* value);
inline int WriteIntValue(const void* value, char* targetString);

// T R E E  N O D E
TreeNode* NewTreeNode(const void* value, size_t valSize);
int Subtree_GetTreeHeight(TreeNode* root); // ~ O(root.count)
void Subtree_TraversalPreorder(TreeNode* root, void (*action)(void*)); // ~ O(root.count * O(action()))
void Subtree_TraversalInorder(TreeNode* root, void (*action)(void*)); // ~ O(root.count * O(action()))
void Subtree_TraversalPostorder(TreeNode* root, void (*action)(void*)); // ~ O(root.count * O(action()))
void Subtree_TraversalLevelorder(TreeNode* root, void (*action)(void*)); // по времени ~ O(root.count * O(action())) ; по памяти ~ O(root.count) <- O(root.count/2)
void Subtree_PrintParenthesesForm(TreeNode* obj, void (*printValueMethod)(const void*));
void Subtree_WriteParenthesesForm(TreeNode* obj, int (*writeValueMethod)(const void*, char*), char** targetString); // broken
TreeNode* Subtree_ReadParenthesesForm(char* sourceString, void (*readValueMethod)(const void*)); // TODO
void Subtree_DisposeBranches(TreeNode* node);
void Subtree_Dispose(TreeNode* node);

// B I N A R Y  T R E E
TreeNode* Tree_AccessNode(Tree* tree, char* accessCode);

// B I N A R Y  S E A R C H  T R E E
int BST_Insert(Tree* obj, const void* newValue, int(*compareMethod)(const void*, const void*));
TreeNode* BSSubtree_Add(TreeNode* root, const void* newValue, size_t valSize, int(*compareMethod)(const void*, const void*));
TreeNode* BST_Search(TreeNode* root, const void* searchValue, int(*compareMethod)(const void*, const void*));
TreeNode* BSSubtree_GetMinElement(TreeNode* root);
TreeNode* BSSubtree_GetMaxElement(TreeNode* root);

#endif