#include <bits/stdc++.h>

using namespace std;

int N, K, W[105], V[105], DP[105][100001];

void input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		cin >> W[i] >> V[i];
	}
}

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			if (j - W[i] >= 0) DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - W[i]] + V[i]);
			else DP[i][j] = DP[i - 1][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();
	cout << DP[N][K];

	return 0;
}