#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<char>> board(20, vector<char>(20));
vector<pair<int, int>> trash;
vector<int> tmp;
vector<bool> visited(10);
int dist[20][20][20][20];

pair<int, int> start;
int w, h, ans;

int getDist(pair<int, int> st, pair<int, int> ed) {
	vector<vector<int>> d(20, vector<int>(20, -1));
	queue<pair<int, int>> q;

	d[st.first][st.second] = 0;
	q.push(st);

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		if (cur == ed) break;

		for (int k = 0; k < 4; k++) {
			int xpos = cur.first + dx[k];
			int ypos = cur.second + dy[k];

			if (xpos < 0 or xpos >= h or ypos < 0 or ypos >= w or d[xpos][ypos] > -1 or board[xpos][ypos] == 'x') continue;
			d[xpos][ypos] = d[cur.first][cur.second] + 1;
			q.push({ xpos,ypos });
		}
	}

	dist[st.first][st.second][ed.first][ed.second] = d[ed.first][ed.second];
	return d[ed.first][ed.second];
}

void perm(int depth, int distance, pair<int,int> curPos) {
	if (depth == trash.size()) {
		ans = min(ans, distance);
		return;
	}

	if (distance == -1) 
		return;
	

	for (int i = 0; i < trash.size(); i++) {
		if (!visited[i]) {
			visited[i] = true;
			tmp.push_back(i);
			int result;
			if (dist[curPos.first][curPos.second][trash[i].first][trash[i].second] == 0)
				result = getDist(curPos, trash[i]);
			else
				result = dist[curPos.first][curPos.second][trash[i].first][trash[i].second];

			if (result == -1) {
				ans = -1;
				return;
			}
			
			perm(depth + 1, distance + result, trash[i]);
			visited[i] = false;
			tmp.pop_back();
		}
	}
}

void solve() {
	perm(0, 0, start);
	cout << ans << '\n';
}


void input() {
	while (true) {
		cin >> w >> h;

		if (w == 0 and h == 0) break;
		
		ans = INT_MAX;
		trash.clear();
		tmp.clear();
		fill(visited.begin(), visited.end(), false);

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> board[i][j];
				if (board[i][j] == '*') trash.push_back({ i,j });
				else if (board[i][j] == 'o') 
					start = { i,j };
			}
		}

		for (int a = 0; a < h; a++) {
			for (int b = 0; b < w; b++) {
				for (int c = 0; c < h; c++) {
					for (int d = 0; d < w; d++) {
						dist[a][b][c][d] = 0;
					}
				}
			}
		}
		solve();
	}
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();

	return 0;
}