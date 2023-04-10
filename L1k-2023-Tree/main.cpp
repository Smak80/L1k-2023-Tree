#include <iostream>
#include "tree.h"
using namespace  std;
enum traverse_type {prefix, infix, postfix};

void show_elems(tree t, traverse_type tt)
{
	queue<node*> q;
	switch (tt)
	{
	case prefix : q = prefix_traverse(t); break;
	case infix  : q = infix_traverse(t); break;
	case postfix: q = postfix_traverse(t); break;
	}
	node* v;
	while (q.size() > 0 && (v = q.front()))
	{
		cout << v->v.x << "(" << v->v.count << ")";
		cout << " ";
		q.pop();
	}
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "");
	tree t;
	int a[] = { 0, 5, 20, 30, 40, 28, 26, 24, 21, 22, 23 };
	for (int i : a)
	{
		add(t, i);
	}
	show_elems(t, prefix);
	show_elems(t, infix);
	show_elems(t, postfix);
	remove(t, 20);
	drop(t);
}