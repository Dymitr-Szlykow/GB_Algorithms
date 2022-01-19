#ifndef LESSON5_H
#define LESSON5_H

#define bool int
#define true 1
#define false 0

// ЗАДАНИЯ к занятию №5.
// 1. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
// 2. Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти.
//    Если память не выделяется, то выводится соответствующее сообщение.
//    Постарайтесь создать ситуацию, когда память не будет выделяться (добавлением большого количества данных).
// 3. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.
//    Примеры правильных скобочных выражений : (), ([])(), {}(), ([{}]), неправильных — )(, ())({ ), (, ]) }), ([(]) для скобок[, (, { .
//    Например: (2 + (2 * 2)) или[2 / {5 * (4 + 7)}]
// 4. * Создать функцию, копирующую односвязный список (то есть создает в памяти копию односвязного списка, не удаляя первый список).
// 5. * *Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.
// 6. * Реализовать очередь.


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
void AssignValue(const void* to, const void* from, size_t size);                 // = O(size)
void SwapValues(const void* a, const void* b, size_t size);                      // = O(size)
bool AreEqual(const void* left, const void* right, size_t size);                 // = O(size)
void DragElement(void* arr, unsigned int from, unsigned int to, size_t elSize);  // = O(|from-to|) ~ O(n)
inline int ToInt(const void* value);                                             // = O(1)
inline char ToChar(const void* value);                                           // = O(1)

// L I S T  (D Y N A M I C  A R R A Y)
List* NewList(size_t elSize, unsigned int capacity);                           // = O(malloc(capacity * elSize))
inline void* List_AccessAt(List* obj, unsigned int atIndex);                   // = O(1)
int	  List_AddTo(List* obj, const void* newValue);                             // = O(AssignValue()) = O(obj.elSize), м.б. вызвана List_RefactorList()
inline int  List_Count(List* obj);                                             // = O(1)
inline void List_Dispose(List* obj, void(*disposeValues)(void*));              // = O(1) при структурных элементах, O(obj.count) при "ссылочных"
int   List_InsertInto(List* obj, const void* newValue, unsigned int atIndex);  // = O(List_AddTo()) + O(DragElement()) = O(obj.elSize + obj.count) ~ O(n), м.б. вызвана List_RefactorList()
inline bool List_IsEmpty(List* obj);                                           // = O(1)
int   List_RefactorList(List* obj);                                            // = O(realloc()) --> O(obj.capacity)
int   List_RemoveFrom(List* obj, unsigned int atIndex);                        // = O(DragElement()) = O(obj.count)

// L I N K A B L E  N O D E:  one-way
Node* NewNode(const void* value, size_t valSize);                  // = O(malloc(valSize)) + O(AssignValue()) --> O(valSize)
Node* NodeChain_Decapitate(Node* head);                            // = O(1)
void  NodeChain_Dipose(Node* node, void(*disposeValues)(void*));   // = O(node.tailCount)  ~ O(n)
void  NodeChain_DiposeTail(Node* node);                            // = O(node.tailCount)  ~ O(n)
Node* NodeChain_GetLastInLine(Node* node);                         // = O(node.tailCount)  ~ O(n)
int   NodeChain_InsertAsNext(Node* obj, Node* newNode);	           // = O(obj.tailCount)   ~ O(n)
Node* NodeChain_Reverse(Node* head);                               // = O(head.tailCount)  ~ O(n)
int   Node_InsertAsPrev(Node* obj, Node* newNode);                 // = O(obj.valSize)     ~ O(n)

