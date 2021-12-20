#include <bits/stdc++.h>


using namespace std;

int dlx[] = { -2,-1,-1,-1,0,1,1,1,2 };
int dly[] = { 0,-1,0,1,-2,-1,0,1,0 };
int ddx[] = { -1,-1,0,0,0,0,1,1,2 };
int ddy[] = { -1,1,-2,-1,1,2,-1,1,0 };
int drx[] = { -2,-1,-1,-1,0,1,1,1,2 };
int dry[] = { 0,-1,0,1,2,-1,0,1,0 };
int dux[] = { -2,-1,-1,0,0,0,0,1,1 };
int duy[] = { 0,-1,1,-2,-1,1,2,-1,1 };

double dl[] = { 0.02, 0.1 , 0.07, 0.01, 0.05, 0.1, 0.07, 0.01, 0.02 };
double dd[] = { 0.01,0.01,0.02,0.07,0.07,0.02,0.1,0.1,0.05 };
double dr[] = { 0.02,0.01,0.07,0.1,0.05,0.01,0.07,0.1,0.02 };
double du[] = { 0.05,0.1,0.1,0.02,0.07,0.07,0.02,0.01,0.01 };

enum DIR {
	L,D,R,U
};

vector<vector<int>> board(500, vector<int>(501));
int N, answer;
pair<int, int> cur;
DIR curD = DIR::L;

void checkDir() {
	if (cur.first == N / 2 and cur.second == N / 2)
		return;

	if (cur.first == cur.second) {
		if (cur.first > N / 2)
			curD = DIR::U;
	}
	else {
		if (cur.first - 1 == cur.second and cur.first <= (N - 1) / 2) {
			curD = DIR::D;
		}
		else if (cur.first + cur.second == N - 1) {
			if (cur.first > N / 2)
				curD = DIR::R;
			else
				curD = DIR::L;
		}
	}
}

void blowSand() {
	switch (curD) {
	case L: {
		cur.second--;

		if (board[cur.first][cur.second] == 0)
			return;

		int sum = 0; // 다른 곳으로 이동한 모래의 합
		for (int k = 0; k < 9; k++) {
			int xpos = cur.first + dlx[k];
			int ypos = cur.second + dly[k];

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)  // 격자 밖으로 나간 경우
				answer += (int)((double)board[cur.first][cur.second] * dl[k]);
			else
				board[xpos][ypos] += (int)((double)board[cur.first][cur.second] * dl[k]);

			sum += (int)((double)board[cur.first][cur.second] * dl[k]);
		}

		// 나머지 처리 부분
		int remain = board[cur.first][cur.second] - sum;
		if (cur.second - 1 < 0)
			answer += remain;
		else
			board[cur.first][cur.second-1] += remain;

		break;
	}
	case D: {
		cur.first++;

		if (board[cur.first][cur.second] == 0)
			return;

		int sum = 0;
		for (int k = 0; k < 9; k++) {
			int xpos = cur.first + ddx[k];
			int ypos = cur.second + ddy[k];

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)  // 격자 밖으로 나간 경우
				answer += (int)((double)board[cur.first][cur.second] * dd[k]);
			else
				board[xpos][ypos] += (int)((double)board[cur.first][cur.second] * dd[k]);

			sum += (int)((double)board[cur.first][cur.second] * dd[k]);
		}

		// 나머지 처리 부분
		int remain = board[cur.first][cur.second] - sum;
		if (cur.first + 1 >= N)
			answer += remain;
		else
			board[cur.first + 1][cur.second] += remain;
		break;
	}
	case R: {
		cur.second++;

		if (board[cur.first][cur.second] == 0)
			return;

		int sum = 0;
		for (int k = 0; k < 9; k++) {
			int xpos = cur.first + drx[k];
			int ypos = cur.second + dry[k];

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)  // 격자 밖으로 나간 경우
				answer += (int)((double)board[cur.first][cur.second] * dr[k]);
			else
				board[xpos][ypos] += (int)((double)board[cur.first][cur.second] * dr[k]);

			sum += (int)((double)board[cur.first][cur.second] * dr[k]);
		}

		// 나머지 처리 부분
		int remain = board[cur.first][cur.second] - sum;
		if (cur.second + 1 >= N)
			answer += remain;
		else
			board[cur.first][cur.second + 1] += remain;
		break;
	}
	case U: {
		cur.first--;

		if (board[cur.first][cur.second] == 0)
			return;

		int sum = 0;
		for (int k = 0; k < 9; k++) {
			int xpos = cur.first + dux[k];
			int ypos = cur.second + duy[k];

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)  // 격자 밖으로 나간 경우
				answer += (int)((double)board[cur.first][cur.second] * du[k]);
			else
				board[xpos][ypos] += (int)((double)board[cur.first][cur.second] * du[k]);

			sum += (int)((double)board[cur.first][cur.second] * du[k]);
		}

		// 나머지 처리 부분
		int remain = board[cur.first][cur.second] - sum;
		if (cur.first - 1 < 0)
			answer += remain;
		else
			board[cur.first - 1][cur.second] += remain;
		break;
	}
	}
	board[cur.first][cur.second] = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	answer = 0;
	cur = { N / 2,N / 2 };

	while (true) {
		if (cur.first == 0 and cur.second == 0)
			break;

		checkDir();
		blowSand();
	}

	cout << answer;

	return 0;
}