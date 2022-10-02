#include <bits/stdc++.h>

using namespace std;


int board[205][205], r, c, k, answer, maxR = 3, maxC = 3;

class pp {
	public:
		int num, count;

		pp(int num, int count) {
			this->num = num;
			this->count = count;
		}
};

bool cmp(pp a, pp b) {
	if (a.count != b.count)
		return a.count < b.count;
	return a.num < b.num;
}

void input() {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) 
		for (int j = 1; j <= 3; j++) 
			cin >> board[i][j];
}

void sortR() {
	for (int i = 1; i <= maxR; i++) {
		vector<int> tmp;
		for (int j = 1; j <= maxC; j++) {
			if (board[i][j] != 0)
				tmp.push_back(board[i][j]);
		}
		sort(tmp.begin(), tmp.end());

		vector<pp> v;
		int index = 1, prevNum = tmp[0], count = 1;
		while (index < tmp.size()) {
			if (prevNum != tmp[index]) {
				v.push_back(pp(prevNum, count));
				count = 1;
				prevNum = tmp[index];
			}
			else {
				count++;
			}
			index++;
		}
		v.push_back(pp(prevNum, count));

		sort(v.begin(), v.end(), cmp);
		int curC = v.size() <= 50 ? v.size() * 2 : 100;
		for (int j = 1; j <= curC; j+=2) {
			board[i][j] = v[j / 2].num;
			board[i][j + 1] = v[j / 2].count;
		}
		if (curC < maxC) {
			for (int j = curC + 1; j <= maxC; j++) board[i][j] = 0;
		}
		else maxC = curC;
	}
}

void sortC() {
	for (int j = 1; j <= maxC; j++) {
		vector<int> tmp;
		for (int i = 1; i <= maxR; i++) {
			if(board[i][j] != 0)
				tmp.push_back(board[i][j]);
		}
		sort(tmp.begin(), tmp.end());

		vector<pp> v;
		int index = 1, prevNum = tmp[0], count = 1;
		while (index < tmp.size()) {
			if (prevNum != tmp[index]) {
				v.push_back(pp(prevNum, count));
				count = 1;
				prevNum = tmp[index];
			}
			else {
				count++;
			}
			index++;
		}
		v.push_back(pp(prevNum, count));

		sort(v.begin(), v.end(), cmp);
		int curR = v.size() <= 50 ? v.size() * 2 : 100;
		for (int i = 1; i <= curR; i += 2) {
			board[i][j] = v[i / 2].num;
			board[i + 1][j] = v[i / 2].count;
		}
		if (curR < maxR)
			for (int i = curR + 1; i <= maxR; i++) board[i][j] = 0;
		else maxR = curR;
	}
}

void solve() {
	while (board[r][c] != k and answer <= 100) {
		if (maxR >= maxC)
			sortR();
		else
			sortC();
		answer++;
	}
	if (answer > 100)
		answer = -1;
	cout << answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}