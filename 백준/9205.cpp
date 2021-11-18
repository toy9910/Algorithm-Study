#include <bits/stdc++.h>

using namespace std;

vector<bool> visited(105, false); // �湮 ǥ��
vector<vector<int>> adj(105, vector<int>()); // ������ spot ǥ�� -> adj[i]�� { 0,2,3 } �� ������ spot[i]�� spot[0], spot[2], spot[3] ���� �� �� �ִٴ� ��
int t, n;

int func(int depth) {
	// n+1��° spot(������)�� ����
	if (depth == n + 1)
		return 1;

	// ���� spot���κ��� ����� spot �湮
	for (auto i : adj[depth]) {
		if (!visited[i]) {
			visited[i] = true;
			if (func(i))
				return 1;
		}
	}

	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;

	while (t--) {
		cin >> n;

		// �迭 �ʱ�ȭ
		fill(visited.begin(), visited.end(), false);
		for (int i = 0; i < 105; i++)
			adj[i].clear();
		vector<pair<int, int>> spot(105);

		for (int i = 0; i < n + 2; i++) 
			cin >> spot[i].first >> spot[i].second;

		// ���ְ� �ٴ� ���� �ʰ� �� �� �ִ� ��� üũ
		for (int i = 0; i < n + 2; i++) {
			for (int j = i + 1; j < n + 2; j++) {
				if (abs(spot[i].first - spot[j].first) + abs(spot[i].second - spot[j].second) <= 1000) {
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}
		
		visited[0] = true;
		if (func(0))
			cout << "happy\n";
		else
			cout << "sad\n";
	}

	return 0;
}