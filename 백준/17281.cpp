#include <bits/stdc++.h>

using namespace std;

bool used[10];	// 선수를 순서 배치에 사용했는지 여부
vector<bool> exist(5, false);	// 주자가 있는지 여부
int players[55][10], N, orders[10], answer;	// players : 각 선수별 득점 정보, orders : 선수 배치 순서

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> players[i][j];
		}
	}

	// 1번째 선수는 4번째로 고정
	orders[4] = 1;
	used[1] = true;
}

// 주자들을 1루씩 옮긴다.
// 인자로 점수를 받아와 3루 주자가 홈인하면 call by reference로 값을 업데이트 한다.
void move(int &s) {
	if (exist[3]) {
		s++;
		exist[3] = false;
	}
	if (exist[2]) {
		exist[3] = true;
		exist[2] = false;
	}
	if (exist[1]) {
		exist[2] = true;
		exist[1] = false;
	}
}

// 점수 계산하는 함수
int calc() {
	// cur : 현재 타순
	int cur = 1, out = 0, score = 0;
	for (int in = 1; in <= N; in++) {
		// 매 이닝마다 아웃카운트, 주자 정보 초기화
		out = 0;
		fill(exist.begin(), exist.end(), false);

		while (out < 3) {
			if (players[in][orders[cur]] == 0) out++;
			else if (players[in][orders[cur]] == 4) { // 홈런인 경우
				// 주자의 수를 센다.
				int cnt = 1;
				for (int i = 1; i <= 3; i++) 
					if (exist[i]) cnt++;
				// 홈런을 치면 모든 주자는 홈에 들어오므로 주자 정보 초기화
				fill(exist.begin(), exist.end(), false);
				score += cnt;
			}
			else {
				// 안타, 2루타, 3루타만큼 주자를 옮긴다.
				for (int i = 0; i < players[in][orders[cur]]; i++) move(score);
				exist[players[in][orders[cur]]] = true;
			}
			cur++;
			if (cur == 10) cur = 1;
		}
	}
	return score;
}

void comb(int depth) {
	if (depth == 10) {
		answer = max(answer, calc());
		return;
	}

	// 4번 타자는 이미 1번 선수이므로 스킵
	if (depth == 4) 
		comb(5);
	else {
		for (int i = 1; i <= 9; i++) {
			if (used[i]) continue;
			orders[depth] = i;
			used[i] = true;
			comb(depth + 1);
			used[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	comb(1);
	cout << answer;

	return 0;
}