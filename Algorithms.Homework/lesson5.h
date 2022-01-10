#pragma once

#define bool int
#define true 1
#define false 0


typedef struct list {
	void* arr;
	int capacity, last;
	size_t elSize;
} List;

typedef struct node {
	void* value;
	size_t valSize;
	struct node* next;
} Node;

typedef struct linkedList {
	struct node* head;
	size_t valSize;
	//int count;
} LinkedList;

typedef struct stack {
	struct node* TopOfStack;
	size_t valSize;
	int count;
} Stack;

typedef struct queue {
	struct node* front;
	struct node* rear;
	size_t valSize;
	int count;
} Queue;

typedef struct queueArr {
	void* arr;
	int capacity, front, rear;
	size_t elSize;
} QueueArr;


void Task_5_1(void);
void Print_AsBinary_stack(int number);
void PrintFromCharStack(Stack* obj);

void Task_5_3(void);
bool BracersSequenceIsOK(char* string);
bool CompareStack(Stack* stack, char c);

void Task_5_4(void);
LinkedList* InitNewLinkedList(size_t valSize, unsigned int count);
void PrintNodeChain(Node* head);

void Task_5_5(void);
int Print_PostfixNotation(char* expression);
int PrintPostfix_ProcessSubstring_Recursive(char* position);
int PrintPostfix_UnloadStack(Stack* stack);
void PrintPostfix_UnloadUntilLowPrecedence(Stack* stack);

//void Task_5_6(void);
void test_QueueLinked(void);
void test_QueueArray(void);
void PrintQueueArray(QueueArr* obj);

void test_DynamicList(void);
void PrintDynamicList(List* list);


// g e n e r i c  e l e m e n t s
void AssignValue(const void* to, const void* from, size_t size);
void SwapValues(const void* a, const void* b, size_t size);
bool AreEqual(const void* left, const void* right, size_t size);
void DragElement(void* arr, unsigned int from, unsigned int to, size_t elSize);
int ToInt(void* value);
char ToChar(void* value);

// L I S T  (D Y N A M I C  A R R A Y)
List* NewList(size_t elSize, unsigned int capacity);
void* List_AccessAt(List* obj, unsigned int atIndex);
int   List_AddTo(List* obj, const void* newValue);
int   List_Count(List* obj);
void  List_Dispose(List* obj);
int   List_InsertInto(List* obj, const void* newValue, unsigned int atIndex);
bool  List_IsEmpty(List* obj);
int   List_RefactorList(List* obj);
int   List_RemoveFrom(List* obj, unsigned int atIndex);

// L I N K A B L E  N O D E:  one-way
Node* NewNode(const void* value, size_t valSize);
Node* NodeChain_Decapitate(Node* head);
void  NodeChain_Dipose(Node* node);
void  NodeChain_DiposeTail(Node* node);
Node* NodeChain_GetLastInLine(Node* node);
int   NodeChain_InsertAsNext(Node* obj, Node* newNode);
Node* NodeChain_Reverse(Node* head);
int   Node_InsertAsPrev(Node* obj, Node* newNode);

// L I N K E D  L I S T
LinkedList* NewLinkedList(size_t valSize);
LinkedList* CopyLinkedList(LinkedList* source);
Node* LinkedList_Access(LinkedList* list, unsigned int atIndex);
int   LinkedList_AddNode(LinkedList* list, const void* value);
int   LinkedList_AttachChain(LinkedList* list, Node* node);
int   LinkedList_DeleteNode(LinkedList* list, unsigned int atIndex);
void  LinkedList_Dispose(LinkedList* list);
Node* LinkedList_ExcludeNode(LinkedList* list, unsigned int atIndex);
int   LinkedList_InsertChain(LinkedList* list, Node* node, unsigned int atIndex);

// S T A C K
Stack* NewStack(size_t valSize);
void  Stack_Dispose(Stack* obj);
bool  Stack_Has(Stack* obj, const void* value);
bool  Stack_IsEmpty(Stack* obj);
void* Stack_Peek(Stack* obj);
int   Stack_Pop(Stack* obj, void* targetVariable);
int   Stack_Push(Stack* obj, const void* value);

// Q U E U E
Queue* NewQueue(size_t valSize);
int   Queue_Dequeue(Queue* obj, void* targetVariable);
void  Queue_Dispose(Queue* obj);
int   Queue_Enqueue(Queue* obj, const void* newValue);
bool  Queue_Has(Queue* obj, const void* value);
bool  Queue_IsEmpty(Queue* obj);
void* Queue_Peek(Queue* obj);

// Q U E U E  (v i a  a r r a y)
QueueArr* NewQueueArr(size_t elSize, unsigned int capacity);
int   QueueArr_Count(QueueArr* obj);
int   QueueArr_Dequeue(QueueArr* obj, void* targetVariable);
void  QueueArr_Dispose(QueueArr* obj);
int   QueueArr_Enqueue(QueueArr* obj, const void* newValue);
bool  QueueArr_Has(QueueArr* obj, const void* value);
bool  QueueArr_IsEmpty(QueueArr* obj);
void* QueueArr_Peek(QueueArr* obj);
int   QueueArr_RefactorArray(QueueArr* obj);