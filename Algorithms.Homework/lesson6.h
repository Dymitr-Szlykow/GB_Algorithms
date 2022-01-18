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
TreeNode* NewTreeNode(const void* value, size_t valSize);                   // = O(malloc(valSize)) + O(AssignValue()) --> O(valSize)
int Subtree_GetTreeHeight(TreeNode* root);                                  // = O(root.count)
void Subtree_TraversalPreorder(TreeNode* root, void (*action)(void*));      // по времени = O(root.count) * O(action()) ; по памяти = O(root.height)
void Subtree_TraversalInorder(TreeNode* root, void (*action)(void*));       // по времени = O(root.count) * O(action()) ; по памяти = O(root.height)
void Subtree_TraversalPostorder(TreeNode* root, void (*action)(void*));     // по времени = O(root.count) * O(action()) ; по памяти = O(root.height)
void Subtree_TraversalLevelorder(TreeNode* root, void (*action)(void*));    // по времени = O(root.count) * O(action()) ; по памяти = O(root.count/2) = O(root.count)
bool Subtree_ISBinarySearchTree(TreeNode* root, void* lowerBound, void* upperBound, int (*compare)(const void*, const void*));
  // по времени = O(root.count) * O(compare()) ; по памяти = O(root.height)
void Subtree_DisposeBranches(TreeNode* node);                               // = O(node.descendants.count)
void Subtree_Dispose(TreeNode* node);                                       // = O(node.descendants.count)

void Subtree_PrintParenthesesForm(TreeNode* obj, void (*printValueMethod)(const void*));
void Subtree_WriteParenthesesForm(TreeNode* obj, int (*writeValueMethod)(const void*, char*), char** targetString); // broken
TreeNode* Subtree_ReadParenthesesForm(char* sourceString, void (*readValueMethod)(const void*)); // TODO

// B I N A R Y  T R E E
TreeNode* Tree_AccessNode(Tree* tree, char* accessCode);
void Tree_Dispose(Tree* obj);
bool Tree_IsBinarySearchTree_Int(Tree* obj); // = O(Subtree_ISBinarySearchTree())

// B I N A R Y  S E A R C H  T R E E
int BST_Insert(Tree* obj, const void* newValue, int(*compareMethod)(const void*, const void*));
TreeNode* BSSubtree_Add(TreeNode* root, const void* newValue, size_t valSize, int(*compare)(const void*, const void*));
TreeNode* BSSubtree_DeleteElement(TreeNode* root, const void* value, int (*compare)(const void*, const void*));
TreeNode* BSSubtree_GetClosestMutualAncestor_1(TreeNode* root, const void* one, const void* another, int(*compare)(const void*, const void*)); // = O(2 * root.height) = O(root.height)
TreeNode* BSSubtree_GetClosestMutualAncestor_2(TreeNode* root, const void* one, const void* another, int(*compare)(const void*, const void*)); //  -//-
TreeNode* BSSubtree_GetInorderSuccessor_1(TreeNode* root, const void* value, int(*compare)(const void*, const void*));
TreeNode* BSSubtree_GetInorderSuccessor_2(TreeNode* root, const void* value, int(*compare)(const void*, const void*));
TreeNode* BSSubtree_GetMinElement(TreeNode* root); // = O(root.height)
TreeNode* BSSubtree_GetMaxElement(TreeNode* root); // = O(root.height)
TreeNode* BSSubtree_Search(TreeNode* root, const void* searchValue, int(*compare)(const void*, const void*));

#endif