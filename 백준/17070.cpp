#include <bits/stdc++.h>

using namespace std;

int dx[] = { 0,1,1 };
int dy[] = { 1,1,0 };

int board[18][18], N, answer;

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

void dfs(pair<int, int> cur, int dir) {
	if (cur.first == N and cur.second == N) {
		answer++;
		return;
	}

	switch (dir) {
	case 0:
		for (int d = 0; d <= 1; d++) {
			int xpos = cur.first + dx[d];
			int ypos = cur.second + dy[d];
			if (d == 1) {
				if (xpos > N or ypos > N or board[xpos][ypos] == 1 or board[xpos - 1][ypos] == 1 or board[xpos][ypos - 1] == 1) continue;
			}
			else {
				if (xpos > N or ypos > N or board[xpos][ypos] == 1) continue;
			}
			dfs(make_pair(xpos, ypos), d);
		}
		break;
	case 1:
		for (int d = 0; d <= 2; d++) {
			int xpos = cur.first + dx[d];
			int ypos = cur.second + dy[d];

			if (d == 1) {
				if (xpos > N or ypos > N or board[xpos][ypos] == 1 or board[xpos - 1][ypos] == 1 or board[xpos][ypos - 1] == 1) continue;
			}
			else {
				if (xpos > N or ypos > N or board[xpos][ypos] == 1) continue;
			}
			dfs(make_pair(xpos, ypos), d);
		}
		break;
	case 2:
		for (int d = 1; d <= 2; d++) {
			int xpos = cur.first + dx[d];
			int ypos = cur.second + dy[d];
			if (d == 1) {
				if (xpos > N or ypos > N or board[xpos][ypos] == 1 or board[xpos - 1][ypos] == 1 or board[xpos][ypos - 1] == 1) continue;
			}
			else {
				if (xpos > N or ypos > N or board[xpos][ypos] == 1) continue;
			}
			dfs(make_pair(xpos, ypos), d);
		}
		break;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	dfs(make_pair(1, 2), 0);
	cout << answer;

	return 0;
}