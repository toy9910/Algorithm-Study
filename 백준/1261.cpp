#include <bits/stdc++.h>

using namespace std;

#define INF 123456789

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(101, vector<int>(101));
vector<vector<int>> dist(101, vector<int>(101, INF));
int N, M;

void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			board[i][j] = str[j] - '0';
		}
	}
}

void solve() {
	if (N == 1 and M == 1) {
		cout << board[M - 1][N - 1];
		return;
	}

	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({ 0,{0,0} });

	while (!pq.empty()) {
		int cost = -pq.top().first;
		auto cur = pq.top().second;
		pq.pop();

		for (int k = 0; k < 4; k++) {
			int xpos = cur.first + dx[k];
			int ypos = cur.second + dy[k];

			if (xpos < 0 or xpos >= M or ypos < 0 or ypos >= N) continue;
			if (dist[xpos][ypos] > cost + board[cur.first][cur.second]) {
				dist[xpos][ypos] = cost + board[cur.first][cur.second];
				pq.push({ -dist[xpos][ypos], {xpos, ypos} });
			}
		}
	}
	cout << dist[M - 1][N - 1];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}