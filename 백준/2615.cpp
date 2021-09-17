#include <bits/stdc++.h>

using namespace std;

// �� �� �� �� �� �� �� �� ���� ����
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };

vector<vector<int>> board(20, vector<int>(20, 0));	// ���� ��
vector<pair<int, int>> stone;	// ������ �ϼ��Ǿ��� �� ���� ��ġ

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	if (p1.second == p2.second)
		return p1.first < p2.first;
	else
		return p1.second < p2.second;
}

int check(pair<int, int> pos) {
	int counts = 1;	// ������ ���� ����
	int xpos, ypos;
	
	for (int i = 0; i < 4; i++) {
		xpos = pos.first + dx[i];
		ypos = pos.second + dy[i];
		
		vector<pair<int, int>> tmp_stone;	// ���� ��ġ�� �����ϴ� ����
		tmp_stone.push_back(pos);

		// ������ ����� �ʰ� ���� ������ �ٸ� ������ �ݺ�
		while (xpos > 0 and xpos < 20 and ypos > 0 and ypos < 20 and board[xpos][ypos] == board[pos.first][pos.second]) {
			tmp_stone.push_back({ xpos,ypos });
			counts++;
			xpos += dx[i];
			ypos += dy[i];
		}

		// �ݴ� ���⵵ �˻�
		int j = i + 4;
		xpos = pos.first + dx[j];
		ypos = pos.second + dy[j];
		while (xpos > 0 and xpos < 20 and ypos > 0 and ypos < 20 and board[xpos][ypos] == board[pos.first][pos.second]) {
			tmp_stone.push_back({ xpos,ypos });
			counts++;
			xpos += dx[j];
			ypos += dy[j];
		}
		
		// �ݴ� ������� �˻����� ���� ������ �ϼ��� ���
		if (counts == 5) {
			stone = tmp_stone;
			return board[pos.first][pos.second];
		}	
		else // ���ӵ� ���� 5������ ���ų� ���� ���
			counts = 1;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 1; i <= 19; i++) {
		for (int j = 1; j <= 19; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= 19; i++) {
		for (int j = 1; j <= 19; j++) {
			if (board[i][j] > 0) {	// �ش� ��ġ�� ���� ������ ���� ���
				int winner = check({ i,j });
				if (winner > 0) {	// ������ �ϼ��� ���
					sort(stone.begin(), stone.end(), cmp);
					cout << winner << '\n' << stone[0].first << ' ' << stone[0].second;
					return 0;
				}
			}
		}
	}

	cout << "0";

	return 0;
}