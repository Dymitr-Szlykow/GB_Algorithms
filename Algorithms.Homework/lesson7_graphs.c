#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lesson3.h"
#include "lesson5.h"
#include "lesson7.h"

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#define bool int
#define true 1
#define false 0


bool IsVisited(int* trackingArray, void* ID) {
	return *(trackingArray + *(int*)ID);
}

void SetVisited(int* trackingArray, void* ID) {
	*(trackingArray + *(int*)ID) = 1;
}


// - - - - - - - - - - - - - - - -
// G R A P H:  A D J A C E N C Y  L I S T S


/// <summary>������� ���� �� ������ ������� ���������� � ������������ ������</summary>
ListGraph* NewListGraph(size_t valSize, bool IsWeighted, bool IsDirected) {
	ListGraph* res = (ListGraph*)malloc(sizeof(ListGraph));
	if (res == NULL) AbortNewListGraph(&res);
	else {
		res->vertices = NewList(valSize, 10);
		res->edges = NewList(sizeof(void*), 10);
		if (res->vertices == NULL || res->edges == NULL) AbortNewListGraph(&res);
		else {
			res->IsWeighted = IsWeighted;
			res->IsDirected = IsDirected;
		}
	}
	return res;
}
void AbortNewListGraph(ListGraph** graph) {
	if (*graph) {
		if ((*graph)->vertices) {
			if ((*graph)->vertices->arr) free((*graph)->vertices->arr);
			free((*graph)->vertices);
		}
		if ((*graph)->edges) {
			if ((*graph)->edges->arr) free((*graph)->edges->arr);
			free((*graph)->edges);
		}
		free(*graph);
	}
	*graph = NULL;
}

/// <summary>������������ ������ � ������, ����������� � ���������� ����</summary>
/// <param name="vertexID">- ������������� ���� �����</param>
/// <returns>�������� ���� ������ ����������</returns>
Node* ListGraph_AccessEdges(ListGraph* obj, int vertexID) {
	return ((LinkedList*)List_AccessAt(obj->edges, vertexID))->head;
}

/// <summary>��������� ���� � ��������� ��������� ��� ������</summary>
/// <returns>������������� ����; -1 ��� ������</returns>
int ListGraph_AddNode_Unconnected(ListGraph* obj, const void* newValue) {
	LinkedList* adjacency = NewLinkedList(obj->IsWeighted ? sizeof(int[2]) : sizeof(int));
	if (adjacency == NULL) return -1;
	if (List_AddTo(obj->vertices, newValue)) return -1;
	if (List_AddTo(obj->edges, adjacency)) return -1;
	return obj->vertices->last;
}

/// <summary>������� ����� (��� �������������) / ���� ������ (��� ���������������) ����� ������ �����</summary>
/// <returns>0 - �������; 1 - ������</returns>
int ListGraph_MakeConnection_unweighted(ListGraph* obj, unsigned int fromID, unsigned int toID) {
	if (fromID > obj->vertices->last || toID > obj->vertices->last || obj->IsWeighted == true) return 1;

	if (LinkedList_AddNode(List_AccessAt(obj->edges, fromID), &toID)) return 1;
	if (obj->IsDirected == false) {
		if (LinkedList_AddNode(List_AccessAt(obj->edges, toID), &fromID)) return 1;
	}
	return 0;
}

/// <summary>������� ����� (��� �������������) / ���� ������ (��� ���������������) � ��������� ����� ����� ������ �����</summary>
/// <returns>0 - �������; 1 - ������</returns>
int ListGraph_MakeConnection_weighted(ListGraph* obj, unsigned int fromID, unsigned int toID, int weight) {
	if (fromID > obj->vertices->last || toID > obj->vertices->last || obj->IsWeighted == false) return 1;

	int edge[2] = { toID, weight };
	if (LinkedList_AddNode(List_AccessAt(obj->edges, fromID), &edge)) return 1;
	if (obj->IsDirected == false) {
		edge[0] = fromID;
		if (LinkedList_AddNode(List_AccessAt(obj->edges, toID), &edge)) return 1;
	}
	return 0;
}

/// <summary>����� ����� ����� � ������ (�����, ��� ����� ����)</summary>
/// <param name="startID">- ������������� ���������� ����</param>
/// <param name="visit">- �������� � ������� �����</param>
void ListGraph_TraversalWidthfirst(ListGraph* graph, int startID, void(*visit)(void*)) {
	Queue* queueOfInt = NewQueue(sizeof(int));
	int* visited = (int*)calloc(graph->vertices->last + 1, sizeof(int));
	if (!queueOfInt || !visited) return;

	Node* edge;
	int stop = false;

	while (!stop) {
		edge = ListGraph_AccessEdges(graph, startID);
		while (edge) {
			if (!IsVisited(visited, edge->value)) Queue_Enqueue(queueOfInt, edge->value);
			SetVisited(visited, edge->value);
			edge = edge->next;
		}

		visit(List_AccessAt(graph->vertices, startID));
		stop = Queue_Dequeue(queueOfInt, &startID);
	}

	free(visited);
	Queue_Dispose(queueOfInt, NULL);
}

/// <summary>����� ����� ����� "� �������"
/// ����� ����������
/// </summary>
/// <param name="startID">- ������������� ���������� ����</param>
/// <param name="visit">- �������� � ������� �����</param>
void ListGraph_TraversalDepthfirst(ListGraph* graph, int startID, void(*visit)(void*)) {
	Stack* stackOfInt = NewQueue(sizeof(int));
	int* visited = (int*)calloc(graph->vertices->last + 1, sizeof(int));
	if (!stackOfInt || !visited) return;

	Node* edge;
	int stop = false;

	while (!stop) {
		edge = ListGraph_AccessEdges(graph, startID);
		while (edge) {
			if (!IsVisited(visited, edge->value)) Stack_Push(stackOfInt, edge->value);
			SetVisited(visited, edge->value);
			edge = edge->next;
		}

		visit(List_AccessAt(graph->vertices, startID));
		stop = Stack_Pop(stackOfInt, &startID);
	}

	free(visited);
	Stack_Dispose(stackOfInt, NULL);
}

/// <summary>������� ���� � ����� �����</summary>
/// <param name="printValue">- ������� ������ �������� �����</param>
void ListGraph_Print(ListGraph* obj, void(*printValue)(const void*)) {
	int i, edge[2], end = obj->vertices->last + 1;
	Node* temp;

	for (i = 0; i < end; i++) {
		printf(" #%d: ", i);
		printValue(List_AccessAt(obj->vertices, i));

		if (temp = ListGraph_AccessEdges(obj, i)) {
			printf("\t\t������: ");

			while (temp) {
				AssignValue(&edge, temp->value, temp->valSize);
				if (!obj->IsWeighted) printf("#%d, ", *(int*)temp->value);
				else printf("#%d (%d), ", *(int*)temp->value, *((int*)temp->value + 1));
				temp = temp->next;
			}
		}
		printf("\n");
	}
}

/// <summary>������������ ������ �����</summary>
/// <param name="disposeValues">- �������, ������������� ������� �������� � ������������ ������; ����� - NULL</param>
void ListGraph_Dispose(ListGraph* graph, void(disposeValues)(void*)) {
	List_Dispose(graph->vertices, disposeValues);
	List_Dispose(graph->edges, NULL);
	free(graph);
}

