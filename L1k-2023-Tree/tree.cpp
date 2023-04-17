#include "tree.h"

#include <cstdlib>

using namespace std;

void small_left_rotate(node*& root);
void small_right_rotate(node*& root);
void big_left_rotate(node*& root);
void big_right_rotate(node*& root);
void balance(node*& root);

bool add(node*& root, int value);
int find(const node* root, int value);
bool remove(node*& root, int val);
void drop(node*& root);
int get_height(const node* root);

void prefix_traverse(node* root, queue& q);
void infix_traverse(node* root, queue& q);
void postfix_traverse(node* root, queue& q);
void wide_traverse(node* root, queue& q);


void small_left_rotate(node*& root)
{
	node* new_root = root->right;
	root->right = new_root->left;
	new_root->left = root;
	root->height = get_height(root);
	root = new_root;
}
void small_right_rotate(node*& root)
{
	node* new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	root->height = get_height(root);
	root = new_root;
}
void big_left_rotate(node*& root)
{
	small_right_rotate(root->right);
	small_left_rotate(root);
}
void big_right_rotate(node*& root)
{
	small_left_rotate(root->left);
	small_right_rotate(root);
}
void balance(node*& root)
{
	if (not root) return;

	int lh = get_height(root->left);
	int rh = get_height(root->right);

	if (abs(lh - rh) > 1)
	{
		if (lh > rh)
		{
			int l_lh = get_height(root->left->left);
			int l_rh = get_height(root->left->right);
			if (l_lh > l_rh) small_right_rotate(root);
			else big_right_rotate(root);
		}
		else
		{
			int r_lh = get_height(root->right->left);
			int r_rh = get_height(root->right->right);
			if (r_rh > r_lh) small_left_rotate(root);
			else big_left_rotate(root);
		}
	}
}

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
	balance(parent);
	parent->height = get_height(parent);
}

bool remove(node*& root, int val)
{
	// 1. »щем удал€емый элемент
	if (root)
	{
		if (root->v.x != val) { // Ёлемент пока не найден
			auto res = remove(val < root->v.x ? root->left : root->right, val);
			if (res) root->height = get_height(root);
			return res;
		}
		// Ёлемент найден
		// 2. ќпредел€ем какое из поддеревьев выше
		auto lh = get_height(root->left);
		auto rh = get_height(root->right);
		if (lh == 0 && rh == 0) // ”дал€емый элемент - лист
		{
			delete root;
			return true;
		}
		auto is_sub_right = lh < rh;
		// 3. ѕоиск наименьшего элемента в правом поддереве
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

queue prefix_traverse(tree& t)
{
	queue q;
	prefix_traverse(t.root, q);
	return q;
}

void prefix_traverse(node* root, queue& q)
{
	if (root) {
		enqueue(q, root);
		prefix_traverse(root->left, q);
		prefix_traverse(root->right, q);
	}
}

queue infix_traverse(tree& t)
{
	queue q;
	infix_traverse(t.root, q);
	return q;
}

void infix_traverse(node* root, queue& q)
{
	if (root) {
		infix_traverse(root->left, q);
		enqueue(q, root);
		infix_traverse(root->right, q);
	}
}

queue postfix_traverse(tree& t)
{
	queue q;
	postfix_traverse(t.root, q);
	return q;
}

void postfix_traverse(node* root, queue& q)
{
	if (root) {
		postfix_traverse(root->left, q);
		postfix_traverse(root->right, q);
		enqueue(q, root);
	}
}

queue wide_traverse(tree& t)
{
	queue q;
	wide_traverse(t.root, q);
	return q;
}

void wide_traverse(node* root, queue& q)
{
	if (root) {
		auto h = root->height;
		enqueue(q, root);
		queue_elem* curr = q.first;
		for (int i = 1; i < (1 << h) - 1; i+=2)
		{
			enqueue(q, curr->tree_node ? curr->tree_node->left : nullptr);
			enqueue(q, curr->tree_node ? curr->tree_node->right : nullptr);
			curr = curr->next;
		}
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
	balance(root);
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