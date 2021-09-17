#include <bits/stdc++.h>

using namespace std;

// ↑ ↖ ← ↙ ↓ ↘ → ↗ 방향 정의
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };

vector<vector<int>> board(20, vector<int>(20, 0));	// 오목 판
vector<pair<int, int>> stone;	// 오목이 완성되었을 때 돌의 위치

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	if (p1.second == p2.second)
		return p1.first < p2.first;
	else
		return p1.second < p2.second;
}

int check(pair<int, int> pos) {
	int counts = 1;	// 연속인 돌의 갯수
	int xpos, ypos;
	
	for (int i = 0; i < 4; i++) {
		xpos = pos.first + dx[i];
		ypos = pos.second + dy[i];
		
		vector<pair<int, int>> tmp_stone;	// 돌의 위치를 저장하는 벡터
		tmp_stone.push_back(pos);

		// 범위에 벗어나지 않고 돌의 색깔이 다를 때까지 반복
		while (xpos > 0 and xpos < 20 and ypos > 0 and ypos < 20 and board[xpos][ypos] == board[pos.first][pos.second]) {
			tmp_stone.push_back({ xpos,ypos });
			counts++;
			xpos += dx[i];
			ypos += dy[i];
		}

		// 반대 방향도 검사
		int j = i + 4;
		xpos = pos.first + dx[j];
		ypos = pos.second + dy[j];
		while (xpos > 0 and xpos < 20 and ypos > 0 and ypos < 20 and board[xpos][ypos] == board[pos.first][pos.second]) {
			tmp_stone.push_back({ xpos,ypos });
			counts++;
			xpos += dx[j];
			ypos += dy[j];
		}
		
		// 반대 방향까지 검사했을 때도 오목이 완성된 경우
		if (counts == 5) {
			stone = tmp_stone;
			return board[pos.first][pos.second];
		}	
		else // 연속된 돌이 5개보다 많거나 적은 경우
			counts = 1;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 1; i <= 19; i++) {
		for (int j = 1; j <= 19; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= 19; i++) {
		for (int j = 1; j <= 19; j++) {
			if (board[i][j] > 0) {	// 해당 위치에 돌이 놓아져 있을 경우
				int winner = check({ i,j });
				if (winner > 0) {	// 오목이 완성된 경우
					sort(stone.begin(), stone.end(), cmp);
					cout << winner << '\n' << stone[0].first << ' ' << stone[0].second;
					return 0;
				}
			}
		}
	}

	cout << "0";

	return 0;
}