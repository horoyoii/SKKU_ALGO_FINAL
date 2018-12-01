#include"headerFiles.h"

RSV_node_ptr RSV_MakeRBT(void) {
	return Sentinel;
}

RSV_node_ptr RSV_MakeNode(char *KEY) {
	RSV_node_ptr newNode = (RSV_node_ptr)malloc(sizeof(RSV_Node));
	newNode->left = Sentinel;
	newNode->right = Sentinel;
	newNode->p = Sentinel;
	memset(newNode->Key, 0, sizeof(newNode->Key));
	strcpy(newNode->Key, KEY);
	
	newNode->color = RED;
	return newNode;
}

bool RSV_RB_INSERT(RSV_node_ptr * Root, char *KEY, hotel_site_ptr DATA,int InputBudget) {
	RSV_node_ptr z = RSV_MakeNode(KEY);
	z->Path = DATA;
	z->InputBudget = InputBudget;
	RSV_node_ptr parentNode = Sentinel;
	RSV_node_ptr x = *Root;

	while (x != Sentinel) {
		parentNode = x;
		if (!strcmp(x->Key, KEY)) {
			return false;
		}
		if (strcmp(x->Key, KEY) > 0 )
			x = x->left;
		else
			x = x->right;
	}
	z->p = parentNode;
	if (parentNode == Sentinel)
		*Root = z;
	else if (strcmp(parentNode->Key, KEY) > 0)
		parentNode->left = z;
	else
		parentNode->right = z;
	RB_INSERT_FIXUP(Root, z);
	return true;
}

void RB_INSERT_FIXUP(RSV_node_ptr *Root, RSV_node_ptr z) {
	RSV_node_ptr y; // uncle node
	while (z->p->color == RED) { // z�� 1st insert�� ��쿡�� z->parent  == Sentinel �̱⿡ nullptr ���� �ȳ�...
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			// case 1 : z�� uncle(y)�� ���� red�� ���
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p; // z->p->p �� red�� �Ǿ��⿡ �� ��带 ������� RB_INSERT_FIXUP ���ν����� �ٽ� �����Ѵ�.
			}
			else {
				// case 2 : z�� uncle�� black �̰� z�� ������ �ڽ��� ���
				if (z == z->p->right) {
					z = z->p;
					LEFT_ROTATE(Root, z);
				}
				// case 3 : z�� uncle�� black �̰� z�� ���� �ڽ��� ���
				z->p->color = BLACK;
				z->p->p->color = RED;
				RIGHT_ROTATE(Root, z->p->p);
			}
		}
		else {
			y = z->p->p->left; // ��Ī���� uncle
							   // case 1 : z�� uncle(y)�� ���� red�� ���
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p; // z->p->p �� red�� �Ǿ��⿡ �� ��带 ������� RB_INSERT_FIXUP ���ν����� �ٽ� �����Ѵ�.
			}
			else {
				// case 2 : z�� uncle�� black �̰� z�� ������ �ڽ��� ���
				if (z == z->p->left) {
					z = z->p;
					RIGHT_ROTATE(Root, z);
				}
				// case 3 : z�� uncle�� black �̰� z�� ���� �ڽ��� ���
				z->p->color = BLACK;
				z->p->p->color = RED;
				LEFT_ROTATE(Root, z->p->p);
			}
		}
	}
	(*Root)->color = BLACK;
}


