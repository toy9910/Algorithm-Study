#include <bits/stdc++.h>

using namespace std;

vector<bool> check(5005, false);	// 출석한 학생
vector<bool> drowsy(5005, false);	// 졸린 학생
vector<int> DP(5005, 0);	// 3번째부터 i번째까지 출석 안 한 학생
int N, K, Q, M, S, E;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K >> Q >> M;

	for (int i = 0; i < K; i++) {
		int num;
		cin >> num;
		drowsy[num] = true;
	}

	for (int i = 0; i < Q; i++) {
		int num;
		cin >> num;

		// 첫 학생이 졸고 있을 경우 출석 코드를 보내지 않는다.
		if (drowsy[num])
			continue;

		for (int j = num; j <= N + 2; j += num) {
			if (!drowsy[j])
				check[j] = true;
		}
	}

	if (!check[3])
		DP[3] = 1;

	for (int i = 4; i <= N + 2; i++) {
		if (!check[i]) 
			DP[i] = DP[i - 1] + 1;
		else 
			DP[i] = DP[i - 1];
	}

	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		cout << DP[E] - DP[S - 1] << '\n';
	}

	return 0;
}