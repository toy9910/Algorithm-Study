#include <bits/stdc++.h>

using namespace std;

vector<bool> isPrime(10005, true);
vector<bool> check(10005, false);
vector<int> cow(10);
vector<int> tmp(10);
vector<int> answer;
int N, M;

void initPrime() {
	for (int i = 2; i <= sqrt(10000); i++) {
		if (isPrime[i]) {
			for (int j = i * 2; j <= 10000; j += i)
				isPrime[j] = false;
		}
	}
}

void func(int depth, int next) {
	if (depth == M) {
		int sum = 0;
		for (int i = 0; i < M; i++) {
			sum += tmp[i];
		}
		if (isPrime[sum] and !check[sum]) {
			answer.push_back(sum);
			check[sum] = true;
		}
		return;
	}

	for (int i = next; i <= N; i++) {
		tmp[depth] = cow[i];
		func(depth + 1, i + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	initPrime();

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> cow[i];
	}

	func(0, 1);
	sort(answer.begin(), answer.end());
	for (auto num : answer)
		cout << num << '\n';

	return 0;
}