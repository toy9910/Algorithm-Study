#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

vector<vector<int>> board(101, vector<int>(101)); // 2���� �迭
vector<int> answer; // �� ���� �翡 ���� ���� ������ ����
int N, maxRain;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	// �ִ�� �� �� �ִ� ���� ��
	maxRain = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			maxRain = max(maxRain, board[i][j]);
		}
	}


	for (int rain = 0; rain <= maxRain; rain++) {
		vector<vector<bool>> visited(101, vector<bool>(101, false));
		int counts = 0; // ���� ������ ��

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// �ش� ��ġ�� �湮�߰ų� ���� �纸�� ���̰� ���� ���
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

	// ������������ ����
	sort(answer.begin(), answer.end(), greater<int>());
	cout << *answer.begin();

	return 0;
}