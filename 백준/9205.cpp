#include <bits/stdc++.h>

using namespace std;

vector<bool> visited(105, false); // 방문 표시
vector<vector<int>> adj(105, vector<int>()); // 인접한 spot 표시 -> adj[i]에 { 0,2,3 } 이 있으면 spot[i]는 spot[0], spot[2], spot[3] 으로 갈 수 있다는 뜻
int t, n;

int func(int depth) {
	// n+1번째 spot(목적지)에 도달
	if (depth == n + 1)
		return 1;

	// 현재 spot으로부터 연결된 spot 방문
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

		// 배열 초기화
		fill(visited.begin(), visited.end(), false);
		for (int i = 0; i < 105; i++)
			adj[i].clear();
		vector<pair<int, int>> spot(105);

		for (int i = 0; i < n + 2; i++) 
			cin >> spot[i].first >> spot[i].second;

		// 맥주가 바닥 나지 않고 갈 수 있는 경우 체크
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