#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> vertex[1001];
int gd[1001];
vector<int> cd(1001, 10000001);
int N, M, X;

void input() {
	cin >> N >> M >> X;
	for (int i = 0; i < M; i++) {
		int start, end, T;
		cin >> start >> end >> T;

		vertex[start].push_back({ end, T });
	}
}

void goDijk() {
	for (int i = 1; i <= N; i++) {
		priority_queue<pair<int, int>> pq;
		vector<int> dist(1001, 10000001);
		dist[i] = 0;

		pq.push({ 0, i });
		while (!pq.empty()) {
			int cur = pq.top().second;
			int cost = -pq.top().first;
			pq.pop();

			for (auto next : vertex[cur]) {
				if (dist[next.first] > cost + next.second) {
					dist[next.first] = cost + next.second;
					pq.push({ -dist[next.first], next.first });
				}
			}
		}
		gd[i] = dist[X];
	}
}

void comeDijk() {
	priority_queue<pair<int, int>> pq;
	cd[X] = 0;

	pq.push({ 0, X });
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();

		for (auto next : vertex[cur]) {
			if (cd[next.first] > cost + next.second) {
				cd[next.first] = cost + next.second;
				pq.push({ -cd[next.first], next.first });
			}
		}
	}
}

void solve() {
	goDijk();
	comeDijk();
	
	int answer = -1;
	for (int i = 1; i <= N; i++) 
		answer = max(answer, gd[i] + cd[i]);

	cout << answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}