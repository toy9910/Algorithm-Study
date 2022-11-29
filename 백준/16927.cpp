#include <bits/stdc++.h>

using namespace std;

int N, M, R, board[305][305];

void input() {
	cin >> N >> M >> R;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			cin >> board[i][j];
}

void rotate(int num) {
	pair<int, int> start = make_pair(0, 0), end = make_pair(N - 1, M - 1);

	while (start.first < end.first) {
		int counts = ((end.first - start.first) * 2) + ((end.second - start.second) * 2);
		for (int k = 0; k < num % counts; k++) {
			int tmp = board[start.first][start.second];
			for (int j = start.second + 1; j <= end.second; j++) {
				board[start.first][j - 1] = board[start.first][j];
			}
			for (int i = start.first + 1; i <= end.first; i++) {
				board[i - 1][end.second] = board[i][end.second];
			}
			for (int j = end.second - 1; j >= start.second; j--) {
				board[end.first][j + 1] = board[end.first][j];
			}
			for (int i = end.first - 1; i > start.first; i--) {
				board[i + 1][start.second] = board[i][start.second];
			}
			board[start.first + 1][start.second] = tmp;
		}
		start = make_pair(start.first + 1, start.second + 1);
		end = make_pair(end.first - 1, end.second - 1);
	}
}

void solve() {
	rotate(R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
		

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();
	
	return 0;
}