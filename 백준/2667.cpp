#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0, -1, 0, 1 };

vector<vector<int>> board(30, vector<int>(30));	// 지도
vector<vector<bool>> visited(30, vector<bool>(30, false)); // 방문 표시
vector<int> answer; // 단지에 속하는 집의 수
int N, apt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			board[i][j] = str[j] - '0';
		}
	}

	// 단지 수 초기화
	apt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 해당 위치의 집에 방문했거나 해당 위치에 집이 없을 경우
			if (visited[i][j] or board[i][j] == 0)
				continue;

			// 해당 위치의 집에 방문
			queue<pair<int, int>> q;
			q.push({ i,j });
			visited[i][j] = true;
			apt++;
			// 해당 단지 내 집의 수
			int counts = 1;

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
						continue;
					if (visited[xpos][ypos] or board[xpos][ypos] == 0)
						continue;
					q.push({ xpos,ypos });
					visited[xpos][ypos] = true;
					counts++;
				}
			}
			answer.push_back(counts);
		}
	}

	cout << apt << '\n';
	sort(answer.begin(), answer.end());
	for (auto num : answer)
		cout << num << '\n';
	return 0;
}