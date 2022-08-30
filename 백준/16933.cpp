#include <bits/stdc++.h>

using namespace std;

#define INF 987654321

int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int N, M, K, board[1001][1001];
bool visited[1001][1001][11];

void input() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			board[i][j + 1] = str[j] - '0';
		}
	}
}

void solve() {
	queue<tuple<int, int, int, int, int>> q;
	q.push({ 1,1,1,0,0 });
	visited[1][1][0] = true;

	while (!q.empty()) {
		int x, y, d, b, n;
		tie(x, y, d, b, n) = q.front();
		q.pop();

		if (x == N and y == M) {
			cout << d;
			return;
		}

		for (int k = 0; k < 4; k++) {
			int xpos = x + dx[k], ypos = y + dy[k];
			if (xpos < 1 or xpos > N or ypos < 1 or ypos > M) continue;
			if (board[xpos][ypos]) {
				if (b == K or visited[xpos][ypos][b+1]) continue;

				if (n == 1) {
					q.push(make_tuple(x, y,d+1, b, 0));
				}
				else {
					visited[xpos][ypos][b + 1] = true;
					q.push(make_tuple(xpos, ypos, d + 1, b + 1, 1));
				}
			}
			else {
				if (visited[xpos][ypos][b]) continue;
				visited[xpos][ypos][b] = true;
				q.push(make_tuple(xpos, ypos, d + 1, b, (n + 1) % 2));
			}
		}
	}
	cout << -1;
	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}