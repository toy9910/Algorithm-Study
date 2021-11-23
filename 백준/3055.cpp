#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<char>> board(51, vector<char>(51));
int R, C;

// ����ġ�� �ش� ĭ�� �� �� �ִ��� Ȯ���ϴ� �Լ�
// �ش� ĭ�� ���� �� �����̸� �� �� ����.
bool canGo(pair<int,int> cur) {
	for (int k = 0; k < 4; k++) {
		int xpos = cur.first + dx[k];
		int ypos = cur.second + dy[k];

		if (xpos < 0 or xpos >= R or ypos < 0 or ypos >= C)
			continue;
		if (board[xpos][ypos] == '*')
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C;

	pair<int, int> dPos, sPos;
	queue<tuple<int, int, int>> q; // 3��° ���� 0�̸� ����ġ�� 1�̸� ���̶�� ���̴�.
	vector<pair<int, int>> dv; // ���� ��ġ�� ����

	for (int i = 0; i < R; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < C; j++) {
			board[i][j] = str[j];

			switch (str[j]) {
			case 'D': {
				dPos = { i,j };
				break;
			}
			case 'S': {
				sPos = { i,j };
				// ����ġ�� ���� �����̱� ���� ���� ť�� ����
				q.push({ sPos.first,sPos.second,0 });
				break;
			}
			case '*': {
				dv.push_back({ i,j });
				break;
			}
			}
		}
	}

	
	vector<vector<int>> dis(51, vector<int>(51, 0)); // ����ġ�� ���������κ����� �Ÿ�
	vector<vector<bool>> visited(51, vector<bool>(51, false));

	// ���� ��ġ���� ť�� ����
	for (auto pos : dv) 
		q.push({ pos.first, pos.second, 1 });
	
	visited[sPos.first][sPos.second] = true;

	int answer = 0;

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		if (get<2>(cur) == 0 and get<0>(cur) == dPos.first and get<1>(cur) == dPos.second) {
			answer = dis[dPos.first][dPos.second];
			break;
		}

		for (int k = 0; k < 4; k++) {
			int xpos = get<0>(cur) + dx[k];
			int ypos = get<1>(cur) + dy[k];

			if (xpos < 0 or xpos >= R or ypos < 0 or ypos >= C)
				continue;
			if (board[xpos][ypos] == 'X')
				continue;

			if (get<2>(cur) == 0) { // ����ġ�� ��� ���� �� �� ����.
				if (board[xpos][ypos] == '*' or visited[xpos][ypos])
					continue;

				// �ش� ��ġ�� D�� �ƴϸ鼭 �� �� ������ ��ŵ
				if (!canGo({ xpos,ypos }) and board[xpos][ypos] != 'D')
					continue;

				visited[xpos][ypos] = true;
				dis[xpos][ypos] = dis[get<0>(cur)][get<1>(cur)] + 1;
				q.push({ xpos,ypos,0 });
			} 
			else { // ���� ��� ����� ���� �� �� ����.
				if (board[xpos][ypos] == 'D' or board[xpos][ypos] == '*')
					continue;
				board[xpos][ypos] = '*';
				q.push({ xpos,ypos,1 });
			}
		}
	}

	if (answer == 0)
		cout << "KAKTUS";
	else
		cout << answer;


	return 0;
}