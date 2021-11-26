#include <bits/stdc++.h>

using namespace std;

struct node {
	char a;
	node* right;
	node* left;
};

vector<node> nodes(27);
int N;

void preorder(node root) {
	cout << root.a;
	if(root.left != NULL)
		preorder(*root.left);
	if(root.right != NULL)
		preorder(*root.right);
}

void inorder(node root) {
	if (root.left != NULL)
		inorder(*root.left);
	cout << root.a;
	if (root.right != NULL)
		inorder(*root.right);
}

void postorder(node root) {
	if (root.left != NULL)
		postorder(*root.left);
	if (root.right != NULL)
		postorder(*root.right);
	cout << root.a;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;


	while (N--) {
		char a;
		cin >> a;

		nodes[a - 'A'].a = a;

		char left, right;
		cin >> left >> right;

		if (left != '.')
			nodes[a - 'A'].left = &nodes[left - 'A'];
		else
			nodes[a - 'A'].left = NULL;

		if (right != '.')
			nodes[a - 'A'].right = &nodes[right - 'A'];
		else
			nodes[a - 'A'].right = NULL;
	}

	preorder(nodes[0]);
	cout << '\n';
	inorder(nodes[0]);
	cout << '\n';
	postorder(nodes[0]);

	return 0;
}