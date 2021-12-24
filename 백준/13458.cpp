#include <bits/stdc++.h>

using namespace std;

vector<int> people(1000001);
int N, B, C;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> people[i];
	}

	cin >> B >> C;

	long long answer = 0;
	for (int i = 0; i < N; i++) {
		int tmp = people[i] - B;
		answer++;
		if (tmp <= 0)
			continue;

		int remain = tmp % C;
		if (remain) 
			answer += ((tmp / C) + 1);
		else 
			answer += (tmp / C);
	}

	cout << answer;

	return 0;
}