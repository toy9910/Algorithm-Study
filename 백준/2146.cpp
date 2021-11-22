#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(101, vector<int>(101)); // 지도
int N, answer;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	int lcount = 0; // 섬의 갯수

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 해당 칸이 육지일 경우
			if (board[i][j] == 1) {
				queue<pair<int, int>> q;
				lcount++;
				// lcount를 더해 섬을 구별해준다.
				// 1번째로 발견된 섬일 경우 lcount인 1을 더하여 2로 만들고
				// 2번째로 발견된 섬일 경우 lcount인 2를 더하여 해당 칸들을 3으로 만든다.
				board[i][j] += lcount;
				q.push(make_pair(i, j));

				while (!q.empty()) {
					auto cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int xpos = cur.first + dx[k];
						int ypos = cur.second + dy[k];

						if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
							continue;
						// 이미 칸을 방문하여 업데이트한 경우와 바다인 경우는 continue 한다.
						if (board[xpos][ypos] > 1 or board[xpos][ypos] == 0)
							continue;
						board[xpos][ypos] += lcount;
						q.push({ xpos,ypos });
					}
				}
			}
		}
	}

	answer = 1000000;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 바다인 경우 continue
			if (board[i][j] == 0)
				continue;
			// 해당 위치가 가장자리인지 판별
			bool isbound = false;
			for (int k = 0; k < 4; k++) {
				int xpos = i + dx[k];
				int ypos = j + dy[k];

				if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
					continue;
				// 한 곳이라도 바다가 있으면 가장자리이므로 break
				if (board[xpos][ypos] == 0) {
					isbound = true;
					break;
				}
			}
			// 가장자리가 아니면 continue
			if (!isbound)
				continue;

			queue<pair<int, int>> q;
			vector<vector<int>> dis(101, vector<int>(101, 0)); // 시작 위치로부터의 거리
			vector<vector<bool>> visited(101, vector<bool>(101, false)); // 방문 여부
			q.push({ i,j });
			visited[i][j] = true;

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				// 시작 섬과 다른 섬이고 해당 위치가 바다가 아닌 경우 다른 섬에 도착한것이다.
				if (board[cur.first][cur.second] != board[i][j] and board[cur.first][cur.second] > 0) {
					answer = min(dis[cur.first][cur.second] - 1, answer);
					break;
				}

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
						continue;
					// 현재 위치가 시작 섬에 포함되거나 이미 방문한 바다인 경우
					if (board[xpos][ypos] == board[i][j] or visited[xpos][ypos])
						continue;
					visited[xpos][ypos] = true;
					dis[xpos][ypos] = dis[cur.first][cur.second] + 1;
					q.push({ xpos,ypos });
				}
			}
		}
	}

	cout << answer;

	return 0;
}