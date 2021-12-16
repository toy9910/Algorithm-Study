#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> people(51, vector<int>(51, 10000000));
int N;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	while(true) {
		int num1, num2;
		cin >> num1 >> num2;

		if (num1 == -1 and num2 == -1)
			break;

		people[num1][num2] = 1;
		people[num2][num1] = 1;
	}


	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (i == j) {
					people[i][j] = 0;
					continue;
				}
				people[i][j] = min(people[i][j], people[i][k] + people[k][j]);
			}
		}
	}

	
	int mCount = 0;
	int mNum = 10000000;
	vector<int> v(51);

	for (int i = 1; i <= N; i++) {
		int tmp = 0;
		for (int j = 1; j <= N; j++) {
			tmp = max(tmp, people[i][j]);
		}
		v[i] = tmp;
		mNum = min(tmp, mNum);
	}

	vector<int> answer;
	for (int i = 1; i <= N; i++) {
		if (v[i] == mNum) {
			mCount++;
			answer.push_back(i);
		}
	}

	cout << mNum << " " << mCount << "\n";
	for (auto num : answer)
		cout << num << " ";

	return 0;
}