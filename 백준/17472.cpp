#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<int> p(10, -1);
vector<tuple<int, int, int>> edge;
pair<int, int> iPos[7];
int board[15][15], N, M, ic, answer;

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

bool is_diff_group(int u, int v) {
	u = find(u); v = find(v);
	if (u == v) return false;
	if (p[u] == p[v]) p[u]--;
	if (p[u] < p[v]) p[v] = u;
	else p[u] = v;
	return true;
}

void change() {
	vector<vector<bool>> visited(15, vector<bool>(15, false));
	int index = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0 or visited[i][j]) continue;
			queue<pair<int, int>> q;
			visited[i][j] = true;
			q.push({ i,j });
			iPos[index] = { i,j };
			board[i][j] = index;

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M or visited[xpos][ypos] or board[xpos][ypos] != 1) continue;
					board[xpos][ypos] = index;
					visited[xpos][ypos] = true;
					q.push({ xpos, ypos });
				}
			}
			index++;
		}
	}
	ic = index - 1;
}

bool check(pair<int, int> p) {
	if (p.first - 1 >= 0 and board[p.first - 1][p.second] == 0)
		return true;
	if (p.second - 1 >= 0 and board[p.first][p.second - 1] == 0)
		return true;
	if (p.first + 1 < N and board[p.first + 1][p.second] == 0)
		return true;
	if (p.second + 1 < M and board[p.first][p.second + 1] == 0)
		return true;
	return false;
}

void setEdge() {
	vector<vector<bool>> visited(15, vector<bool>(15, false));

	for (int i = 1; i <= ic; i++) {
		queue<pair<int, int>> q;
		visited[iPos[i].first][iPos[i].second] = true;
		q.push(iPos[i]);

		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			for (int k = 0; k < 4; k++) {
				int xpos = cur.first + dx[k];
				int ypos = cur.second + dy[k];
				if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M or visited[xpos][ypos] or board[cur.first][cur.second] != board[xpos][ypos]) continue;
				q.push({ xpos, ypos });
				visited[xpos][ypos] = true;
			}

			if (!check(cur)) continue;

			for (int k = 0; k < 4; k++) {
				int xpos = cur.first + dx[k];
				int ypos = cur.second + dy[k];
				int dist = 0;

				if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M or board[cur.first][cur.second] == board[xpos][ypos]) continue;
				while (xpos >= 0 and xpos < N and ypos >= 0 and ypos < M and board[xpos][ypos] == 0) {
					dist++;
					xpos += dx[k];
					ypos += dy[k];
				}
				if (dist < 2 or xpos < 0 or xpos >= N or ypos < 0 or ypos >= M) continue;
				edge.push_back({ dist, board[cur.first][cur.second], board[xpos][ypos] });
			}
		}
	}
}

void solve() {
	change();
	setEdge();
	sort(edge.begin(), edge.end());

	int cnt = 0;

	for (auto e : edge) {
		int start, dest, cost;
		tie(cost, start, dest) = e;
		if (!is_diff_group(start, dest)) continue;
		cnt++;
		answer += cost;
		if (cnt == ic - 1) break;
	}
	if (answer == 0 or cnt != ic - 1) answer = -1;
	cout << answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}