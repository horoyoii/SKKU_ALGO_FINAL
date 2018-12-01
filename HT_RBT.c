#include"headerFiles.h"


HT_RBnode_ptr HT_MakeRBT(void){
	return HT_Sentinel;
}

HT_RBnode_ptr HT_MakeRBNode(int KEY, int hotelNum) {
	HT_RBnode_ptr newNode = (HT_RBnode_ptr)malloc(sizeof(HT_RBNode));
	newNode->left = HT_Sentinel;
	newNode->right = HT_Sentinel;
	newNode->p = HT_Sentinel;
	newNode->Key = KEY;
	newNode->Hotel_Num = hotelNum;
	newNode->color = RED;
	return newNode;
}

bool HT_RB_INSERT(HT_RBnode_ptr * Root, int KEY, int hotelNum) {
	HT_RBnode_ptr z = HT_MakeRBNode(KEY, hotelNum);
	HT_RBnode_ptr parentNode = HT_Sentinel;
	HT_RBnode_ptr x = *Root;

	while (x != HT_Sentinel) {
		parentNode = x;
		if (x->Key == KEY) {
			return false;
		}
		if (KEY < x->Key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = parentNode;
	if (parentNode == HT_Sentinel)
		*Root = z;
	else if (parentNode->Key < KEY)
		parentNode->right = z;
	else
		parentNode->left = z;
	HT_RB_INSERT_FIXUP(Root, z);
	return true;
}

void HT_RB_INSERT_FIXUP(HT_RBnode_ptr *Root, HT_RBnode_ptr z) {
	HT_RBnode_ptr y; // uncle node
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
					HT_LEFT_ROTATE(Root, z);
				}
				// case 3 : z�� uncle�� black �̰� z�� ���� �ڽ��� ���
				z->p->color = BLACK;
				z->p->p->color = RED;
				HT_RIGHT_ROTATE(Root, z->p->p);
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
					HT_RIGHT_ROTATE(Root, z);
				}
				// case 3 : z�� uncle�� black �̰� z�� ���� �ڽ��� ���
				z->p->color = BLACK;
				z->p->p->color = RED;
				HT_LEFT_ROTATE(Root, z->p->p);
			}
		}
	}
	(*Root)->color = BLACK;
}

void HT_LEFT_ROTATE(HT_RBnode_ptr * Root, HT_RBnode_ptr x) {
	HT_RBnode_ptr y = x->right;
	x->right = y->left; // move beta
	if (y->left != HT_Sentinel)
		y->left->p = x;
	y->p = x->p; // swap x and y
	if (x->p == HT_Sentinel)
		*Root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void HT_RIGHT_ROTATE(HT_RBnode_ptr * Root, HT_RBnode_ptr y) {
	HT_RBnode_ptr x = y->left;
	y->left = x->right; // move beta
	if (x->right != HT_Sentinel)
		x->right->p = y;
	x->p = y->p;// swap x and y
	if (y->p == HT_Sentinel)
		*Root = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}


// DELETE =================================================
HT_RBnode_ptr HT_RB_DELETE(HT_RBnode_ptr *root, int KEY) {
	// 1) Search
	HT_RBnode_ptr delNode = HT_TREE_SEARCH(*root, KEY);
	HT_RBnode_ptr y; // ��ü���
	HT_RBnode_ptr x; // ��ü����� �ڽĳ��
	if (delNode == HT_Sentinel) {
			return HT_Sentinel;
	}
	// 2) Delete
	if (delNode->left == HT_Sentinel || delNode->right == HT_Sentinel)
		y = delNode;
	else
		y = HT_TREE_SUCCESSOR(delNode);
	if (y->left != HT_Sentinel)
		x = y->left;
	else
		x = y->right;
	x->p = y->p;

	if (y->p == HT_Sentinel)
		*root = x;
	else if (y == y->p->left)  //  ��ü����� �ڽĳ�带 ��ü����� �θ���� �����Ű�� (2)
		y->p->left = x;
	else
		y->p->right = x;
	if (delNode != y)
		delNode->Key = y->Key;
	// RB_DELETE_FIXUP ==============
	if (y->color == BLACK)  // delNode�� black�̸� property�� �������� �� �� �� �ִ�.
		HT_RB_DELETE_FIXUP(root, x);
	return y;
}

void HT_RB_DELETE_FIXUP(HT_RBnode_ptr *root, HT_RBnode_ptr x) {
	HT_RBnode_ptr w;
	while (x != *root && x->color == BLACK) {
		if (x == x->p->left) {
			w = x->p->right;
			if (w->color == RED) { // Case 1 ===================
				w->color = BLACK;
				x->p->color = RED;
				HT_LEFT_ROTATE(root, x->p);
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
					HT_RIGHT_ROTATE(root, w);
					w = x->p->right;
				}
				// case 4 -- x�� �ִ� ��ο��� bh�� 1�� ����.
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				HT_LEFT_ROTATE(root, x->p);
				x = *root;
			}
		}
		else {
			w = x->p->left;
			if (w->color == RED) { // Case 1 ===================
				w->color = BLACK;
				x->p->color = RED;
				HT_RIGHT_ROTATE(root, x->p);
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
					HT_LEFT_ROTATE(root, w);
					w = x->p->left;
				}
				// case 4 -- x�� �ִ� ��ο��� bh�� 1�� ����.
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				HT_RIGHT_ROTATE(root, x->p);
				x = *root;
			}
		}
	}
	x->color = BLACK;
}

// ===================================================================
HT_RBnode_ptr HT_TREE_SEARCH(HT_RBnode_ptr root, int KEY) {
	if (root == HT_Sentinel)
		return HT_Sentinel;
	if (root->Key == KEY)
		return root;
	else if (root->Key < KEY)
		return HT_TREE_SEARCH(root->right, KEY);
	else
		return HT_TREE_SEARCH(root->left, KEY);
}

HT_RBnode_ptr HT_TREE_SUCCESSOR(HT_RBnode_ptr target) {
	if (target->right != HT_Sentinel)
		return HT_TREE_MIN(target->right);
	HT_RBnode_ptr p = target->p;
	while (p != HT_Sentinel && p->right == target) {
		target = p;
		p = target->p;
	}
	return p;
}

HT_RBnode_ptr HT_TREE_PREDECESSOR(HT_RBnode_ptr target) {
	if (target->left != HT_Sentinel&&target->left->Key != -1)
		return HT_TREE_MAX(target->left);
	HT_RBnode_ptr p = target->p;
	while (p != HT_Sentinel && p->left == target) {
		target = p;
		p = target->p;
	}
	return p;
}

HT_RBnode_ptr HT_TREE_MAX(HT_RBnode_ptr root) {
	while (root->right != HT_Sentinel && root->right->Key != -1)
		root = root->right;
	return root;
}

HT_RBnode_ptr HT_TREE_MIN(HT_RBnode_ptr root) {
	while (root->left != HT_Sentinel && root->left->Key != -1)
		root = root->left;
	return root;
}

void HT_MakeSentinel() {
	HT_Sentinel = (HT_RBnode_ptr)malloc(sizeof(HT_RBNode));
	HT_Sentinel->Key = -1;
	HT_Sentinel->left = NULL;
	HT_Sentinel->right = NULL;
	HT_Sentinel->p = NULL;
	HT_Sentinel->color = BLACK;
}

