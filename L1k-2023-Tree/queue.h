#pragma once
#include "structs.h"

struct queue_elem
{
	node* tree_node;
	queue_elem* next = nullptr;
	queue_elem* prev = nullptr;
};

struct queue
{
	queue_elem* first = nullptr;
	queue_elem* last  = nullptr;
};

void enqueue(queue& q, node* employee);
bool dequeue(queue& q, node*& employee);
void clear(queue& q);
