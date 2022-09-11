#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

int board[51][51];
int n;


void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			board[i][j + 1] = str[j] - '0';
		}
	}
}

void solve() {
	vector<vector<int>> visited(51, vector<int>(51, 987654321));
	queue<pair<int, int>> q;
	q.push({ 1,1 });
	visited[1][1] = 0;

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) {
			int xpos = cur.first + dx[k];
			int ypos = cur.second + dy[k];

			if (xpos < 1 or xpos > n or ypos < 1 or ypos > n) continue;
			if (board[xpos][ypos] == 1) {
				if (visited[xpos][ypos] > visited[cur.first][cur.second]) {
					visited[xpos][ypos] = visited[cur.first][cur.second];
					q.push({ xpos,ypos });
				}
			}
			else {
				if (visited[xpos][ypos] > visited[cur.first][cur.second] + 1) {
					visited[xpos][ypos] = visited[cur.first][cur.second] + 1;
					q.push({ xpos,ypos });
				}
			}
		}
	}

	cout << visited[n][n];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}