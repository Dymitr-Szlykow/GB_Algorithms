#include <conio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lesson5.h"

#pragma warning(disable : 4996)

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


/// <summary>
/// 1. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
/// </summary>
void Task_5_1(void) {
	int number;
	printf("Введите число: ");
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
/// 3. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.
/// </summary>
void Task_5_3(void) {
	char
		* str1 = "())({)",
		* str2 = "([(])",
		* str3 = "[2/{5*(4+7)}]";
	char input[64];
	printf("Последовательности скобок.\n");
	printf("В выражении \"%s\" - %sвыдержана.\n", str1, BracersSequenceIsOK(str1) ? "" : "не ");
	printf("В выражении \"%s\" - %sвыдержана.\n", str2, BracersSequenceIsOK(str2) ? "" : "не ");
	printf("В выражении \"%s\" - %sвыдержана.\n", str3, BracersSequenceIsOK(str3) ? "" : "не ");

	printf("\nВведите выражение:  ");
	fgets(input, 64, stdin);
	printf("Последовательность скобок %sвыдержана.\n", BracersSequenceIsOK(input) ? "" : "не ");
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
	if (!Stack_IsEmpty(stack) && meanwhile == true) meanwhile = false;

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
/// 4. * Создать функцию, копирующую односвязный список (то есть создает в памяти копию односвязного списка, не удаляя первый список).
/// </summary>
void Task_5_4(void) {
	LinkedList* list1 = InitNewLinkedList(sizeof(int), 9);
	printf("Исходный список:  ");
	PrintNodeChain(list1->head);
	printf("\n");

	LinkedList* list2 = CopyLinkedList(list1);
	printf("Копия списка:     ");
	PrintNodeChain(list2->head);
	printf("\n\n");

	if (LinkedList_DeleteNode(list2, 4)) printf("не могу удалить по индексу 4:\t");
	else printf("удаляю по индексу 4:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	if (LinkedList_DeleteNode(list2, 6)) printf("не могу удалить по индексу 6:\t");
	else printf("удаляю по индексу 6:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	if (LinkedList_DeleteNode(list2, 10)) printf("не могу удалить по индексу 10:\t");
	else printf("удаляю по индексу 10:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	if (LinkedList_DeleteNode(list2, 0)) printf("не могу удалить по индексу 0:\t");
	else printf("удаляю по индексу 0:\t\t");
	PrintNodeChain(list2->head);
	printf("\n");

	Node* out = LinkedList_ExcludeNode(list2, 3);
	printf("вычленяю узел[3] (%d):\t\t", ToInt(out->value));
	PrintNodeChain(list2->head);
	printf("\n\n");

	NodeChain_Dipose(out);
	out = LinkedList_ExcludeNode(list2, 10);

	printf("Исходный список:  ");
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
/// 5. **Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.
/// </summary>
void Task_5_5(void) {
	char* expressions[10] = {
		"12 * 4 + 7 * 2 = 31 * 2",
		"12 + 4 * 7 + 2 = 42",
		"12 + 4 * 7 / 2 = 3 + 3 * 3 + 3 / 3 * 6 + 4 + 4",
		"12 + 4 * (7 + 2) > 45",
		"(12 + 8) / (7 + 3) = 2",
		"(22 + 4 * (7 - 2) - 4 * (9 + 1)) + 5 = 7",
		"12 + 8 < (3 * 15) + 1 < 12 * (5 - 1)"
	};

	int i;
	for (i = 0; i < 7; i++) {
		printf("%s\n", expressions[i]);
		if (Print_PostfixNotation(expressions[i])) {
			printf("\n ! что-то пошло не так !\n");
			return;
		}
		printf("\n\n");
	}
}

int Print_PostfixNotation(char* expression) {
	Stack* stack = NewStack(sizeof(char));
	char c = ' ';
	int shift;

	while (*expression != '\0') {
		if ('0' <= (*expression) && (*expression) <= '9') {
			printf("%c", *expression++);
			if (*(expression) == ' ' || *(expression) == '\0' || *(expression) == ')') printf(" ");
		}

		else if ((*expression) == '+' || (*expression) == '-') {
			PrintPostfix_UnloadStack(stack);
			Stack_Push(stack, expression++);
		}

		else if ((*expression) == '*' || (*expression) == '/') {
			PrintPostfix_UnloadUntilLowPrecedence(stack);
			Stack_Push(stack, expression++);
		}

		//else if ((*expression) == '(') {
		//	if ((shift = PrintPostfix_ProcessSubstring_Recursive(expression)) < 0) return 1;
		//	else expression += shift;
		//}

		else if ((*expression) == '(') {
			Stack_Push(stack, expression++);
		}
		else if ((*expression) == ')') {
			PrintPostfix_UnloadStack(stack);
			expression++;
		}

		else if ((*expression) == '=' || (*expression) == '<' || (*expression) == '>') {
			if (PrintPostfix_UnloadStack(stack)) {
				Stack_Dispose(stack);
				return 1;
			}
			printf("%c ", *expression++);
		}

		else expression++;
	}
	if (PrintPostfix_UnloadStack(stack)) {
		Stack_Dispose(stack);
		return 1;
	}

	Stack_Dispose(stack);
	return 0;
}

int PrintPostfix_ProcessSubstring_Recursive(char* position) {
	Stack* stack = NewStack(sizeof(char));
	Stack_Push(stack, position++);
	int length = -1, i;
	char c;

	while (!Stack_IsEmpty(stack)) {
		length++;
		if (*(position + length) == '(') Stack_Push(stack, position);
		else if (*(position + length) == ')') Stack_Pop(stack, &c);
	}
	Stack_Dispose(stack);


	char* substring = (char*)malloc(length + 1);
	if (substring == NULL) return -1;
	else {
		for (i = 0; i < length; i++) {
			*(substring + i) = *position++;
		}
		*(substring + length) = '\0';
		Print_PostfixNotation(substring);
		free(substring);
	}

	return length + 2;
}

int PrintPostfix_UnloadStack(Stack* stack) {
	char c;
	int res;
	while (!Stack_IsEmpty(stack)) {
		Stack_Pop(stack, &c);
		if (c == '(') return 1;
		printf("%c ", c);
	}
	return 0;
}

void PrintPostfix_UnloadUntilLowPrecedence(Stack* stack) {
	char c;
	while (!Stack_IsEmpty(stack)) {
		c = *((char*)Stack_Peek(stack));
		if (c == '+' || c == '-' || c == '(') return;

		else if (c == '*' || c == '/') {
			Stack_Pop(stack, &c);
			printf("%c ", c);
		}
	}
}


/// <summary>
/// 6. * Реализовать очередь.
/// </summary>
void test_QueueLinked(void) {
	Queue* queue = NewQueue(sizeof(int));
	int i, in, out;

	printf("Исходная очередь %s\n\n", Queue_IsEmpty(queue) ? "пуста" : "должна бы быть пуста, хм-м...");

	for (i = 0; i < 16; i++) {
		in = i * 2 + 1;

		printf("добавляю значение %d:\t\t", in);
		if (Queue_Enqueue(queue, &in)) printf("не вышло :(\n");
		else {
			PrintNodeChain(queue->front);
			printf("\t  элементов %d, впереди - %d\n", queue->count, ToInt(Queue_Peek(queue)));
		}

		if ((i + 1) % 3 == 0) {
			printf("достаю значение ");
			if (Queue_Dequeue(queue, &out)) printf("не вышло :(\n");
			else {
				printf("%d:\t\t", out);
				PrintNodeChain(queue->front);
				printf("\t  элементов %d, впереди - %d\n", queue->count, ToInt(Queue_Peek(queue)));
			}
		}
	}
	printf("\n");

	for (i = 0; i < 16; i++) {
		out = i * 2 + 1;
		printf("в очереди %s %d\n", Queue_Has(queue, &out) ? "имеется значение" : "нет значения", out);
	}

	Queue_Dispose(queue);
}

void test_QueueArray(void) {
	QueueArr* queue = NewQueueArr(sizeof(int), 5);
	int i, in, out;

	printf("Исходная очередь %s\n\n", QueueArr_IsEmpty(queue) ? "пуста" : "должна бы быть пуста, хм-м...");

	for (i = 0; i < 16; i++) {
		in = i * 2 + 1;

		printf("добавляю значение %d:\t\t", in);
		if (QueueArr_Enqueue(queue, &in)) printf("не вышло (\n");
		else PrintQueueArray(queue);

		if ((i + 1) % 3 == 0) {
			printf("достаю значение ");
			if (QueueArr_Dequeue(queue, &out)) printf("\t\tне вышло :(\n");
			else {
				printf("%d:\t\t", out);
				PrintQueueArray(queue);
			}
		}
	}

	for (i = 0; i < 16; i++) {
		out = i * 2 + 1;
		printf("в очереди %s %d\n", QueueArr_Has(queue, &out) ? "имеется значение" : "нет значения", out);
	}

	QueueArr_Dispose(queue);
}

void PrintQueueArray(QueueArr* obj) {
	if (obj) {
		int i, count = QueueArr_Count(obj);
		for (i = 0; i < count; i++) {
			printf("%d ", ToInt((char*)obj->arr + ((obj->front + i) % obj->capacity) * obj->elSize));
		}
		printf("\t  эл-тов %d/%d, впереди %d\n", count, obj->capacity, ToInt(QueueArr_Peek(obj)));
	}
}


/// <summary>
/// тест: список (динамический массив)
/// </summary>
void test_DynamicList(void) {
	List* list = NewList(sizeof(int), 5);
	int i, newValue;

	printf("Исходный список %s\n\n", List_IsEmpty(list) ? "пуст" : "должен бы быть пустым, хм-м...");

	printf("Добавление элементов:\n");
	for (i = 0; i < 9; i++) {
		newValue = i * 2 + 1;
		List_AddTo(list, &newValue);
		PrintDynamicList(list);
	}

	printf("Удаление элемента:\n");
	List_RemoveFrom(list, 5);
	PrintDynamicList(list);

	printf("Вставка элемента:\n");
	newValue = 42;
	List_InsertInto(list, &newValue, 3);
	PrintDynamicList(list);
	
	List_Dispose(list);
}

void PrintDynamicList(List* obj) {
	if (obj) {
		int i;
		printf("    эл-тов %2d/%-2d, последний №%d:\t\t", List_Count(obj), obj->capacity, obj->last);
		for (i = 0; i <= obj->last; i++) {
			printf("%d ", ToInt(List_AccessAt(obj, i)));
		}
		printf("\n");
	}
}


// - - - - - - - - - - - - - - - -
//   g e n e r i c  e l e m e n t s


/// <summary>обобщенное присваивание</summary>
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

/// <summary>обобщенный обмен значений</summary>
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

/// <summary>обобщенное сравнение</summary>
bool AreEqual(const void* left, const void* right, size_t size) {
	int chunk;
	if (size % sizeof(int) == 0) {
		size /= sizeof(int);
		for (chunk = 0; chunk < size; chunk++) {
			if (*((int*)left + chunk) != *((int*)right + chunk)) return false;
		}
	}
	else {
		for (chunk = 0; chunk < size; chunk++) {
			if (*((char*)left + chunk) != *((char*)right + chunk)) return false;
		}
	}
	return true;
}

/// <summary>продвигает элемент по массиву</summary>
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

/// <summary>читает значение как int</summary>
int ToInt(void* value) {
	return *((int*)value);
}

/// <summary>читает значение как char</summary>
char ToChar(void* value) {
	return *((char*)value);
}


// - - - - - - - - - - - - - - - -
//   L I N K A B L E  N O D E:  one-way


/// <summary>создает связываемый узел в динамической памяти</summary>
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

/// <summary>проходит по цепочке узлов до последнего</summary>
/// <returns>указатель на последний узел в цепочке</returns>
Node* NodeChain_GetLastInLine(Node* node) {
	while (node->next != NULL) {
		node = node->next;
	}
	return node;
}

/// <summary>связывает второй узел и его хвост с первым, хвост первого связывается с хвостом второго</summary>
int NodeChain_InsertAsNext(Node* obj, Node* newNode) {
	if (obj->valSize != newNode->valSize) return 1;
	if (obj->next != NULL) (NodeChain_GetLastInLine(newNode))->next = obj->next;
	obj->next = newNode;
	return 0;
}

/// <summary>симулирует вставку "перед"</summary>
/// <param name="newNode">узел без хвоста</param>
int Node_InsertAsPrev(Node* obj, Node* newNode) {
	if (newNode->next != NULL || obj->valSize != newNode->valSize) return 1;

	if (obj->next != NULL) newNode->next = obj->next;
	obj->next = newNode;
	SwapValues(obj->value, newNode->value, obj->valSize);
	return 0;
}

/// <summary>разворачивает цепочку связных узлов</summary>
/// <returns>бывший последний узел цепочки</returns>
Node* NodeChain_Reverse(Node* head) {
	if (head == NULL || head->next == NULL) return head;

	Node* newHead = NodeChain_Reverse(head->next);
	(head->next)->next = head;
	head->next = NULL;
	return newHead;
}

/// <summary>высвобождает память возглавгляющего узла цепочки</summary>
/// <returns>указатель на узел, следующий за бывшим возглавляющим</returns>
Node* NodeChain_Decapitate(Node* head) {
	Node* res = head->next;
	free(head->value);
	free(head);
	return res;
}

/// <summary>высвобождает память всех следующих узлов</summary>
void NodeChain_DiposeTail(Node* node) {
	if (node->next) {
		NodeChain_DiposeTail(node->next);
		free(node->next->value);
		free(node->next);
	}
}

/// <summary>высвобождает память всех следующих и текущего узла</summary>
void NodeChain_Dipose(Node* node) {
	NodeChain_DiposeTail(node);
	free(node->value);
	free(node);
}


// - - - - - - - - - - - - - - - -
//   L I N K E D  L I S T


/// <summary>создает связный список в динамической памяти</summary>
LinkedList* NewLinkedList(size_t valSize) {
	LinkedList* res = (LinkedList*)malloc(sizeof(LinkedList));
	if (res != NULL) {
		res->head = NULL;
		//res->count = 0;
		res->valSize = valSize;
	}
	return res;
}

/// <summary>создает в куче копию указанного связного списка</summary>
/// <returns>указатель на новый список в динамической памяти</returns>
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

/// <summary>осуществляет доступ к Н-ому узлу связного списка</summary>
/// <returns>указатель на искомый узел</returns>
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

/// <summary>создает новый узел с указанным значением в конце связного списка</summary>
int LinkedList_AddNode(LinkedList* list, const void* value) {
	Node* newNode = NewNode(value, list->valSize);
	if (newNode == NULL) return 1;
	if (LinkedList_AttachChain(list, newNode)) return 1;
	return 0;
}

/// <summary>проикрепляет указанный узел к концу связного списка</summary>
int LinkedList_AttachChain(LinkedList* list, Node* node) {
	if (node->valSize != list->valSize) return 1;

	if (list->head == NULL) list->head = node;
	else (NodeChain_GetLastInLine(list->head))->next = node;
	return 0;
}

/// <summary>вставляет цепочку узлов в указанное положение</summary>
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

/// <summary>исключает узел на указанной позиции</summary>
/// <returns>указатель на исключенный узел</returns>
Node* LinkedList_ExcludeNode(LinkedList* list, unsigned int atIndex) {
	Node *res = NULL, * previous = LinkedList_Access(list, atIndex - 1);
	if (previous != NULL) {
		res = previous->next;
		previous->next = res->next;
		res->next = NULL;
	}
	return res;
}

/// <summary>удаляет указанный узел, высвобождает его память</summary>
int LinkedList_DeleteNode(LinkedList* list, unsigned int atIndex) {
	if (atIndex == 0) list->head = NodeChain_Decapitate(list->head);

	else {
		Node* prev = LinkedList_Access(list, atIndex - 1);
		if (prev == NULL) return 1;
		else prev->next = NodeChain_Decapitate(prev->next);
	}
	return 0;
}

/// <summary>высвобождает память всех узлов списка и самого списка</summary>
void LinkedList_Dispose(LinkedList* list) {
	if (list->head != NULL) NodeChain_Dipose(list->head);
	free(list);
}


// - - - - - - - - - - - - - - - -
//   S T A C K


/// <summary>создает стопку в динамической памяти</summary>
Stack* NewStack(size_t valSize) {
	Stack* res = (Stack*)malloc(sizeof(Stack));
	if (res != NULL) {
		res->TopOfStack = NULL;
		res->valSize = valSize;
		res->count = 0;
	}
	return res;
}

/// <summary>"ложит" значение в стопку</summary>
int Stack_Push(Stack* obj, const void* value) {
	Node* newNode = NewNode(value, obj->valSize);
	if (newNode == NULL) return 1;
	else {
		if (obj->TopOfStack != NULL) newNode->next = obj->TopOfStack;
		obj->TopOfStack = newNode;
		(obj->count)++;
	}
	return 0;
}

/// <summary>"подглядывает" значение наверху стопки</summary>
void* Stack_Peek(Stack* obj) {
	if (obj->TopOfStack) return obj->TopOfStack->value;
	else return NULL;
}

/// <summary>"берет" значение со стопки</summary>
/// <param name="targetVariable">целевая переменная, сохраняющая полученное значение</param>
int Stack_Pop(Stack* obj, void* targetVariable) {
	if (obj->TopOfStack == NULL) return 1;
	else {
		AssignValue(targetVariable, obj->TopOfStack->value, obj->valSize);
		obj->TopOfStack = NodeChain_Decapitate(obj->TopOfStack);
		(obj->count)--;
	}
	return 0;
}

/// <summary>проверяет наличие значения в стопке</summary>
bool Stack_Has(Stack* obj, const void* value) {
	Node* temp = obj->TopOfStack;
	while (temp) {
		if (AreEqual(temp->value, value, temp->valSize)) return true;
		temp = temp->next;
	}
	return false;
}

bool Stack_IsEmpty(Stack* obj) {
	return obj->count == 0;
}

/// <summary>высвобождает память всех узлов стопки и самой стопки</summary>
void Stack_Dispose(Stack* obj) {
	if (obj->TopOfStack != NULL) NodeChain_Dipose(obj->TopOfStack);
	free(obj);
}


// - - - - - - - - - - - - - - - -
//   Q U E U E


/// <summary>создает очередь в динамической памяти</summary>
Queue* NewQueue(size_t valSize) {
	Queue* res = (Queue*)malloc(sizeof(Queue));
	if (res != NULL) {
		res->front = res->rear = NULL;
		res->valSize = valSize;
		res->count = 0;
	}
	return res;
}

/// <summary>"ставит" значение в очередь</summary>
int Queue_Enqueue(Queue* obj, const void* newValue) {

	Node* newNode = NewNode(newValue, obj->valSize);
	if (newNode == NULL) return 1;
	else {
		if (obj->rear) {
			obj->rear->next = newNode;
			obj->rear = newNode;
		}
		else obj->front = obj->rear = newNode;
		(obj->count)++;
	}
	return 0;
}

/// <summary>"подглядывает" следующее в очереди значение</summary>
void* Queue_Peek(Queue* obj) {
	if (obj->front) return obj->front->value;
	else return NULL;
}

/// <summary>"достает" значение из очереди</summary>
int Queue_Dequeue(Queue* obj, void* targetVariable) {
	if (obj->front == NULL) return 1;
	else {
		AssignValue(targetVariable, obj->front->value, obj->valSize);
		obj->front = NodeChain_Decapitate(obj->front);
		if (obj->front == NULL) obj->rear = NULL;
		(obj->count)--;
	}
	return 0;
}

/// <summary>проверяет наличие значения в очереди</summary>
bool Queue_Has(Queue* obj, const void* value) {
	Node* temp = obj->front;
	while (temp) {
		if (AreEqual(temp->value, value, temp->valSize)) return true;
		temp = temp->next;
	}
	return false;
}

bool Queue_IsEmpty(Queue* obj) {
	return obj->count == 0;
}

/// <summary>высвобождает память всех узлов очереди и самой очереди</summary>
void Queue_Dispose(Queue* obj) {
	if (obj->front != NULL) NodeChain_Dipose(obj->front);
	free(obj);
}


// - - - - - - - - - - - - - - - -
//   L I S T  (D Y N A M I C  A R R A Y)


/// <summary>создает новый список в динамической памяти</summary>
/// <param name="capacity">начальная вместимость списка</param>
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

/// <summary>пересоздает список, удваивая вместимость</summary>
int List_RefactorList(List* obj) {
	void* newpool = realloc(obj->arr, 2 * obj->capacity * obj->elSize);
	if (newpool == NULL) return 1;
	else {
		obj->arr = newpool;
		obj->capacity *= 2;
	}
	return 0;
}

/// <summary>добавляет запись в конец списка</summary>
int List_AddTo(List* obj, const void* newValue) {
	if (obj->last + 1 == obj->capacity) {
		if (List_RefactorList(obj)) return 1;
	}
	obj->last++;
	AssignValue((char*)(obj->arr) + obj->last * obj->elSize, newValue, obj->elSize);
	return 0;
}

/// <summary>вставляет запись в список</summary>
int List_InsertInto(List* obj, const void* newValue, unsigned int atIndex) {
	if (atIndex > obj->last) return 1;

	List_AddTo(obj, newValue);
	DragElement(obj->arr, obj->last, atIndex, obj->elSize);
	return 0;
}

/// <summary>удаляет запись из списка</summary>
int List_RemoveFrom(List* obj, unsigned int atIndex) {
	if (atIndex > obj->last) return 1;

	DragElement(obj->arr, atIndex, obj->last, obj->elSize);
	obj->last--;
	return 0;
}

/// <summary>осуществляет доступ к элементу</summary>
/// <returns>указатель на начало элемента</returns>
void* List_AccessAt(List* obj, unsigned int atIndex) {
	return (void*)((char*)(obj->arr) + atIndex * obj->elSize);
}

bool List_IsEmpty(List* obj) {
	return obj->last < 0 ? true : false;
}

int List_Count(List* obj) {
	return obj->last + 1;
}

/// <summary>высвободжает память массива списка и самого списка</summary>
void List_Dispose(List* obj) {
	free(obj->arr);
	free(obj);
}


// - - - - - - - - - - - - - - - -
//   Q U E U E  (v i a  a r r a y)


/// <summary>создает новую очередь в динамической памяти</summary>
/// <param name="capacity">начальная вместимость очереди</param>
QueueArr* NewQueueArr(size_t elSize, unsigned int capacity) {
	QueueArr* res = (QueueArr*)malloc(sizeof(QueueArr));
	if (res != NULL) {
		res->elSize = elSize;
		res->capacity = capacity;
		res->front = res->rear = -1;
		res->arr = malloc(capacity * elSize);
	}
	return res;
}

/// <summary>пересоздает очередь, удваивая вместимость</summary>
int QueueArr_RefactorArray(QueueArr* obj) {
	void* newpool = malloc(2 * obj->capacity * obj->elSize);
	if (newpool == NULL) return 1;
	else {
		int i;
		for (i = 0; i < obj->capacity; i++) {
			AssignValue((char*)newpool + i * obj->elSize, (char*)obj->arr + ((obj->front + i) % obj->capacity) * obj->elSize, obj->elSize);
		}
		obj->front = 0;
		obj->rear = obj->capacity - 1;
		obj->capacity *= 2;

		free(obj->arr);
		obj->arr = newpool;
	}
	return 0;
}

/// <summary>"ставит" значение в очередь</summary>
int QueueArr_Enqueue(QueueArr* obj, const void* newValue) {
	if (obj->rear < 0) {
		obj->front = obj->rear = 0;
	}
	else {
		if ((obj->rear + 1) % obj->capacity == obj->front) {
			if (QueueArr_RefactorArray(obj)) return 1;
		}
		obj->rear = (obj->rear + 1) % obj->capacity;
	}
	AssignValue((char*)obj->arr + obj->rear * obj->elSize, newValue, obj->elSize);
	return 0;
}

/// <summary>"подглядывает" следующее в очереди значение</summary>
void* QueueArr_Peek(QueueArr* obj) {
	if (obj->rear < 0) return NULL;
	else return (void*)((char*)(obj->arr) + obj->front * obj->elSize);
}

/// <summary>"достает" значение из очереди</summary>
int QueueArr_Dequeue(QueueArr* obj, void* targetVariable) {
	if (obj->front < 0) return 1;
	AssignValue(targetVariable, (char*)obj->arr + obj->front * obj->elSize, obj->elSize);

	if (obj->front == obj->rear) obj->front = obj->rear = -1;
	else obj->front = (obj->front + 1) % obj->capacity;
	return 0;
}

/// <summary>проверяет наличие значения в очереди</summary>
bool QueueArr_Has(QueueArr* obj, const void* value) {
	int i, end = QueueArr_Count(obj) + 1;
	for (i = obj->front; i < end; i = (i + 1) % obj->capacity) {
		if (AreEqual((char*)obj->arr + i * obj->elSize, value, obj->elSize)) return true;
	}
	return false;
}

bool QueueArr_IsEmpty(QueueArr* obj) {
	return obj->rear < 0;
}

int QueueArr_Count(QueueArr* obj) {
	if (obj->rear < 0) return 0;
	else return 1 + (obj->rear - obj->front + obj->capacity) % obj->capacity;
}

/// <summary>высвободжает память массива очереди и самой очереди</summary>
void QueueArr_Dispose(QueueArr* obj) {
	free(obj->arr);
	free(obj);
}