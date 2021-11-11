#include <bits/stdc++.h>

using namespace std;

// ����Ʈ�� �̵��� �� �ִ� 8���� ����
int dx[8] = { -2,-1,1,2,2,1,-1,-2 };
int dy[8] = { -1,-2,-2,-1,1,2,2,1 };

pair<int, int> spos, epos;	// �������� ��������
int N;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	while (N--) {
		int l;
		cin >> l;

		int n1, n2;
		cin >> n1 >> n2;

		spos = { n1, n2 };	// ������

		cin >> n1 >> n2;
		epos = { n1, n2 };	// ��������

		queue<pair<int, int>> q;
		vector<vector<int>> board(301, vector<int>(301, 0));	// ����Ʈ�� �̵� Ƚ��
		vector<vector<bool>> visited(301, vector<bool>(301, false));	// ����Ʈ�� �湮 ����

		q.push(spos);
		visited[spos.first][spos.second] = true;

		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			// ���� ���� ����
			if (cur.first == epos.first and cur.second == epos.second)
				break;

			for (int k = 0; k < 8; k++) {
				int xpos = cur.first + dx[k];
				int ypos = cur.second + dy[k];

				// ü���� �������� ����ų� �̹� �ش� ĭ�� �湮���� ��� ��ŵ
				if (xpos < 0 or xpos >= l or ypos < 0 or ypos >= l)
					continue;
				if (visited[xpos][ypos])
					continue;
				
				board[xpos][ypos] = board[cur.first][cur.second] + 1;	// ���� ĭ�� �̵� Ƚ�� = ���� ĭ������ �̵� Ƚ�� + 1
				visited[xpos][ypos] = true;	// �湮 ǥ��
				q.push({ xpos, ypos });
			}
		}
		cout << board[epos.first][epos.second] << '\n';
	}

	return 0;
}