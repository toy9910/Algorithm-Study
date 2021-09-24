#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> arr(301, vector<int>(301, 0));
vector<vector<int>> DP(301, vector<int>(301, 0));
int N, M, K;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
			if (i == 1 and j == 1)
				DP[i][j] = arr[i][j];
			else {
				if (i == 1) 
					DP[i][j] = DP[i][j - 1] + arr[i][j];
				else if (j == 1)
					DP[i][j] = DP[i - 1][j] + arr[i][j];
				else
					DP[i][j] = DP[i][j - 1] + DP[i - 1][j] - DP[i - 1][j - 1] + arr[i][j];
			}
		}
	}

	cin >> K;
	for (int k = 0; k < K; k++) {
		int i, j, x, y;
		cin >> i >> j >> x >> y;

		if (i == 1 and j == 1)
			cout << DP[x][y] << '\n';
		else {
			if (i == 1)
				cout << DP[x][y] - DP[x][j - 1] << '\n';
			else if (j == 1)
				cout << DP[x][y] - DP[i - 1][y] << '\n';
			else
				cout << DP[x][y] - DP[x][j - 1] - DP[i - 1][y] + DP[i - 1][j - 1] << '\n';
		}
	}

	return 0;
}