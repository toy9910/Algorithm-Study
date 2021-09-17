#include <bits/stdc++.h>

using namespace std;

bool arr[2000001];
vector<int> times;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, C;
	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		for (int j = num; j <= C; j += num) {
			if (!arr[j]) {
				arr[j] = true;
				times.push_back(j);
			}
		}
	}

	cout << times.size();

	return 0;
}