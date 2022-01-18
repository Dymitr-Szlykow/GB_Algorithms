#ifndef LESSON7_H
#define LESSON7_H

#define bool int
#define true 1
#define false 0

// ������� � ������� �7.
// 1. �������� �������, ������� ��������� ������� ��������� �� ����� � ������� �� �� �����.
// 2. �������� ����������� ������� ������ ����� � �������.
// 3. �������� ������� ������ ����� � ������.
// 4. * ������� ���������� ������� ��� ������ � �������.


//typedef struct graphNode {
//} TreeNode;

typedef struct graph_AdjacencyList {
	struct list* vertices;
	struct list* edges; // ��. ������� 5
	size_t valSize;
	bool IsWeighted, IsDirected;
} ListGraph;


// g e n e r i c  e l e m e n t s

// G R A P H:  A D J A C E N C Y  L I S T S
ListGraph* NewListGraph(size_t valSize, bool IsWeighted, bool IsDirected);
void  AbortNewListGraph(ListGraph* graph);
Node* ListGraph_AccessEdges(ListGraph* obj, int vertexID);
int   ListGraph_AddNode_Unconnected(ListGraph* obj, const void* newValue);
void  ListGraph_Dispose(ListGraph* graph, void(disposeValues)(void*));
int   ListGraph_MakeConnection_unweighted(ListGraph* obj, unsigned int fromID, unsigned int toID);
int   ListGraph_MakeConnection_weighted(ListGraph* obj, unsigned int fromID, unsigned int toID, int weight);
void  ListGraph_Print(ListGraph* obj, void(*printValue)(const void*));
void  ListGraph_TraversalWidthfirst(ListGraph* graph, int startID, void(*visit)(void*));

#endif