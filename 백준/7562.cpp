#include <bits/stdc++.h>

using namespace std;

// 나이트가 이동할 수 있는 8가지 방향
int dx[8] = { -2,-1,1,2,2,1,-1,-2 };
int dy[8] = { -1,-2,-2,-1,1,2,2,1 };

pair<int, int> spos, epos;	// 시작점과 종료지점
int N;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	while (N--) {
		int l;
		cin >> l;

		int n1, n2;
		cin >> n1 >> n2;

		spos = { n1, n2 };	// 시작점

		cin >> n1 >> n2;
		epos = { n1, n2 };	// 종료지점

		queue<pair<int, int>> q;
		vector<vector<int>> board(301, vector<int>(301, 0));	// 나이트의 이동 횟수
		vector<vector<bool>> visited(301, vector<bool>(301, false));	// 나이트의 방문 여부

		q.push(spos);
		visited[spos.first][spos.second] = true;

		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			// 종료 지점 도달
			if (cur.first == epos.first and cur.second == epos.second)
				break;

			for (int k = 0; k < 8; k++) {
				int xpos = cur.first + dx[k];
				int ypos = cur.second + dy[k];

				// 체스판 범위에서 벗어나거나 이미 해당 칸에 방문했을 경우 스킵
				if (xpos < 0 or xpos >= l or ypos < 0 or ypos >= l)
					continue;
				if (visited[xpos][ypos])
					continue;
				
				board[xpos][ypos] = board[cur.first][cur.second] + 1;	// 다음 칸의 이동 횟수 = 현재 칸까지의 이동 횟수 + 1
				visited[xpos][ypos] = true;	// 방문 표시
				q.push({ xpos, ypos });
			}
		}
		cout << board[epos.first][epos.second] << '\n';
	}

	return 0;
}