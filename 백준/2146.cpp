#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(101, vector<int>(101)); // ����
int N, answer;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	int lcount = 0; // ���� ����

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// �ش� ĭ�� ������ ���
			if (board[i][j] == 1) {
				queue<pair<int, int>> q;
				lcount++;
				// lcount�� ���� ���� �������ش�.
				// 1��°�� �߰ߵ� ���� ��� lcount�� 1�� ���Ͽ� 2�� �����
				// 2��°�� �߰ߵ� ���� ��� lcount�� 2�� ���Ͽ� �ش� ĭ���� 3���� �����.
				board[i][j] += lcount;
				q.push(make_pair(i, j));

				while (!q.empty()) {
					auto cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int xpos = cur.first + dx[k];
						int ypos = cur.second + dy[k];

						if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
							continue;
						// �̹� ĭ�� �湮�Ͽ� ������Ʈ�� ���� �ٴ��� ���� continue �Ѵ�.
						if (board[xpos][ypos] > 1 or board[xpos][ypos] == 0)
							continue;
						board[xpos][ypos] += lcount;
						q.push({ xpos,ypos });
					}
				}
			}
		}
	}

	answer = 1000000;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// �ٴ��� ��� continue
			if (board[i][j] == 0)
				continue;
			// �ش� ��ġ�� �����ڸ����� �Ǻ�
			bool isbound = false;
			for (int k = 0; k < 4; k++) {
				int xpos = i + dx[k];
				int ypos = j + dy[k];

				if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
					continue;
				// �� ���̶� �ٴٰ� ������ �����ڸ��̹Ƿ� break
				if (board[xpos][ypos] == 0) {
					isbound = true;
					break;
				}
			}
			// �����ڸ��� �ƴϸ� continue
			if (!isbound)
				continue;

			queue<pair<int, int>> q;
			vector<vector<int>> dis(101, vector<int>(101, 0)); // ���� ��ġ�κ����� �Ÿ�
			vector<vector<bool>> visited(101, vector<bool>(101, false)); // �湮 ����
			q.push({ i,j });
			visited[i][j] = true;

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				// ���� ���� �ٸ� ���̰� �ش� ��ġ�� �ٴٰ� �ƴ� ��� �ٸ� ���� �����Ѱ��̴�.
				if (board[cur.first][cur.second] != board[i][j] and board[cur.first][cur.second] > 0) {
					answer = min(dis[cur.first][cur.second] - 1, answer);
					break;
				}

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
						continue;
					// ���� ��ġ�� ���� ���� ���Եǰų� �̹� �湮�� �ٴ��� ���
					if (board[xpos][ypos] == board[i][j] or visited[xpos][ypos])
						continue;
					visited[xpos][ypos] = true;
					dis[xpos][ypos] = dis[cur.first][cur.second] + 1;
					q.push({ xpos,ypos });
				}
			}
		}
	}

	cout << answer;

	return 0;
}