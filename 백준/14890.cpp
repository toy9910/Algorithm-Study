#include <bits/stdc++.h>

using namespace std;

vector<vector<int>>board(101, vector<int>(101)); // 지도
int N, L, answer;

bool downDFS(int xpos, int ypos, char d, vector<bool> s); // 다음 칸이 한 칸 낮은 경우
bool upDFS(int counts, int xpos, int ypos, char d, vector<bool> s); // 다음 칸이 한 칸 높은 경우

// counts는 지도가 1 1 1 2 이런 경우 1의 갯수를 뜻함.
// xpos, ypos 는 한 칸 높은 칸의 위치
// d는 현재 진행 방향
// s는 해당 칸에 경사로 존재 여부
bool upDFS(int counts, int xpos, int ypos, char d, vector<bool> s) {
	// 낮은 칸의 갯수가 L보다 작은 경우
	// 경사로를 놓을 수 없다.
	if (counts < L)
		return false;

	int target = board[xpos][ypos];
	int scount = 0; // target 숫자의 갯수

	switch (d) {
	case 'R': { // 진행 방향이 가로
		// 앞 칸에 경사로를 놓아준다.
		for (int j = ypos - 1; j >= ypos - L; j--) {
			if (j < 0 or s[j])
				return false;
			s[j] = true;
		}

		
		for (int j = ypos; j < N; j++) {
			// 높이 차이가 1보다 큰 경우
			if (abs(board[xpos][j] - target) > 1)
				return false;
			
			if (board[xpos][j] == target)
				scount++;
			else if (board[xpos][j] < target) 
				return downDFS(xpos, j, 'R', s);
			
			else 
				return upDFS(scount, xpos, j, 'R', s);
		}
		break;
	}
	default: { // 진행 방향이 세로
		for (int i = xpos - 1; i >= xpos - L; i--) {
			if (i < 0 or s[i])
				return false;
			s[i] = true;
		}

		scount = 0;
		for (int i = xpos; i < N; i++) {
			if (abs(board[i][ypos] - target) > 1)
				return false;

			if (board[i][ypos] == target)
				scount++;
			else if (board[i][ypos] < target) 
				return downDFS(i, ypos, 'D', s);
			else 
				return upDFS(scount, i, ypos, 'D', s);
		}
	}
	}
	return true;
}

bool downDFS(int xpos, int ypos, char d, vector<bool> s) {
	int scount = 0;
	int target = board[xpos][ypos];

	switch (d) {
	case 'R': {
		// 3 2 2 2 인 경우에
		// 2의 갯수를 체크하는 과정
		for (int j = ypos; j < N; j++) {
			if (scount == L)
				break;

			if (board[xpos][j] == target)
				scount++;
			else
				break;
		}
		// 2의 갯수가 L보다 작은 경우
		if (scount != L)
			return false;

		// 길이 L만큼 경사로 설치
		for (int j = ypos; j < ypos + L; j++) 
			s[j] = true;

		scount = 0;
		for (int j = ypos + L; j < N; j++) {
			if (abs(board[xpos][j] - target) > 1)
				return false;

			if (board[xpos][j] == target)
				scount++;
			else if (board[xpos][j] < target) 
				return downDFS(xpos, j, 'R', s);
			else 
				return upDFS(scount, xpos, j, 'R', s);
		}
		break;
	}
	default: {
		for (int i = xpos; i < N; i++) {
			if (scount == L)
				break;

			if (board[i][ypos] == target)
				scount++;
			else
				break;
		}
		if (scount != L)
			return false;
		for (int i = xpos; i < xpos + L; i++) {
			s[i] = true;
		}

		scount = 0;
		for (int i = xpos + L; i < N; i++) {
			if (abs(board[i][ypos] - target) > 1)
				return false;

			if (board[i][ypos] == target)
				scount++;
			else if (board[i][ypos] < target) 
				return downDFS(i, ypos, 'D', s);
			else 
				return upDFS(scount, i, ypos, 'D', s);
		}
	}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> L;

	answer = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		int target = board[i][0];
		int scount = 0; // target 숫자의 갯수
		bool canGo = true; // 경사로를 놓을 수 있는지 여부
		for (int j = 0; j < N; j++) {
			// target 숫자와 해당 칸의 높이 차이가 1보다 큰 경우
			if (abs(board[i][j] - target) > 1) {
				canGo = false;
				break;
			}

			if (board[i][j] == target)
				scount++;
			else if (board[i][j] < target) {
				vector<bool> v(N + 1, false);
				canGo = downDFS(i, j, 'R', v);
				break;
			}
			else {
				vector<bool> v(N + 1, false);
				canGo = upDFS(scount, i, j, 'R', v);
				break;
			}
		}
		if (canGo)
			answer++;
	}

	for (int j = 0; j < N; j++) {
		int target = board[0][j];
		int scount = 0;
		bool canGo = true;
		for (int i = 0; i < N; i++) {
			if (abs(board[i][j] - target) > 1) {
				canGo = false;
				break;
			}

			if (board[i][j] == target)
				scount++;
			else if (board[i][j] < target) {
				vector<bool> v(N + 1, false);
				canGo = downDFS(i, j, 'D', v);
				break;
			}
			else {
				vector<bool> v(N + 1, false);
				canGo = upDFS(scount, i, j, 'D', v);
				break;
			}
		}
		if (canGo)
			answer++;
	}

	cout << answer;

	return 0;
}