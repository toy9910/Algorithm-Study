#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board(51, vector<int>(51));
vector<tuple<int, int, int>> oper; // 연산들
vector<tuple<int, int, int>> tmp_oper; // 순열을 사용한 연산 조합
vector<bool> visited(6);
int N, M, K, answer;

void input() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> board[i][j];
	for (int i = 0; i < K; i++) {
		int r, c, s;
		cin >> r >> c >> s;
		oper.push_back({ r,c,s });
	}
}

// 해당 배열의 값 구하는 함수
int getSum(vector<vector<int>> b) {
	int mini = 987654321;
	for (int i = 1; i <= N; i++) {
		int sum = 0;
		for (int j = 1; j <= M; j++) 
			sum += b[i][j];
		mini = min(mini, sum);
	}
	return mini;
}

// 회전하는 함수
void spin(vector<vector<int>>& b, pair<int, int> tl, pair<int, int> br) {
	while (tl != br) {
		for (int i = tl.first; i < br.first; i++) {
			swap(b[i][tl.second], b[i + 1][tl.second]);
		}
		for (int j = tl.second; j < br.second; j++) {
			swap(b[br.first][j], b[br.first][j + 1]);
		}
		for (int i = br.first; i > tl.first; i--) {
			swap(b[i][br.second], b[i - 1][br.second]);
		}
		for (int j = br.second; j > tl.second + 1; j--) {
			swap(b[tl.first][j], b[tl.first][j - 1]);
		}
		tl = { tl.first + 1, tl.second + 1 };
		br = { br.first - 1, br.second - 1 };
	}
	
}

void Execute(vector<vector<int>> b) {
	for (auto t : tmp_oper) {
		pair<int, int> tl = { get<0>(t) - get<2>(t),get<1>(t) - get<2>(t) };
		pair<int, int> br = { get<0>(t) + get<2>(t), get<1>(t) + get<2>(t) };
		spin(b, tl, br);
	}
	answer = min(answer, getSum(b));
}

// 순열을 사용해서 연산들을 조합한다.
void func(int depth) {
	if (depth == oper.size()) {
		Execute(board);
		return;
	}

	for (int i = 0; i < oper.size(); i++) {
		if (!visited[i]) {
			visited[i] = true;
			tmp_oper.push_back(oper[i]);
			func(depth + 1);
			tmp_oper.pop_back();
			visited[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	answer = 987654321;
	input();
	func(0);
	cout << answer;

	return 0;
}