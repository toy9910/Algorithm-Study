#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(50, vector<int>(50));
vector<pair<int, int>> virus;
vector<int> tmp;
int N, M, ans = INT_MAX;

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) virus.push_back({ i,j });
		}
	}
}

int getCount() {
	int max_dist = 0;
	vector<vector<int>> dist(50, vector<int>(50, -1));
	queue<pair<int, int>> q;

	for (auto n : tmp) {
		q.push(virus[n]);
		dist[virus[n].first][virus[n].second] = 0;
	}
	
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) {
			int xpos = cur.first + dx[k];
			int ypos = cur.second + dy[k];

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N or board[xpos][ypos] == 1 or dist[xpos][ypos] >= 0) continue;
			dist[xpos][ypos] = dist[cur.first][cur.second] + 1;
			max_dist = max(max_dist, dist[xpos][ypos]);
			q.push({ xpos,ypos });
		}
	}

	bool isAllVirus = true;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 1 and dist[i][j] == -1) {
				isAllVirus = false;
				break;
			}
		}
	}

	if (!isAllVirus)
		max_dist = INT_MAX;
	return max_dist;
}

void comb(int depth, int next) {
	if (depth == M) {
		
		ans = min(ans, getCount());
		return;
	}

	for (int i = next; i < virus.size(); i++) {
		tmp.push_back(i);
		comb(depth + 1, i + 1);
		tmp.pop_back();
	}
}

void solve() {
	comb(0, 0);
	if (ans == INT_MAX) ans = -1;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();
	

	return 0;
}