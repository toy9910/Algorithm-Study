#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(51, vector<int>(51));
vector<pair<int, int>> virus; // ��� ���̷����� ��ġ
vector<pair<int, int>> tmp(11); // �������� ������ ���̷�����
vector<int> answers; // �� ����� �ɸ� �ð��� ����
int N, M, answer, zcount;

void func(int depth, int next) {
	if (depth == M) {
		answer = 0;
		vector<vector<int>> dis(51, vector<int>(51, 0)); // �ɸ� �ð�
		vector<vector<bool>> visited(51, vector<bool>(51, false)); // �湮 ǥ��
		queue<pair<int, int>> q;

		// ť�� M���� Ȱ��ȭ ���̷��� �ֱ�
		for (int i = 0; i < M; i++) {
			q.push({ tmp[i] });
			visited[tmp[i].first][tmp[i].second] = true;
		}

		int ccount = 0; // �� ĭ -> ���̷����� �� ����

		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			for (int k = 0; k < 4; k++) {
				int xpos = cur.first + dx[k];
				int ypos = cur.second + dy[k];

				if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
					continue;
				if (board[xpos][ypos] == 1 or visited[xpos][ypos]) // �� �Ǵ� ���̷����� ���, �̹� �湮�� ���
					continue;
				if (board[xpos][ypos] == 0) // �� ĭ -> ���̷��� üũ
					ccount++;
				dis[xpos][ypos] = dis[cur.first][cur.second] + 1; // �ɸ� �ð� ������Ʈ

				// ��� �� ĭ�� ���̷����� �� ���
				if (zcount == ccount) {
					answer = max(dis[xpos][ypos], answer);
					answers.push_back(answer);
					return;
				}
				dis[xpos][ypos] = dis[cur.first][cur.second] + 1;
				visited[xpos][ypos] = true;
				q.push({ xpos,ypos });
			}
		}
	}
	else {
		// ��ͷ� ���� ����
		for (int i = next; i < virus.size(); i++) {
			tmp[depth] = virus[i];
			func(depth + 1, i + 1);
		}
	}
	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	// �� ĭ ����
	zcount = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2)
				virus.push_back({ i,j });
			else if (board[i][j] == 0)
				zcount++;
		}
	}

	// �� ĭ�� ���� ���
	if (zcount == 0) {
		cout << 0;
		return 0;
	}

	func(0, 0);
	// ��� �� ĭ�� ���̷����� �۶߸� �� �ִ� ���
	if (!answers.empty()) {
		// ���� �� �ּڰ� ���
		sort(answers.begin(), answers.end());
		cout << answers[0];
	}
	else // ��� �� ĭ�� ���̷����� �۶߸� �� ���� ���
		cout << -1;

	return 0;
}