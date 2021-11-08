#include <bits/stdc++.h>

using namespace std;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

vector<vector<int>> board(1001, vector<int>(1001));	// �丶�� ���� â��
vector<vector<bool>> visited(1001, vector<bool>(1001, false));	// �湮 ���� Ȯ��
vector<vector<int>> day(1001, vector<int>(1001, 0));	// �ּ� ��¥�� �����س��� �迭
int M, N;
int total = 0;	// 0�� ����
int answer = 0;	// 0->1�� �ٲ� �丶�� ����
int days = 0;	// �ּ� ��¥

// total == answer�� ��� �丶�䰡 ���� �Ű�
// total != ansewr�� �丶�䰡 ��� ���� ���� ��!
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

			// ����� �� ���� ���� �ִ��� üũ
			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
				continue;

			// �湮�� ��ġ���� üũ
			if (visited[xpos][ypos])
				continue;

			// ���� ���� �丶������ üũ
			if (board[xpos][ypos] == 0) {
				q.push({ xpos,ypos });
				board[xpos][ypos] = 1;
				day[xpos][ypos] = day[cur.first][cur.second] + 1;	// �ش� ��ġ ��¥ = �� ��¥ + 1
				days = day[xpos][ypos];	// �ش� ��ġ ��¥�� �� �ּ� ��¥
				visited[xpos][ypos] = true;	// �湮 ǥ��
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