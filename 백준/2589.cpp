#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<char>> board(51, vector<char>(51));
int N, M, answer;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	answer = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < M; j++) {
			board[i][j] = str[j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 'W')
				continue;

			queue<pair<int, int>> q;
			vector<vector<bool>> visited(51, vector<bool>(51, false));
			vector<vector<int>> dis(51, vector<int>(51, 0));
			visited[i][j] = true;
			q.push({ i,j });

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
						continue;
					if (board[xpos][ypos] == 'W' or visited[xpos][ypos])
						continue;
					dis[xpos][ypos] = dis[cur.first][cur.second] + 1;
					visited[xpos][ypos] = true;
					q.push({ xpos,ypos });
					answer = max(answer, dis[xpos][ypos]);
				}
			}
		}
	}

	cout << answer;

	return 0;
}