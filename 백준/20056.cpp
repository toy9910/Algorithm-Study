#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> fb;

int dx[] = { -1,-1,0,1,1,1,0,-1 };
int dy[] = { 0,1,1,1,0,-1,-1,-1 };

vector<vector<vector<fb>>> board(51, vector<vector<fb>>(51, vector<fb>()));
int N, M, K;

void moveBall() {
	vector<vector<vector<fb>>> tmpBoard(51, vector<vector<fb>>(51, vector<fb>()));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j].empty())
				continue;
			// ���̾ �ű��
			for (auto ball : board[i][j]) {
				// m ����, s �ӵ�, d ����
				int xpos, ypos, m, s, d;
				tie(m, s, d) = ball;

				xpos = i; 
				ypos = j;
				for (int k = 0; k < s; k++) {
					xpos += dx[d];
					ypos += dy[d];
					// ���̾�� �迭 ������ �Ѿ ���
					if (xpos == 0)
						xpos = N;
					else if (xpos > N)
						xpos = 1;
					if (ypos == 0)
						ypos = N;
					else if (ypos > N)
						ypos = 1;
				}
				tmpBoard[xpos][ypos].push_back(ball);
			}
		}
	}
	board = tmpBoard;
}

void combineBall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j].size() <= 1)
				continue;
			int summ, sums, sumd;
			summ = 0; sums = 0; sumd = 0;
			for (auto ball : board[i][j]) {
				int m, s, d;
				tie(m, s, d) = ball;
				summ += m; sums += s;
				// �ش� ���̾ ������ ¦���� sumd�� 1�� ���ϰ� Ȧ���� �״�� �д�.
				// �ؿ��� sumd�� ���̾ ������ �������� �� �������� 0�̸� ��� Ȧ���̰ų� ¦��
				if (d % 2 == 0)
					sumd++;
			}
			int sizes = board[i][j].size();
			board[i][j].clear();

			// ������ 0�� ���
			if (summ / 5 == 0)
				continue;
			for (int k = 0; k < 4; k++) {
				if (sumd % sizes == 0)  // �������� ���̾�� ������ ��� Ȧ���̰ų� ¦��
					board[i][j].push_back(make_tuple(summ / 5, sums / sizes, k * 2));
				else
					board[i][j].push_back(make_tuple(summ / 5, sums / sizes, k * 2 + 1));
			}
		}
	}
}

int calculateBall() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j].empty())
				continue;
			for (auto ball : board[i][j])
				answer += get<0>(ball);
		}
	}
	return answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;

	for (int i = 0; i < M; i++) {
		int xpos, ypos, m, s, d;
		cin >> xpos >> ypos >> m >> s >> d;
		board[xpos][ypos].push_back(make_tuple(m, s, d));
	}

	while (K--) {
		moveBall();
		combineBall();
	}

	cout << calculateBall();

	return 0;
}