void LEFT_ROTATE(RSV_node_ptr * Root, RSV_node_ptr x) {
	RSV_node_ptr y = x->right;
	x->right = y->left; // move beta
	if (y->left != Sentinel)
		y->left->p = x;
	y->p = x->p; // swap x and y
	if (x->p == Sentinel)
		*Root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void RIGHT_ROTATE(RSV_node_ptr * Root, RSV_node_ptr y) {
	RSV_node_ptr x = y->left;
	y->left = x->right; // move beta
	if (x->right != Sentinel)
		x->right->p = y;
	x->p = y->p;// swap x and y
	if (y->p == Sentinel)
		*Root = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}


// DELETE =================================================
RSV_node_ptr RSV_RB_DELETE(RSV_node_ptr *root, char *KEY) {
	// 1) Search
	RSV_node_ptr delNode = RSV_TREE_SEARCH(*root, KEY);
	RSV_node_ptr y; // ��ü���
	RSV_node_ptr x; // ��ü����� �ڽĳ��
	if (delNode == Sentinel) {
		return Sentinel;
	}
	// 2) Delete
	if (delNode->left == Sentinel || delNode->right == Sentinel)
		y = delNode;
	else
		y = TREE_SUCCESSOR(delNode);
	if (y->left != Sentinel)
		x = y->left;
	else
		x = y->right;
	x->p = y->p;

	if (y->p == Sentinel)
		*root = x;
	else if (y == y->p->left)  //  ��ü����� �ڽĳ�带 ��ü����� �θ���� �����Ű�� (2)
		y->p->left = x;
	else
		y->p->right = x;
	if (delNode != y) {
		//delNode->Key = y->Key;
	}
	// RB_DELETE_FIXUP ==============
	if (y->color == BLACK)  // delNode�� black�̸� property�� �������� �� �� �� �ִ�.
		RB_DELETE_FIXUP(root, x);
	return y;
}

void RB_DELETE_FIXUP(RSV_node_ptr *root, RSV_node_ptr x) {
	RSV_node_ptr w;
	while (x != *root && x->color == BLACK) {
		if (x == x->p->left) {
			w = x->p->right;
			if (w->color == RED) { // Case 1 ===================
				w->color = BLACK;
				x->p->color = RED;
				LEFT_ROTATE(root, x->p);
				w = x->p->right;
			} // case 1�� ���Ͽ� case 2, 3, 4 �� �ϳ��� ������ �ٲ��ش�.

			if (w->left->color == BLACK && w->right->color == BLACK) { // Case 2
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->right->color == BLACK) { // case 3
					w->left->color = BLACK;
					w->color = RED;
					RIGHT_ROTATE(root, w);
					w = x->p->right;
				}
				// case 4 -- x�� �ִ� ��ο��� bh�� 1�� ����.
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				LEFT_ROTATE(root, x->p);
				x = *root;
			}
		}
		else {
			w = x->p->left;
			if (w->color == RED) { // Case 1 ===================
				w->color = BLACK;
				x->p->color = RED;
				RIGHT_ROTATE(root, x->p);
				w = x->p->left;
			} // case 1�� ���Ͽ� case 2, 3, 4 �� �ϳ��� ������ �ٲ��ش�.
			if (w->right->color == BLACK && w->left->color == BLACK) { // Case 2
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) { // case 3
					w->right->color = BLACK;
					w->color = RED;
					LEFT_ROTATE(root, w);
					w = x->p->left;
				}
				// case 4 -- x�� �ִ� ��ο��� bh�� 1�� ����.
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				RIGHT_ROTATE(root, x->p);
				x = *root;
			}
		}
	}
	x->color = BLACK;
}

// ===================================================================
RSV_node_ptr RSV_TREE_SEARCH(RSV_node_ptr root, char *KEY) {
	if (root == Sentinel)
		return Sentinel;
	if (!strcmp(KEY, root->Key))
		return root;
	else if (strcmp(root->Key, KEY) < 0)
		return RSV_TREE_SEARCH(root->right, KEY);
	else
		return RSV_TREE_SEARCH(root->left, KEY);
}

RSV_node_ptr TREE_SUCCESSOR(RSV_node_ptr target) {
	if (target->right != Sentinel)
		return TREE_MIN(target->right);
	RSV_node_ptr p = target->p;
	while (p != Sentinel && p->right == target) {
		target = p;
		p = target->p;
	}
	return p;
}

RSV_node_ptr TREE_MIN(RSV_node_ptr root) {
	while (root->left != Sentinel)
		root = root->left;
	return root;
}

void MakeSentinel() {
	Sentinel = (RSV_node_ptr)malloc(sizeof(RSV_Node));
	Sentinel->left = NULL;
	Sentinel->right = NULL;
	Sentinel->p = NULL;
	Sentinel->color = BLACK;
}



