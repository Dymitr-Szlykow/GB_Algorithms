#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define bool int
#define true 1
#define false 0


typedef struct node Node;
typedef struct list List;
typedef struct linkedList LinkedList;
typedef struct stack Stack;

inline void Task_5_1(void);
inline void Print_AsBinary_stack(int number);
inline void PrintFromCharStack(Stack* obj);

inline void Task_5_3(void);
inline bool BracersSequenceIsOK(char* string);
inline bool CompareStack(Stack* stack, char c);

inline void Task_5_4(void);
inline LinkedList* InitNewLinkedList(size_t valSize, unsigned int count);
inline void PrintNodeChain(Node* head);

inline void Task_5_5(void);
inline void Task_5_6(void);

inline void test_DynamicList(void);
inline void PrintDynamicList(List* list);

// g e n e r i c  e l e m e n t s
inline void AssignValue(const void* to, const void* from, size_t size);
inline void SwapValues(const void* a, const void* b, size_t size);
inline void DragElement(void* arr, unsigned int from, unsigned int to, size_t elSize);
inline int ToInt(void* value);
inline char ToChar(void* value);
// L I S T  (D Y N A M I C  A R R A Y)
inline List* NewList(size_t elSize, unsigned int capacity);
inline void* List_AccessAt(List* obj, unsigned int atIndex);
inline int   List_AddTo(List* obj, const void* newValue);
inline int   List_Count(List* obj);
inline void  List_Dispose(List* obj);
inline int   List_InsertInto(List* obj, const void* newValue, unsigned int atIndex);
inline bool  List_IsEmpty(List* obj);
inline int   List_RefactorList(List* obj);
inline int   List_RemoveFrom(List* obj, unsigned int atIndex);
// L I N K A B L E  N O D E:  one-way
inline Node* NewNode(const void* value, size_t valSize);
inline Node* NodeChain_Decapitate(Node* head);
inline void  NodeChain_Dipose(Node* node);
inline void  NodeChain_DiposeTail(Node* node);
inline Node* NodeChain_GetLastInLine(Node* node);
inline int   NodeChain_InsertAsNext(Node* this, Node* newNode);
inline Node* NodeChain_Reverse(Node* head);
inline int   Node_InsertAsPrev(Node* this, Node* newNode);
// L I N K E D  L I S T
inline LinkedList* NewLinkedList(size_t valSize);
inline LinkedList* CopyLinkedList(LinkedList* source);
inline Node* LinkedList_Access(LinkedList* list, unsigned int atIndex);
inline int   LinkedList_AddNode(LinkedList* list, const void* value);
inline int   LinkedList_AttachChain(LinkedList* list, Node* node);
inline int   LinkedList_DeleteNode(LinkedList* list, unsigned int atIndex);
inline void  LinkedList_Dispose(LinkedList* list);
inline Node* LinkedList_ExcludeNode(LinkedList* list, unsigned int atIndex);
inline int   LinkedList_InsertChain(LinkedList* list, Node* node, unsigned int atIndex);
// S T A C K
inline Stack* NewStack(size_t valSize);
inline void  Stack_Dispose(Stack* obj);
inline bool  Stack_IsEmpty(Stack* obj);
inline void* Stack_Peek(Stack* obj);
inline void  Stack_Pop(Stack* obj, void* targetVariable);
inline void  Stack_Push(Stack* obj, const void* value);


struct list {
	void* arr;
	int capacity, last;
	size_t elSize;
};

struct node {
	void* value;
	size_t valSize;
	struct node* next;
};

struct linkedList {
	struct node* head;
	size_t valSize;
	//int count;
};

struct stack {
	struct node* TopOfStack;
	size_t valSize;
};

