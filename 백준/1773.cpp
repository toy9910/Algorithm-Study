#include <bits/stdc++.h>

using namespace std;

bool arr[2000001];	// 해당 시간에 폭죽이 터지는지 확인하는 배열
vector<int> times;	// 폭죽이 터지는 시간들을 저장하는 벡터


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, C;
	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		for (int j = num; j <= C; j += num) {
			if (!arr[j]) {	// 해당 시간에 폭죽이 터지지 않는다면
				arr[j] = true;
				times.push_back(j);
			}
		}
	}

	cout << times.size();

	return 0;
}