// L I N K E D  L I S T
LinkedList* NewLinkedList(size_t valSize);                                         // = O(1)
LinkedList* CopyLinkedList(LinkedList* source);                                    // = O(source.count)
Node* LinkedList_Access(LinkedList* list, unsigned int atIndex);                   // = O(list.count)
int   LinkedList_AddNode(LinkedList* list, const void* value);                     // = O(LinkedList_AttachChain()) = O(list.count)
int   LinkedList_AttachChain(LinkedList* list, Node* node);                        // = O(NodeChain_GetLastInLine()) = O(list.count)
int   LinkedList_DeleteNode(LinkedList* list, unsigned int atIndex);               // = O(LinkedList_Access()) + O(NodeChain_Decapitate()) = O(list.count + 1) = O(list.count)
void  LinkedList_Dispose(LinkedList* list, void(*disposeValues)(void*));           // = O(NodeChain_Dipose()) = O(list.count)
Node* LinkedList_ExcludeNode(LinkedList* list, unsigned int atIndex);              // = O(LinkedList_Access()) = O(list.count)
int   LinkedList_InsertChain(LinkedList* list, Node* node, unsigned int atIndex);  // = O(LinkedList_Access) + O(NodeChain_InsertAsNext()) = O(list.count + node.tailCount)  ~ O(n)

// S T A C K
Stack* NewStack(size_t valSize);                               // = O(1)
void  Stack_Dispose(Stack* obj, void(*disposeValues)(void*));  // = O(NodeChain_Dipose()) = O(obj.count)
bool  Stack_Has(Stack* obj, const void* value);                // = O(obj.count) * O(AreEqual()) = O(obj.count * obj.valSize)  -> O(obj.count)
inline bool  Stack_IsEmpty(Stack* obj);                        // = O(1)
inline void* Stack_Peek(Stack* obj);                           // = O(1)
int   Stack_Pop(Stack* obj, void* targetVariable);             // = O(AssignValue()) + O(NodeChain_Decapitate()) = O(obj.valSize + 1) = O(obj.valSize)
int   Stack_Push(Stack* obj, const void* value);               // = O(AssignValue()) = O(obj.valSize)

// Q U E U E
Queue* NewQueue(size_t valSize);                               // = O(1)
int   Queue_Dequeue(Queue* obj, void* targetVariable);         // = O(AssignValue()) + O(NodeChain_Decapitate()) = O(obj.valSize + 1) = O(obj.valSize)
void  Queue_Dispose(Queue* obj, void(*disposeValues)(void*));  // = O(NodeChain_Dipose()) = O(obj.count)
int   Queue_Enqueue(Queue* obj, const void* newValue);         // = O(AssignValue()) = O(obj.valSize)
bool  Queue_Has(Queue* obj, const void* value);                // = O(obj.count) * O(AreEqual()) = O(obj.count * obj.valSize)  --> O(obj.count)
inline bool  Queue_IsEmpty(Queue* obj);                        // = O(1)
inline void* Queue_Peek(Queue* obj);                           // = O(1)

// Q U E U E  (v i a  a r r a y)
QueueArr* NewQueueArr(size_t elSize, unsigned int capacity);   // = O(malloc(capacity * elSize))
inline int   QueueArr_Count(QueueArr* obj);                    // = O(1)
int  QueueArr_Dequeue(QueueArr* obj, void* targetVariable);    // = O(AssignValue()) = O(obj.elSize)
inline void  QueueArr_Dispose(QueueArr* obj);                  // = O(1)
int  QueueArr_Enqueue(QueueArr* obj, const void* newValue);    // = O(AssignValue()) = O(obj.elSize), м.б. вызвана QueueArr_RefactorArray()
bool QueueArr_Has(QueueArr* obj, const void* value);           // = O(obj.count) * O(AreEqual()) = O(obj.count * obj.elSize) --> O(obj.count)
inline bool  QueueArr_IsEmpty(QueueArr* obj);                  // = O(1)
inline void* QueueArr_Peek(QueueArr* obj);                     // = O(1)
int  QueueArr_RefactorArray(QueueArr* obj);                    // = O(obj.capacity) * O(AssignValue()) = O(obj.capacity * obj.elSize) --> O(obj.capacity)

#endif