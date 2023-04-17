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
		else cout << (char)(v->v.x) << "(" << v->v.count << ")";
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
	int a[] = { 'F', 'B', 'G', 'A', 'D', 'I', 'C', 'E', 'H' };
	for (int i : a)
	{
		add(t, i);
	}
	show_elems(t, prefix);
	show_elems(t, infix);
	show_elems(t, postfix);
	show_elems(t, wide);
	remove(t, 20);
	drop(t);
}