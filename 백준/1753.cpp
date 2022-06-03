#include <bits/stdc++.h>

using namespace std;

#define INF 200001

vector<int> dist(20001, INF);
vector<pair<int, int>> vertex[20001];
int V, E, K;

void input() {
	cin >> V >> E >> K;
	for (int i = 0; i < E; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		vertex[u].push_back({ v,w });
	}
}

void dijk() {
	priority_queue<pair<int, int>> pq;
	dist[K] = 0;
	pq.push({ 0, K });

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		for (auto next : vertex[cur]) {
			int nCost = next.second;
			if (dist[next.first] > cost + nCost) {
				dist[next.first] = cost + nCost;
				pq.push({ -dist[next.first], next.first });
			}
		}
	}
}

void solve() {
	dijk();
	for (int i = 1; i <= V; i++) {
		if (dist[i] != INF) cout << dist[i] << '\n';
		else cout << "INF" << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}