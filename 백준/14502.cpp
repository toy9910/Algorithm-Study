#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

vector<vector<int>> lab(8, vector<int>(8));	// ������
int N, M, answer;

// ���̷��� ���� üũ
void checkVirus(vector<vector<int>> board) {
	vector<vector<bool>> visited(8, vector<bool>(8, false));	// ���̷��� �湮 ǥ��
	queue<pair<int, int>> vq;	// ���̷����� ��ġ�� �����ϴ� ť

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// ���̷����� �ƴ� ��� ��ŵ
			if (board[i][j] != 2)
				continue;

			// ���̷����� ��� �湮 ǥ�� �� ť�� ����
			visited[i][j] = true;
			vq.push({ i,j });

			// ���̷��� �۶߸��� �۾�
			while (!vq.empty()) {
				auto cur = vq.front();
				vq.pop();

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
						continue;
					if (visited[xpos][ypos] or board[xpos][ypos] == 1)
						continue;

					// �ش� ��ġ�� ���̷��� ����
					board[xpos][ypos] = 2;
					visited[xpos][ypos] = true;
					vq.push({ xpos, ypos });
				}
			}
		}
	}

	// ���� ������ ũ��
	int scount = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0)
				scount++;
		}
	}

	answer = max(scount, answer);
}

void func(int depth, int next) {
	// ���� ���� ������ 3���� ��� ���̷����� �۶߸� �� ���� ������ ����Ѵ�.
	if (depth == 3) {
		checkVirus(lab);
		return;
	}

	// �ߺ��� ������� �ʴ� ������ ���
	for (int i = next / M; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (lab[i][j] == 2 or lab[i][j] == 1)
				continue;

			// �ش� ��ġ�� ���� ����� ����Լ� ȣ��
			lab[i][j] = 1;
			func(depth + 1, i * M + j+1);
			lab[i][j] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	answer = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int num;
			cin >> num;
			lab[i][j] = num;
		}
	}

	func(0, 0);

	cout << answer;

	return 0;
}