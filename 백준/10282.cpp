#include <bits/stdc++.h>

using namespace std;

#define INF 987654321

vector<pair<int, int>> edge[10005];
int t, n, d, c, a, b, s, answer;

void input() {
	for (int i = 0; i < n; i++) 
		edge[i].clear();
	
	cin >> n >> d >> c;
	for (int i = 0; i < d; i++) {
		cin >> a >> b >> s;
		edge[b].push_back(make_pair(a, s));
	}
}

void solve() {
	answer = 0;

	vector<int> ti(10005, INF);
	vector<bool> dead(10005, false);
	

	priority_queue<pair<int,int>> pq;
	pq.push({ 0, c });
	ti[c] = 0;

	while (!pq.empty()) {
		int times = -pq.top().first, cur = pq.top().second;
		pq.pop();

		for (auto e : edge[cur]) {
			if (ti[e.first] > times + e.second) {
				ti[e.first] = times + e.second;
				pq.push({ -ti[e.first], e.first });
			}
		}
	}


	int tt = 0, counts = 1;
	for (int i = 1; i <= n; i++) {
		if (ti[i] == INF) continue;
		tt = max(tt, ti[i]);
		counts++;
	}
	cout << counts << " " << tt << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for (int i = 0; i < t; i++) {
		input();
		solve();
	}

	return 0;
}