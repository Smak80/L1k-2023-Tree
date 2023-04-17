#include <iostream>
#include "tree.h"
#include "structs.h"
#include "queue.h"
using namespace  std;
enum traverse_type {prefix, infix, postfix, wide};

void show_elems(tree t, traverse_type tt)
{
	queue q;
	switch (tt)
	{
	case prefix : q = prefix_traverse(t); break;
	case infix  : q = infix_traverse(t); break;
	case postfix: q = postfix_traverse(t); break;
	case wide: q = wide_traverse(t); break;
	}
	auto curr = q.first;
	while (curr)
	{
		const auto v = curr->tree_node;
		if (!v) cout << "[-]";
		else cout << (v->v.x) << "(" << v->v.count << "; " << v->height << ")";
		cout << " ";
		curr = curr->next;
	}
	cout << endl;
	clear(q);
}

void main()
{
	setlocale(LC_ALL, "");
	tree t;
	//int a[] = { 0, 5, 20, 30, 40, 28, 26, 24, 21, 22, 23 };
	//int a[] = { 'B', 'A', 'D', 'C', 'E', 'F'};
	int a[] = { 6,3,10,1,4,8,12,14 };
	for (int i : a)
	{
		add(t, i);
	}
	//show_elems(t, prefix);
	//show_elems(t, infix);
	//show_elems(t, postfix);
	show_elems(t, wide);
	remove(t, 1);
	show_elems(t, wide);
	remove(t, 4);
	show_elems(t, wide);
	drop(t);
}