// ������� � ������� �5.
// 1. ����������� ������� �� ���������� � �������� ������� ��������� � �������������� �����.
// 2. �������� � ��������� ����������� ����� �� ������ ������������ ������ �������� �� ��������� ������.
//    ���� ������ �� ����������, �� ��������� ��������������� ���������.
//    ������������ ������� ��������, ����� ������ �� ����� ���������� (����������� �������� ���������� ������).
// 3. �������� ���������, ������� ����������, �������� �� ��������� ��������� ������������������ ����������.
//    ������� ���������� ��������� ��������� : (), ([])(), {}(), ([{}]), ������������ � )(, ())({ ), (, ]) }), ([(]) ��� ������[, (, { .
//    ��������: (2 + (2 * 2)) ���[2 / {5 * (4 + 7)}]
// 4. * ������� �������, ���������� ����������� ������ (�� ���� ������� � ������ ����� ������������ ������, �� ������ ������ ������).
// 5. * *����������� �������� �������� �� ��������� ������ ��������������� ��������� � �����������.
// 6. * ����������� �������.


/// <summary>
/// 1. ����������� ������� �� ���������� � �������� ������� ��������� � �������������� �����.
/// </summary>
void Task_5_1(void) {
	int number;
	printf("������� �����: ");
	scanf("%d", &number);

	Print_AsBinary_stack(number);
}

void Print_AsBinary_stack(int number) {
	if (number < 0) {
		printf("-");
		number *= -1;
	}

	Stack* stack = NewStack(sizeof(char));
	char temp;

	while (number > 0) {
		if (number % 2 == 0) {
			temp = '0';
			number /= 2;
		}
		else {
			temp = '1';
			number = (number - 1) / 2;
		}
		Stack_Push(stack, &temp);
	}
	if (number == 0 && stack->TopOfStack == NULL) {
		temp = '0';
		Stack_Push(stack, &temp);
	}

	PrintFromCharStack(stack);
	printf("\n");

	Stack_Dispose(stack);
}

void PrintFromCharStack(Stack* obj) {
	int c;
	while (obj->TopOfStack != NULL) {
		Stack_Pop(obj, &c);
		printf("%c", c);
	}
}


/// <summary>
/// 3. �������� ���������, ������� ����������, �������� �� ��������� ��������� ������������������ ����������.
/// </summary>
void Task_5_3(void) {
	char
		* str1 = "())({)",
		* str2 = "([(])",
		* str3 = "[2/{5*(4+7)}]";
	char input[64];
	printf("������������������ ������.\n");
	printf("� ��������� \"%s\" - %s���������.\n", str1, BracersSequenceIsOK(str1) ? "" : "�� ");
	printf("� ��������� \"%s\" - %s���������.\n", str2, BracersSequenceIsOK(str2) ? "" : "�� ");
	printf("� ��������� \"%s\" - %s���������.\n", str3, BracersSequenceIsOK(str3) ? "" : "�� ");

	printf("\n������� ���������:  ");
	fgets(input, 64, stdin);
	printf("������������������ ������ %s���������.\n", BracersSequenceIsOK(input) ? "" : "�� ");
}

bool BracersSequenceIsOK(char* string) {
	Stack* stack = NewStack(sizeof(char));
	char c;
	bool meanwhile = true;

	while (*string != '\0' && meanwhile == true) {
		switch (*string) {
		case '(': Stack_Push(stack, string); break;
		case '[': Stack_Push(stack, string); break;
		case '{': Stack_Push(stack, string); break;
		case ')': meanwhile = CompareStack(stack, '('); break;
		case ']': meanwhile = CompareStack(stack, '['); break;
		case '}': meanwhile = CompareStack(stack, '{'); break;
		}
		string++;
	}
	if (!Stack_IsEmpty(stack)) meanwhile = false;

	Stack_Dispose(stack);
	return meanwhile;
}

bool CompareStack(Stack* stack, char c) {
	char top;
	if (Stack_IsEmpty(stack)) return false;
	else {
		Stack_Pop(stack, &top);
		if (top != c) return false;
	}
	return true;
}


