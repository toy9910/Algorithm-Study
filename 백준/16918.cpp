#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = {0, -1, 0, 1};

int N, R, C;
vector<vector<char>> board1(205, vector<char>(205)), board2(205, vector<char>(205, 'O')), board3(205, vector<char>(205)), board4(205, vector<char>(205)) , answer;


void input() {
	cin >> R >> C >> N;
	for (int i = 0; i < R; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			board1[i][j] = str[j];
			board2[i][j] = 'O';
		}
	}
}

void explode1() {
	vector<vector<char>> b = board1;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (b[i][j] == '.') {
				b[i][j] = 'B';
			}
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (b[i][j] == 'O') {
				b[i][j] = '.';

				for (int k = 0; k < 4; k++) {
					int xpos = i + dx[k], ypos = j + dy[k];
					if (xpos < 0 or xpos >= R or ypos < 0 or ypos >= C) continue;
					if (b[xpos][ypos] == 'O') continue;
					b[xpos][ypos] = '.';
				}
			}
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (b[i][j] == 'B') {
				b[i][j] = 'O';
			}
		}
	}
	board3 = b;
}

void explode2() {
	vector<vector<char>> b = board3;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (b[i][j] == '.') {
				b[i][j] = 'B';
			}
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (b[i][j] == 'O') {
				b[i][j] = '.';

				for (int k = 0; k < 4; k++) {
					int xpos = i + dx[k], ypos = j + dy[k];
					if (xpos < 0 or xpos >= R or ypos < 0 or ypos >= C) continue;
					if (b[xpos][ypos] == 'O') continue;
					b[xpos][ypos] = '.';
				}
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (b[i][j] == 'B') {
				b[i][j] = 'O';
			}
		}
	}
	board4 = b;
}


void solve() {
	explode1();
	explode2();

	if (N == 1) {
		answer = board1;
	}
	else if (N % 2 == 0) {
		answer = board2;
	}
	else {
		if (N % 4 == 3) {
			answer = board3;
		}
		else {
			answer = board4;
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << answer[i][j];
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}