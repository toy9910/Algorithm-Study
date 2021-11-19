#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

vector<vector<int>> board(101, vector<int>(101)); // 2차원 배열
vector<int> answer; // 각 비의 양에 따른 안전 영역의 개수
int N, maxRain;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	// 최대로 올 수 있는 비의 양
	maxRain = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			maxRain = max(maxRain, board[i][j]);
		}
	}


	for (int rain = 0; rain <= maxRain; rain++) {
		vector<vector<bool>> visited(101, vector<bool>(101, false));
		int counts = 0; // 안전 영역의 수

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 해당 위치를 방문했거나 비의 양보다 높이가 높을 경우
				if (board[i][j] <= rain or visited[i][j])
					continue;

				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = true;
				counts++;

				while (!q.empty()) {
					auto cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int xpos = cur.first + dx[k];
						int ypos = cur.second + dy[k];

						if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
							continue;
						if (visited[xpos][ypos] or board[xpos][ypos] <= rain)
							continue;
						q.push({ xpos,ypos });
						visited[xpos][ypos] = true;
					}
				}
			}
		}
		answer.push_back(counts);
	}

	// 내림차순으로 정렬
	sort(answer.begin(), answer.end(), greater<int>());
	cout << *answer.begin();

	return 0;
}