/// <summary>
/// 4. * ������� �������, ���������� ����������� ������ (�� ���� ������� � ������ ����� ������������ ������, �� ������ ������ ������).
/// </summary>
void Task_5_4(void) {
	LinkedList* list1 = InitNewLinkedList(sizeof(int), 9);
	printf("�������� ������:  ");
	PrintNodeChain(list1->head);
	printf("\n");

	LinkedList* list2 = CopyLinkedList(list1);
	printf("����� ������:     ");
	PrintNodeChain(list2->head);
	printf("\n\n");

	if (LinkedList_DeleteNode(list2, 4)) printf("�� ���� ������� �� ������� 4:\t");
	else printf("������ �� ������� 4:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	if (LinkedList_DeleteNode(list2, 6)) printf("�� ���� ������� �� ������� 6:\t");
	else printf("������ �� ������� 6:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	if (LinkedList_DeleteNode(list2, 10)) printf("�� ���� ������� �� ������� 10:\t");
	else printf("������ �� ������� 10:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	if (LinkedList_DeleteNode(list2, 0)) printf("�� ���� ������� �� ������� 0:\t");
	else printf("������ �� ������� 0:\t\t");
	PrintNodeChain(list2->head);
	printf("\n\n");

	Node* out = LinkedList_ExcludeNode(list2, 3);
	printf("����[3]: %d\n", ToInt(out->value));

	NodeChain_Dipose(out);
	out = LinkedList_ExcludeNode(list2, 10);

	printf("�������� ������:  ");
	PrintNodeChain(list1->head);
	printf("\n");

	if (out) NodeChain_Dipose(out);
	LinkedList_Dispose(list1);
	LinkedList_Dispose(list2);
}

LinkedList* InitNewLinkedList(size_t valSize, unsigned int count) {
	LinkedList* res = NewLinkedList(sizeof(int));
	int i, newValue = 0;
	for (i = 0; i < count; i++) {
		newValue += 2 * i;
		LinkedList_AddNode(res, &newValue);
	}
	return res;
}

void PrintNodeChain(Node* head) {
	while (head != NULL) {
		printf("%d ", ToInt(head->value));
		head = head->next;
	}
}


/// <summary>
/// 5. **����������� �������� �������� �� ��������� ������ ��������������� ��������� � �����������.
/// </summary>
void Task_5_5(void) {
	//
}


/// <summary>
/// 6. * ����������� �������.
/// </summary>
void Task_5_6(void) {
	//
}


/// <summary>
/// ����: ������ (������������ ������)
/// </summary>
void test_DynamicList(void) {
	List* list = NewList(sizeof(int), 5);
	int i, newValue;

	printf("�������� ������ %s\n", List_IsEmpty(list) ? "����" : "������ �� ���� ������, ��-�...");

	printf("���������� ���������:\n");
	for (i = 0; i < 9; i++) {
		newValue = i * 2 + 1;
		List_AddTo(list, &newValue);
		PrintDynamicList(list);
	}

	printf("�������� ��������:\n");
	List_RemoveFrom(list, 5);
	PrintDynamicList(list);

	printf("������� ��������:\n");
	newValue = 42;
	List_InsertInto(list, &newValue, 3);
	PrintDynamicList(list);
	
	List_Dispose(list);
}

void PrintDynamicList(List* obj) {
	if (obj != NULL) {
		int i;
		printf("    ��-��� %2d/%2d, ��������� %2d\t", List_Count(obj), obj->capacity, obj->last);
		for (i = 0; i <= obj->last; i++) {
			printf("%d ", ToInt(List_AccessAt(obj, i)));
		}
		printf("\n");
	}
}


// - - - - - - - - - - - - - - - -
//   g e n e r i c  e l e m e n t s


/// <summary>���������� ������������</summary>
void AssignValue(const void* to, const void* from, size_t size) {
	int chunk;
	if (size % sizeof(double) == 0) {
		size /= sizeof(double);
		for (chunk = 0; chunk < size; chunk++) {
			*((double*)to + chunk) = *((double*)from + chunk);
		}
	}
	else if (size % sizeof(int) == 0) {
		size /= sizeof(int);
		for (chunk = 0; chunk < size; chunk++) {
			*((int*)to + chunk) = *((int*)from + chunk);
		}
	}
	else {
		for (chunk = 0; chunk < size; chunk++) {
			*((char*)to + chunk) = *((char*)from + chunk);
		}
	}
}

/// <summary>���������� ����� ��������</summary>
void SwapValues(const void* a, const void* b, size_t size) {
	int chunk;
	if (size % sizeof(int) == 0) {
		size /= sizeof(int);
		for (chunk = 0; chunk < size; chunk++) {
			*((int*)a + chunk) ^= *((int*)b + chunk);
			*((int*)b + chunk) ^= *((int*)a + chunk);
			*((int*)a + chunk) ^= *((int*)b + chunk);
		}
	}
	else {
		for (chunk = 0; chunk < size; chunk++) {
			*((char*)a + chunk) ^= *((char*)b + chunk);
			*((char*)b + chunk) ^= *((char*)a + chunk);
			*((char*)a + chunk) ^= *((char*)b + chunk);
		}
	}
}

/// <summary>���������� ������� �� �������</summary>
void DragElement(void* arr, unsigned int from, unsigned int to, size_t elSize) {
	int i;
	if (from > to) {
		for (i = from; i > to; i--) {
			SwapValues((char*)(arr)+(i - 1) * elSize, (char*)(arr)+i * elSize, elSize);
		}
	}
	else if (from < to) {
		for (i = from; i < to; i++) {
			SwapValues((char*)(arr)+i * elSize, (char*)(arr)+(i + 1) * elSize, elSize);
		}
	}
}

/// <summary>������ �������� ��� int</summary>
int ToInt(void* value) {
	return *((int*)value);
}

/// <summary>������ �������� ��� char</summary>
char ToChar(void* value) {
	return *((char*)value);
}


// - - - - - - - - - - - - - - - -
//   L I N K A B L E  N O D E:  one-way


/// <summary>������� ����������� ���� � ������������ ������</summary>
Node* NewNode(const void* value, size_t valSize) {
	Node* res = (Node*)malloc(sizeof(Node));
	if (res != NULL) {
		res->valSize = valSize;
		res->value = malloc(valSize);
		AssignValue(res->value, value, valSize);
		res->next = NULL;
	}
	return res;
}

/// <summary>�������� �� ������� ����� �� ����������</summary>
/// <returns>��������� �� ��������� ���� � �������</returns>
Node* NodeChain_GetLastInLine(Node* node) {
	while (node->next != NULL) {
		node = node->next;
	}
	return node;
}

/// <summary>��������� ������ ���� � ��� ����� � ������, ����� ������� ����������� � ������� �������</summary>
int NodeChain_InsertAsNext(Node* this, Node* newNode) {
	if (this->valSize != newNode->valSize) return 1;
	if (this->next != NULL) (NodeChain_GetLastInLine(newNode))->next = this->next;
	this->next = newNode;
	return 0;
}

/// <summary>���������� ������� "�����"</summary>
/// <param name="newNode">���� ��� ������</param>
int Node_InsertAsPrev(Node* this, Node* newNode) {
	if (newNode->next != NULL || this->valSize != newNode->valSize) return 1;

	if (this->next != NULL) newNode->next = this->next;
	this->next = newNode;
	SwapValues(this->value, newNode->value, this->valSize);
	return 0;
}

/// <summary>������������� ������� ������� �����</summary>
/// <returns>������ ��������� ���� �������</returns>
Node* NodeChain_Reverse(Node* head) {
	if (head == NULL || head->next == NULL) return head;

	Node* newHead = NodeChain_Reverse(head->next);
	(head->next)->next = head;
	head->next = NULL;
	return newHead;
}

/// <summary>������������ ������ ��������������� ���� �������</summary>
/// <returns>��������� �� ����, ��������� �� ������ �������������</returns>
Node* NodeChain_Decapitate(Node* head) {
	Node* res = head->next;
	free(head->value);
	free(head);
	return res;
}

/// <summary>������������ ������ ���� ��������� �����</summary>
void NodeChain_DiposeTail(Node* node) {
	if (node->next) {
		NodeChain_DiposeTail(node->next);
		free(node->next->value);
		free(node->next);
	}
}

/// <summary>������������ ������ ���� ��������� � �������� ����</summary>
void NodeChain_Dipose(Node* node) {
	NodeChain_DiposeTail(node);
	free(node->value);
	free(node);
}


// - - - - - - - - - - - - - - - -
//   L I N K E D  L I S T


/// <summary>������� ������� ������ � ������������ ������</summary>
LinkedList* NewLinkedList(size_t valSize) {
	LinkedList* res = (LinkedList*)malloc(sizeof(LinkedList));
	if (res != NULL) {
		res->head = NULL;
		//res->count = 0;
		res->valSize = valSize;
	}
	return res;
}

/// <summary>������� � ���� ����� ���������� �������� ������</summary>
/// <returns>��������� �� ����� ������ � ������������ ������</returns>
LinkedList* CopyLinkedList(LinkedList* source) {
	LinkedList* res = NewLinkedList(source->valSize);
	Node* sourceNode = source->head;
	Node** position = &(res->head);

	while (sourceNode != NULL) {
		*position = NewNode(sourceNode->value, sourceNode->valSize);
		position = &((*position)->next);
		sourceNode = sourceNode->next;
	}
	return res;
}

/// <summary>������������ ������ � �-��� ���� �������� ������</summary>
/// <returns>��������� �� ������� ����</returns>
Node* LinkedList_Access(LinkedList* list, unsigned int atIndex) {
	Node* res;
	if (list->head == NULL) return res = NULL;

	int i;
	for (i = 0, res = list->head; i < atIndex; i++) {
		if (res->next == NULL) return res = NULL;
		else res = res->next;
	}
	return res;
}

/// <summary>������� ����� ���� � ��������� ��������� � ����� �������� ������</summary>
int LinkedList_AddNode(LinkedList* list, const void* value) {
	Node* newNode = NewNode(value, list->valSize);
	if (newNode == NULL) return 1;
	if (LinkedList_AttachChain(list, newNode)) return 1;
	return 0;
}

/// <summary>������������ ��������� ���� � ����� �������� ������</summary>
int LinkedList_AttachChain(LinkedList* list, Node* node) {
	if (node->valSize != list->valSize) return 1;

	if (list->head == NULL) list->head = node;
	else (NodeChain_GetLastInLine(list->head))->next = node;
	return 0;
}

/// <summary>��������� ������� ����� � ��������� ���������</summary>
int LinkedList_InsertChain(LinkedList* list, Node* node, unsigned int atIndex) {
	if (node->valSize != list->valSize) return 1;

	if (atIndex == 0) {
		if (list->head == NULL) list->head = node;
		else {
			(NodeChain_GetLastInLine(node))->next = list->head;
			list->head = node;
		}
	}
	else {
		Node* previous = LinkedList_Access(list, atIndex - 1);
		if (previous == NULL) return 1;
		else if (NodeChain_InsertAsNext(previous, node)) return 1;
	}
	return 0;
}

/// <summary>��������� ���� �� ��������� �������</summary>
/// <returns>��������� �� ����������� ����</returns>
Node* LinkedList_ExcludeNode(LinkedList* list, unsigned int atIndex) {
	Node *res = NULL, *prev = LinkedList_Access(list, atIndex - 1);
	if (prev != NULL) {
		res = prev->next;
		prev->next = res->next;
		res->next = NULL;
	}
	return res;
}

/// <summary>������� ��������� ����, ������������ ��� ������</summary>
int LinkedList_DeleteNode(LinkedList* list, unsigned int atIndex) {
	if (atIndex == 0) list->head = NodeChain_Decapitate(list->head);

	else {
		Node* prev = LinkedList_Access(list, atIndex - 1);
		if (prev == NULL) return 1;
		else prev->next = NodeChain_Decapitate(prev->next);
	}
	return 0;
}

/// <summary>������������ ������ ���� ����� ������ � ������ ������</summary>
void LinkedList_Dispose(LinkedList* list) {
	if (list->head != NULL) NodeChain_Dipose(list->head);
	free(list);
}


// - - - - - - - - - - - - - - - -
//   S T A C K


/// <summary>������� ������ � ������������ ������</summary>
Stack* NewStack(size_t valSize) {
	Stack* res = (Stack*)malloc(sizeof(Stack));
	if (res != NULL) {
		res->TopOfStack = NULL;
		res->valSize = valSize;
	}
	return res;
}

/// <summary>"�����" �������� � ������</summary>
void Stack_Push(Stack* obj, const void* value) {
	Node* newNode = NewNode(value, obj->valSize);
	if (obj->TopOfStack != NULL) newNode->next = obj->TopOfStack;
	obj->TopOfStack = newNode;
}

/// <summary>"������������" �������� ������� ������</summary>
void* Stack_Peek(Stack* obj) {
	if (obj->TopOfStack) return obj->TopOfStack->value;
	else return NULL;
}

/// <summary>"�����" �������� �� ������</summary>
/// <param name="targetVariable">������� ����������, ����������� ���������� ��������</param>
void Stack_Pop(Stack* obj, void* targetVariable) {
	if (obj->TopOfStack) {
		AssignValue(targetVariable, obj->TopOfStack->value, obj->valSize);
		obj->TopOfStack = NodeChain_Decapitate(obj->TopOfStack);
	}
}

bool Stack_IsEmpty(Stack* obj) {
	return obj->TopOfStack ? false : true;
}

/// <summary>������������ ������ ���� ����� ������ � ����� ������</summary>
void Stack_Dispose(Stack* obj) {
	if (obj->TopOfStack != NULL) NodeChain_Dipose(obj->TopOfStack);
	free(obj);
}


// - - - - - - - - - - - - - - - -
//   L I S T  (D Y N A M I C  A R R A Y)


/// <summary>������� ����� ������</summary>
/// <param name="elSize">������ ������ �������� ������</param>
/// <param name="capacity">��������� ����������� ������</param>
/// <returns>��������� �� ��������� ������ � ������������ ������</returns>
List* NewList(size_t elSize, unsigned int capacity) {
	List* listObj = (List*)malloc(sizeof(List));
	if (listObj != NULL) {
		listObj->elSize = elSize;
		listObj->capacity = capacity;
		listObj->last = -1;
		listObj->arr = malloc(capacity * elSize);
	}
	return listObj;
}

/// <summary>����������� ������, �������� �����������</summary>
int List_RefactorList(List* obj) {
	void* newpool = realloc(obj->arr, 2 * obj->capacity * obj->elSize);
	if (newpool == NULL) return 1;
	else {
		obj->arr = newpool;
		obj->capacity *= 2;
	}
	return 0;
}

/// <summary>��������� ������ � ����� ������</summary>
int List_AddTo(List* obj, const void* newValue) {
	if (obj->last + 1 == obj->capacity) {
		if (List_RefactorList(obj)) return 1;
	}
	obj->last++;
	AssignValue((char*)(obj->arr) + obj->last * obj->elSize, newValue, obj->elSize);
	return 0;
}

/// <summary>��������� ������ � ������</summary>
int List_InsertInto(List* obj, const void* newValue, unsigned int atIndex) {
	if (atIndex > obj->last) return 1;

	List_AddTo(obj, newValue);
	DragElement(obj->arr, obj->last, atIndex, obj->elSize);
	return 0;
}

/// <summary>������� ������ �� ������</summary>
int List_RemoveFrom(List* obj, unsigned int atIndex) {
	if (atIndex > obj->last) return 1;

	DragElement(obj->arr, atIndex, obj->last, obj->elSize);
	obj->last--;
	return 0;
}

/// <summary>������������ ������ � ��������</summary>
/// <returns>��������� �� ������ ��������</returns>
void* List_AccessAt(List* obj, unsigned int atIndex) {
	return (void*)((char*)(obj->arr) + atIndex * obj->elSize);
}

bool List_IsEmpty(List* obj) {
	return obj->last < 0 ? true : false;
}

int List_Count(List* obj) {
	return obj->last + 1;
}

/// <summary>������������ ������ ������� ������ � ������ ������</summary>
void List_Dispose(List* obj) {
	free(obj->arr);
	free(obj);
}