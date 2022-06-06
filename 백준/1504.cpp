#include <bits/stdc++.h>

using namespace std;

#define INF 2000000001

vector<vector<pair<int,int>>> con(801, vector<pair<int,int>>());

int N, E, v1, v2;

void input() {
	cin >> N >> E;
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		con[a].push_back({ c,b });
		con[b].push_back({ c,a });
	}
	cin >> v1 >> v2;
}

long long dijk(int s, int e) {
	vector<long long> dist(801, INF);
	dist[s] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({ 0, s });

	while (!pq.empty()) {
		long long cost = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();


		for (auto v : con[cur]) {
			if (dist[v.second] > cost + v.first) {
				dist[v.second] = cost + v.first;
				pq.push({ -dist[v.second], v.second });
			}
		}
	}

	return dist[e];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	input();
	long long answer = min(dijk(1,v1)+dijk(v1,v2)+dijk(v2,N), dijk(1, v2) + dijk(v2, v1) + dijk(v1, N));
	if (answer >= INF)
		answer = -1;
	cout << answer;

	return 0;
}