#include <bits/stdc++.h>

using namespace std;

vector<int> t1 = { 0,0,0,0,0,1,1,1,1,2,2,2,3,3,4 };
vector<int> t2 = { 1,2,3,4,5,2,3,4,5,3,4,5,4,5,5 };
int match[6][3], result[6][3], answer[4];

void input() {
	for (int j = 0; j < 6; j++) {
		for (int c = 0; c < 3; c++) {
			cin >> match[j][c];
		}
	}
}

void dfs(int t, int round) {
	if (round == 15) {
		bool flag = true;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				if (result[i][j] != match[i][j]) {
					flag = false;
					break;
				}
			}
			if (!flag) break;
		}

		if (flag) answer[t] = 1;
		return;
	}

	int team1 = t1[round];
	int team2 = t2[round];

	// team1 ½Â, team2 ÆÐ
	result[team1][0]++; result[team2][2]++;
	dfs(t, round + 1);
	result[team1][0]--; result[team2][2]--;

	// team1, team2 ¹«½ÂºÎ
	result[team1][1]++; result[team2][1]++;
	dfs(t, round + 1);
	result[team1][1]--; result[team2][1]--;

	// team1 ÆÐ, team2 ½Â
	result[team1][2]++; result[team2][0]++;
	dfs(t, round + 1);
	result[team1][2]--; result[team2][0]--;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		input();
		dfs(i, 0);
		
	}
	for (int i = 0; i < 4; i++) cout << answer[i] << " ";

	return 0;
}