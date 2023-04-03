#include <iostream>
#include "tree.h"
using namespace  std;

void main()
{
	setlocale(LC_ALL, "");
	tree t;
	int a[] = { 0, 5, 20, 30, 40, 28, 26, 24, 21, 22, 23 };
	for (int i : a)
	{
		add(t, i);
	}
	remove(t, 20);
	drop(t);
}