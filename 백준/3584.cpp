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

		// 마지막 줄의 두 노드
		int num1, num2;
		cin >> num1 >> num2;

		// 두 노드의 부모들을 저장할 큐
		queue<int> pnum1, pnum2;

		// 첫 번째 노드와 부모들 저장
		node cur = nodes[num1];
		pnum1.push(cur.num);
		while (cur.parent != NULL) {
			pnum1.push(cur.parent->num);
			cur = *cur.parent;
		}

		// 두 번째 노드와 부모들 저장
		cur = nodes[num2];
		pnum2.push(cur.num);
		while (cur.parent != NULL) {
			pnum2.push(cur.parent->num);
			cur = *cur.parent;
		}

		// 만약 두 노드의 부모 수가 다를 경우 부모 수를 같게 해준다.
		// 예를 들어, { 15, 6, 4, 8} 과 { 3, 16, 10, 4, 8} 일 경우
		// 한 칸씩 밀려서 안 맞기 때문
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

		// 맨 앞 하나씩 빼면서 비교
		while (pnum1.front() != pnum2.front()) {
			pnum1.pop();
			pnum2.pop();
		}

		cout << pnum1.front() << '\n';
	}

	

	return 0;
}