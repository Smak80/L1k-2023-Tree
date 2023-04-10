#pragma once
#include <queue>

struct value
{
	int x;
	int count = 1;
};

struct node
{
	value v;
	int height = 1;
	node* left = nullptr;
	node* right = nullptr;
};

struct tree
{
	node* root = nullptr;
};

bool add(tree& t, int value);
int find(tree  t, int value);
bool remove(tree& t, int value);
void drop(tree& t);

std::queue<node*> prefix_traverse(tree& t);
std::queue<node*> infix_traverse(tree& t);
std::queue<node*> postfix_traverse(tree& t);


