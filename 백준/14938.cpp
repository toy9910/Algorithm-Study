#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX

vector<int> dist(105, INF);
vector<pair<int, int>> adj[105];
vector<int> item(105);
int n, m, r, t, ans;

void input() {
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) {
		cin >> item[i];
	}

	for (int i = 0; i < r; i++) {
		int a, b, l;
		cin >> a >> b >> l;

		adj[a].push_back({ l, b });
		adj[b].push_back({ l, a });
	}
}


void dijk() {
	for (int i = 1; i <= n; i++) {
		priority_queue<pair<int, int>> pq;
		dist[i] = 0;
		pq.push({ 0,i });

		while (!pq.empty()) {
			int cost = -pq.top().first;
			int cur = pq.top().second;
			pq.pop();

			if (dist[cur] < cost) continue;
			for (auto nxt : adj[cur]) {
				if (dist[nxt.second] > cost + nxt.first and cost + nxt.first <= m) {
					dist[nxt.second] = cost + nxt.first;
					pq.push({ -dist[nxt.second], nxt.second });
				}
			}
		}

		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (dist[j] != INF) sum += item[j];
		ans = max(ans, sum);
		fill(dist.begin(), dist.end(), INF);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	dijk();

	return 0;
}