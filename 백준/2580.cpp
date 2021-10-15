#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board(9, vector<int>(9));
vector<vector<bool>> horizontalExist(9, vector<bool>(10, false));	// horizontalExist[i][n] -> i��° �����ٿ� ���� n�� �����ϴ���
vector<vector<bool>> verticalExist(9, vector<bool>(10, false));	// verticalExist[j][n] -> j��° �����ٿ� ���� n�� �����ϴ���

// ���� ��ܺ��� ���������� ���簢�� ��ȣ�� �ű��.
// 0 1 2
// 3 4 5
// 6 7 8
// ���� ���, (0, 2)�� 0��° ���簢���� (3, 4)�� 4��° ���簢���� ��ġ�Ѵ�.
vector<vector<bool>> rectangleExist(9, vector<bool>(10, false));	// k��° ���簢���� ���� n�� �����ϴ���

int blank_size;	// �� �� ĭ�� ����
bool isfound = false;	// �ش��� ã�Ҵ����� ���� flag

bool checkRectangle(pair<int, int> pos, int num) {	// �ش� ��ġ�� ���簢���� num�̶�� ���� �����ϴ��� Ȯ���ϴ� �Լ�
	if (rectangleExist[(pos.first / 3) * 3 + (pos.second / 3)][num])
		return false;
	return true;
}

bool checkLine(pair<int, int> pos, int num) {	// �ش� ��ġ�� �����ٰ� �����ٿ� num�̶�� ���� �����ϴ��� Ȯ���ϴ� �Լ�
	if (horizontalExist[pos.first][num])
		return false;
	if (verticalExist[pos.second][num])
		return false;
	return true;
}

void func(int depth, deque<pair<int, int>> blanks) {
	if (depth == blank_size) {	// ��� �� ĭ�� ä���� ���
		for (int i = 0; i < board.size(); i++) {
			for (auto num : board[i])
				cout << num << " ";
			cout << '\n';
		}
		isfound = true;
		return;
	}
	auto it = blanks.begin();	// �� ĭ �ϳ��� �����´�.
	
	for (int i = 1; i <= 9; i++) {
		// �ش� �� ĭ�� ���ڰ� �� �� �ִ��� üũ
		if (!checkLine(*it, i))
			continue;
		if (!checkRectangle(*it, i))
			continue;

		// �� ������Ʈ
		board[it->first][it->second] = i;
		horizontalExist[it->first][i] = true;
		verticalExist[it->second][i] = true;
		rectangleExist[(it->first / 3) * 3 + (it->second / 3)][i] = true;

		deque<pair<int, int>> tmp_blank = blanks;
		// �� ĭ �ϳ��� ä������ pop_front�� �Ѵ�.
		tmp_blank.pop_front();

		func(depth + 1, tmp_blank);
		
		if (isfound)	// �ϳ��� ����� ���� ã�Ҵٸ� �Լ� ����
			return;

		// �� �ǵ�����
		board[it->first][it->second] = 0;
		horizontalExist[it->first][i] = false;
		verticalExist[it->second][i] = false;
		rectangleExist[(it->first / 3) * 3 + (it->second / 3)][i] = false;
	}
	
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	deque<pair<int, int>> blank;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num;
			cin >> num;
			board[i][j] = num;

			if (num == 0) {
				blank.push_back({ i,j });
				continue;
			}

			horizontalExist[i][num] = true;
			verticalExist[j][num] = true;
			rectangleExist[(i / 3) * 3 + (j / 3)][num] = true;
		}
	}
	blank_size = blank.size();

	func(0, blank);

	return 0;
}