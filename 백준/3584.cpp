#include <bits/stdc++.h>

using namespace std;

struct node {
	node* parent;
	int num;
};


int T;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		vector<node> nodes(10005);

		for (int i = 0; i < N - 1; i++) {
			int parent, child;
			cin >> parent >> child;
			
			nodes[child].num = child;
			nodes[child].parent = &nodes[parent];
			nodes[parent].num = parent;
		}

		// ������ ���� �� ���
		int num1, num2;
		cin >> num1 >> num2;

		// �� ����� �θ���� ������ ť
		queue<int> pnum1, pnum2;

		// ù ��° ���� �θ�� ����
		node cur = nodes[num1];
		pnum1.push(cur.num);
		while (cur.parent != NULL) {
			pnum1.push(cur.parent->num);
			cur = *cur.parent;
		}

		// �� ��° ���� �θ�� ����
		cur = nodes[num2];
		pnum2.push(cur.num);
		while (cur.parent != NULL) {
			pnum2.push(cur.parent->num);
			cur = *cur.parent;
		}

		// ���� �� ����� �θ� ���� �ٸ� ��� �θ� ���� ���� ���ش�.
		// ���� ���, { 15, 6, 4, 8} �� { 3, 16, 10, 4, 8} �� ���
		// �� ĭ�� �з��� �� �±� ����
		if (pnum1.size() > pnum2.size()) {
			int n = pnum1.size() - pnum2.size();
			for (int i = 0; i < n; i++) {
				pnum1.pop();
			}
		}
		else if (pnum1.size() < pnum2.size()) {
			int n = pnum2.size() - pnum1.size();
			for (int i = 0; i < n; i++) {
				pnum2.pop();
			}
		}

		// �� �� �ϳ��� ���鼭 ��
		while (pnum1.front() != pnum2.front()) {
			pnum1.pop();
			pnum2.pop();
		}

		cout << pnum1.front() << '\n';
	}

	

	return 0;
}