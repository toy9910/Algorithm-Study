#include <bits/stdc++.h>

using namespace std;

vector<int>	D(101);
vector<int> snow(101);
int N, M;
int answer = 0;

void func(int time, int size, int pos) {
	if (time == M or pos >= N) {
		answer = max(size, answer);
		return;
	}


	for (int i = 1; i <= 2; i++) {
		if (i == 1) {
			func(time + 1, size + snow[pos + i], pos + i);
		}
		else
			func(time + 1, (size / 2) + snow[pos + i], pos + i);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		cin >> snow[i];
	}
	
	func(0,1,0);
	cout << answer;

	return 0;
}