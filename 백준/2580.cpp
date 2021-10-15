#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board(9, vector<int>(9));
vector<vector<bool>> horizontalExist(9, vector<bool>(10, false));	// horizontalExist[i][n] -> i번째 가로줄에 숫자 n이 존재하는지
vector<vector<bool>> verticalExist(9, vector<bool>(10, false));	// verticalExist[j][n] -> j번째 세로줄에 숫자 n이 존재하는지

// 왼쪽 상단부터 오른쪽으로 정사각형 번호를 매긴다.
// 0 1 2
// 3 4 5
// 6 7 8
// 예를 들면, (0, 2)는 0번째 정사각형에 (3, 4)는 4번째 정사각형에 위치한다.
vector<vector<bool>> rectangleExist(9, vector<bool>(10, false));	// k번째 정사각형에 숫자 n이 존재하는지

int blank_size;	// 총 빈 칸의 갯수
bool isfound = false;	// 해답을 찾았는지에 대한 flag

bool checkRectangle(pair<int, int> pos, int num) {	// 해당 위치의 정사각형에 num이라는 수가 존재하는지 확인하는 함수
	if (rectangleExist[(pos.first / 3) * 3 + (pos.second / 3)][num])
		return false;
	return true;
}

bool checkLine(pair<int, int> pos, int num) {	// 해당 위치의 가로줄과 세로줄에 num이라는 수가 존재하는지 확인하는 함수
	if (horizontalExist[pos.first][num])
		return false;
	if (verticalExist[pos.second][num])
		return false;
	return true;
}

void func(int depth, deque<pair<int, int>> blanks) {
	if (depth == blank_size) {	// 모든 빈 칸을 채웠을 경우
		for (int i = 0; i < board.size(); i++) {
			for (auto num : board[i])
				cout << num << " ";
			cout << '\n';
		}
		isfound = true;
		return;
	}
	auto it = blanks.begin();	// 빈 칸 하나를 가져온다.
	
	for (int i = 1; i <= 9; i++) {
		// 해당 빈 칸에 숫자가 들어갈 수 있는지 체크
		if (!checkLine(*it, i))
			continue;
		if (!checkRectangle(*it, i))
			continue;

		// 값 업데이트
		board[it->first][it->second] = i;
		horizontalExist[it->first][i] = true;
		verticalExist[it->second][i] = true;
		rectangleExist[(it->first / 3) * 3 + (it->second / 3)][i] = true;

		deque<pair<int, int>> tmp_blank = blanks;
		// 빈 칸 하나를 채웠으니 pop_front를 한다.
		tmp_blank.pop_front();

		func(depth + 1, tmp_blank);
		
		if (isfound)	// 하나의 경우의 수라도 찾았다면 함수 종료
			return;

		// 값 되돌리기
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