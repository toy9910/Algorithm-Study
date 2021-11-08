#include <bits/stdc++.h>

using namespace std;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

vector<vector<int>> board(1001, vector<int>(1001));	// 토마토 보관 창고
vector<vector<bool>> visited(1001, vector<bool>(1001, false));	// 방문 여부 확인
vector<vector<int>> day(1001, vector<int>(1001, 0));	// 최소 날짜를 저장해놓은 배열
int M, N;
int total = 0;	// 0의 갯수
int answer = 0;	// 0->1로 바뀐 토마토 갯수
int days = 0;	// 최소 날짜

// total == answer면 모든 토마토가 익은 거고
// total != ansewr면 토마토가 모두 익지 않은 것!
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> M >> N;

	queue<pair<int, int>> q;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 0)
				total++;
			if (board[i][j] == 1)
				q.push({ i,j });
		}
	}

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) {
			int xpos = cur.first + dx[k];
			int ypos = cur.second + dy[k];

			// 제대로 된 범위 내에 있는지 체크
			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
				continue;

			// 방문한 위치인지 체크
			if (visited[xpos][ypos])
				continue;

			// 익지 않은 토마토인지 체크
			if (board[xpos][ypos] == 0) {
				q.push({ xpos,ypos });
				board[xpos][ypos] = 1;
				day[xpos][ypos] = day[cur.first][cur.second] + 1;	// 해당 위치 날짜 = 전 날짜 + 1
				days = day[xpos][ypos];	// 해당 위치 날짜가 곧 최소 날짜
				visited[xpos][ypos] = true;	// 방문 표시
				answer++;
			}
		}
	}

	if (total == answer)
		cout << days;
	else
		cout << "-1";

	return 0;
}