#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

int N, M;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	if (N == 1 and M == 1) {
		cout << 1;
		return 0;
	}

	vector<vector<int>> board(1001, vector<int>(1001, 0)); // ��
	// ����� ~ �ش� ��ġ������ �Ÿ�
	// 3���� �迭�� 0��°�� ���� ���� �ʰ� �� ����� �Ÿ��� ���ϰ�
	// 1��°�� ���� �հ� �� ����� �Ÿ��� ���Ѵ�.
	// dis[5][3][1] = 10 �� ��� 5,3���� ���� �� �� �հ� 10ĭ �ɸ��ٴ� ��
	vector<vector<vector<int>>> dis(1001, vector<vector<int>>(1001, vector<int>(2, 0))); 

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;

		for (int j = 0; j < str.length(); j++) {
			board[i][j] = str[j] - '0';
		}
	}

	// Ʃ���� { ��, ��, ���� ��ġ���� ���� �հ� �Դ����� ���� ���� } �� ���Ѵ�.
	// ����° ���� 0�� ���� ���� �հ� ���� ����, 1�� ��� ���� �հ� �Դٴ� ��
	queue<tuple<int,int,int>> q;
	q.push({ 0,0,0 });

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) {
			int xpos = get<0>(cur) + dx[k];
			int ypos = get<1>(cur) + dy[k];

			if (xpos == 0 and ypos == 0)
				continue;

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
				continue;

			if (get<2>(cur) > 0) {	// ���� �μ��� �� ���
				if (board[xpos][ypos] < 1) { // ������ ���� �ƴ� ���
					if (dis[xpos][ypos][1] == 0) {	// ���� ��ġ�� ���� �μ��� �湮�� ��찡 ���� ��
						dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][1] + 1;
						q.push({ xpos,ypos,1 });
					}
					else { // ���� ��ġ�� ���� �μ��� �湮�� ��찡 ���� ��
						// �Ÿ��� ���Ѵ�.
						if (dis[xpos][ypos][1] > dis[get<0>(cur)][get<1>(cur)][1] + 1) {
							dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][1] + 1;
							q.push({ xpos,ypos,1 });
						}
					}
				}
			}
			else {	// ���� �Ⱥμ��� �� ���
				if (board[xpos][ypos] < 1) { // ������ ���� �ƴ� ���
					if (dis[xpos][ypos][0] == 0) {	// ���� ��ġ�� ���� �Ⱥμ��� �湮�� ��찡 ���� ��
						dis[xpos][ypos][0] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
						q.push({ xpos,ypos,0 });
					}
					else { // ���� ��ġ�� ���� �Ⱥμ��� �湮�� ��찡 ���� ��
						// �Ÿ��� ���Ѵ�.
						if (dis[xpos][ypos][0] > dis[get<0>(cur)][get<1>(cur)][0] + 1) {
							dis[xpos][ypos][0] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
							q.push({ xpos,ypos,0});
						}
					}
				}
				else { // ���� ��ġ�� ���� ���
					if (dis[xpos][ypos][1] > 0) { // ���� ��ġ�� ���� �μ��� �湮�� ��찡 ���� ��
						// �Ÿ��� ���Ѵ�.
						if (dis[xpos][ypos][1] > dis[get<0>(cur)][get<1>(cur)][0] + 1) {
							dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
							q.push({ xpos,ypos,1 });
						}
					}
					else { // ���� ��ġ�� ���� �μ��� �湮�� ��찡 ���� ��
						dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
						q.push({ xpos,ypos, 1 });
					}
				}
			}
		}
	}

	// �������� ������ ���� ���
	if (max(dis[N - 1][M - 1][0], dis[N - 1][M - 1][1]) == 0)
		cout << -1;
	else { // �������� ���� �μ��� ���ų�, ���� �μ��� �ʰ� ������ ���
		if (dis[N - 1][M - 1][0] > 0 and dis[N - 1][M - 1][1] > 0)
			// ���� �μ��� �� ���� ���� �μ��� ���� ���� ��� �� �� ���� ��
			// �� �� ���� ���� ����ؾ� �Ѵ�.
			cout << min(dis[N - 1][M - 1][0], dis[N - 1][M - 1][1]) + 1;
		else
			// ���� �μ��� �� ���� ���� �μ��� ���� ���� ��� �� �ϳ��� ���� ��
			// ���� �μ��� �� ���� 0�̹Ƿ� �� �� ū ���� ����ؾ� �Ѵ�.
			cout << max(dis[N - 1][M - 1][0], dis[N - 1][M - 1][1]) + 1;
	}

	return 0;
}