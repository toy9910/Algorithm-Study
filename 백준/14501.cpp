#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> v(16); // �� ��¥�� �޴� �ݾ�
vector<int> money; // �޴� �ݾ�
int N, answer;

void func(int depth) {
	if (depth > N) {
		int sum = 0;
		if(depth == N + 1) // ������ ��㳯�� N��° �Ǵ� ���� ���
			for (auto it = money.begin(); it != money.end(); it++)
				sum += *it;
		else // ������ ��㳯�� N�Ϻ��� �� ū ���
			for (auto it = money.begin(); it != money.end() - 1; it++)
				sum += *it;
	
		answer = max(answer, sum);
		return;
	}

	for (int i = depth; i <= N; i++) {
		money.push_back(v[i].second);
		func(i + v[i].first);
		money.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		int days, pay;
		cin >> days >> pay;

		v[i] = { days,pay };
	}

	answer = 0;
	func(1);

	cout << answer;

	return 0;
}