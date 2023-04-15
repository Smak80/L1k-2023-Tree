#include "tree.h"
using namespace std;

bool add(node*& root, int value);
int find(const node* root, int value);
bool remove(node*& root, int val);
void drop(node*& root);
int get_height(const node* root);

void prefix_traverse(node* root, queue<node*>& q);
void infix_traverse(node* root, queue<node*>& q);
void postfix_traverse(node* root, queue<node*>& q);

bool add(tree& t, int value)
{
	return add(t.root, value);
}

int find(tree t, int value)
{
	return find(t.root, value);
}

bool remove(tree& t, int value)
{
	return remove(t.root, value);
}

void remove_leaf(node*& parent, node*& rem, bool is_sub_right, value& saved_value)
{
	auto& sub = (is_sub_right) ? rem->left : rem->right;
	if (sub) remove_leaf(rem, sub, is_sub_right, saved_value);
	else
	{
		auto del = rem;
		saved_value = rem->v;
		rem = is_sub_right ? rem->right : rem->left;
		delete del;
	}
	parent->height = get_height(parent);
}

bool remove(node*& root, int val)
{
	// 1. Если дерево не пустое
	if (root)
	{
		if (root->v.x != val) {
		    //Рекурсивно спускаемся по дереву выбирая ветки
		    //Условием выше ждём пока элемент не станет корневым какого-то из поддеревьев
		    auto res = remove(val < root->v.x ? root->left : root->right, val);

		    if (res) root->height = get_height(root);
		    return res;
		}
		
		// Элемент корень какого-то поддерева
		// 2. Смотрим на высоту ветвей этого поддерева
		auto lh = get_height(root->left);
		auto rh = get_height(root->right);
		if (lh == 0 && rh == 0) // Если этот элемент лист, то удаляем
		{
		    delete root;
		    return true;
		}
		auto is_sub_right = lh < rh;
		
		// 3. Заменяем элемент минимальным значением
		// из правого поддерева или максимальным из левого
		auto* rem = (is_sub_right) ? root->right : root->left;
		value saved_value;
		remove_leaf(root, rem, is_sub_right, saved_value);
		root->v = saved_value;
		return true;
	}
	
	return false;
}

int find(const node* root, int value)
{
	if (root) {
		if (root->v.x == value) return root->v.count;
		return find(value < root->v.x ? root->left : root->right, value);
	}
	return 0;
}

void drop(tree& t)
{
	drop(t.root);
}

queue<node*> prefix_traverse(tree& t)
{
	queue<node*> q;
	prefix_traverse(t.root, q);
	return q;
}

void prefix_traverse(node* root, queue<node*>& q)
{
	if (root) {
		q.push(root);
		prefix_traverse(root->left, q);
		prefix_traverse(root->right, q);
	}
}

queue<node*> infix_traverse(tree& t)
{
	queue<node*> q;
	infix_traverse(t.root, q);
	return q;
}

void infix_traverse(node* root, queue<node*>& q)
{
	if (root) {
		infix_traverse(root->left, q);
		q.push(root);
		infix_traverse(root->right, q);
	}
}

queue<node*> postfix_traverse(tree& t)
{
	queue<node*> q;
	postfix_traverse(t.root, q);
	return q;
}

void postfix_traverse(node* root, queue<node*>& q)
{
	if (root) {
		postfix_traverse(root->left, q);
		postfix_traverse(root->right, q);
		q.push(root);
	}
}



void drop(node*& root)
{
	if (!root) return;
	if (root->left) drop(root->left);
	if (root->right) drop(root->right);
	delete root;
	root = nullptr;
}

bool add(node*& root, int value)
{
	if (!root)
	{
		auto* new_node = new node;
		new_node->v.x = value;
		root = new_node;
		return true;
	}
	if (root->v.x == value)
	{
		root->v.count++;
		return false;
	}
	const auto result = add(value < root->v.x ? root->left : root->right, value);
	if (result) root->height = get_height(root);
	return result;
}

int get_height(const node* root)
{
	if (!root) return 0;
	const auto lh = (root->left) ? root->left->height : 0;
	const auto rh = (root->right) ? root->right->height : 0;
	return 1 + (lh < rh ? rh : lh);
}
