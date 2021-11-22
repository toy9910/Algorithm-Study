#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(501, vector<int>(501)); // ����
vector<vector<int>> DP(501, vector<int>(501, -1)); // (i, j)���� ������������ ����� ��
int N, M, answer;

int DFS(int x, int y) {
	if (x == N - 1 and y == M - 1)
		return 1;

	// �̹� �湮�� ���� �־� ����� ���� ����� �س��� ���
	if (DP[x][y] > -1)
		return DP[x][y];

	// ����� �� ���
	DP[x][y] = 0;
	for (int k = 0; k < 4; k++) {
		int xpos = x + dx[k];
		int ypos = y + dy[k];

		if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
			continue;
		if(board[x][y] > board[xpos][ypos])
			DP[x][y] += DFS(xpos, ypos);
	}
	return DP[x][y];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}

	answer = DFS(0, 0);
	cout << DP[0][0];

	return 0;
}