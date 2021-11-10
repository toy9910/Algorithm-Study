#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board(51, vector<int>(51));
vector<pair<int, int>> house;
vector<pair<int, int>> chicken;
vector<pair<int, int>> tmp_chicken;
int N, M, answer;

void func(int depth, int next) {
	if (depth == M) {
		int sum = 0;
		for (auto cur : house) {
			int mini = 1000000;
			for (auto chick : tmp_chicken) {
				mini = min(mini, abs(cur.first - chick.first) + abs(cur.second - chick.second));
			}
			sum += mini;
		}
		answer = min(sum, answer);
		return;
	}

	for (int i = next; i < chicken.size(); i++) {
		tmp_chicken.push_back(chicken[i]);
		func(depth + 1, i + 1);
		tmp_chicken.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	answer = 1000000;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int num;
			cin >> num;

			board[i][j] = num;

			switch (num) {
			case 1: {
				house.push_back({ i,j });
				break;
			}
			case 2: {
				chicken.push_back({ i, j });
				break;
			}
			}
		}
	}

	func(0, 0);
	cout << answer;
	
	return 0;
}