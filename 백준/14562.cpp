#include <bits/stdc++.h>

using namespace std;

int C, S, T, answer;

void func(int score, int count) {
	if (score > T)
		return;

	if (score == T) {
		answer = min(count, answer);
		return;
	}

	// A ������
	T += 3;
	func(score * 2, count + 1);
	T -= 3;
	// B ������
	func(score + 1, count + 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> C;

	while (C--) {
		answer = 1000000;
		cin >> S >> T;
		func(S, 0);
		cout << answer << '\n';
	}


	return 0;
}