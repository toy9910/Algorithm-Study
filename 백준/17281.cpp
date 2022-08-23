#include <bits/stdc++.h>

using namespace std;

bool used[10];	// ������ ���� ��ġ�� ����ߴ��� ����
vector<bool> exist(5, false);	// ���ڰ� �ִ��� ����
int players[55][10], N, orders[10], answer;	// players : �� ������ ���� ����, orders : ���� ��ġ ����

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> players[i][j];
		}
	}

	// 1��° ������ 4��°�� ����
	orders[4] = 1;
	used[1] = true;
}

// ���ڵ��� 1�羿 �ű��.
// ���ڷ� ������ �޾ƿ� 3�� ���ڰ� Ȩ���ϸ� call by reference�� ���� ������Ʈ �Ѵ�.
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

// ���� ����ϴ� �Լ�
int calc() {
	// cur : ���� Ÿ��
	int cur = 1, out = 0, score = 0;
	for (int in = 1; in <= N; in++) {
		// �� �̴׸��� �ƿ�ī��Ʈ, ���� ���� �ʱ�ȭ
		out = 0;
		fill(exist.begin(), exist.end(), false);

		while (out < 3) {
			if (players[in][orders[cur]] == 0) out++;
			else if (players[in][orders[cur]] == 4) { // Ȩ���� ���
				// ������ ���� ����.
				int cnt = 1;
				for (int i = 1; i <= 3; i++) 
					if (exist[i]) cnt++;
				// Ȩ���� ġ�� ��� ���ڴ� Ȩ�� �����Ƿ� ���� ���� �ʱ�ȭ
				fill(exist.begin(), exist.end(), false);
				score += cnt;
			}
			else {
				// ��Ÿ, 2��Ÿ, 3��Ÿ��ŭ ���ڸ� �ű��.
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

	// 4�� Ÿ�ڴ� �̹� 1�� �����̹Ƿ� ��ŵ
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