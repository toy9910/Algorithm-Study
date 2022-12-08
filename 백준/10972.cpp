#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> v;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
}

void solve() {
	if (next_permutation(v.begin(), v.end())) {
		for (auto n : v)
			cout << n << ' ';
	}
	else {
		cout << -1;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();


	return 0;
}