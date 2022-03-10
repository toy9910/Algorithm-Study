#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> connected(12, vector<bool>(31)); // i, i+1�� �������� j�� ������ ��ġ
vector<pair<int, int>> lines; // ���� �� �ִ� ������ �����ϴ� �迭
vector<pair<int, int>> tmp; // ���� ������ ����� ��
int N, M, H, answer;

void input() {
	cin >> N >> M >> H;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		connected[b][a] = true;
	}

	for (int i = 1; i <= H; i++) 
		for (int j = 1; j < N; j++) 
			if (!connected[j][i]) // i�� ������ j, j+1�� �������� ������ �� �����Ƿ� lines�� �ִ´�.
				lines.push_back({ j,i });
}

// ��ٸ� ��� Ȯ��
bool check() {
	for (int i = 1; i <= N; i++) {
		// ���� ���� ��ȣ
		int line = i;
		for (int j = 1; j <= H; j++) {
			// ���������� ����Ǿ� ������ + 1
			if (connected[line][j]) 
				line++;
			// �������� ����Ǿ� ������ - 1
			else if (connected[line - 1][j])
				line--;
		}
		// ���� ��ȣ�� �ٸ� ��� false ����
		if (line != i)
			return false;
	}
	return true;
}

void func(int depth, int next) {
	// ��� Ȯ��
	if (check()) 
		answer = min(answer, static_cast<int>(tmp.size()));

	if (tmp.size() == 3)
		return;

	for (int i = next; i < lines.size(); i++) {
		// �� ���� �׾��� ���� ���� ��� ���� �ߴ´�.
		if (!connected[lines[i].first - 1][lines[i].second] and !connected[lines[i].first + 1][lines[i].second]) {
			tmp.push_back(lines[i]);
			connected[lines[i].first][lines[i].second] = true;
			func(depth + 1, i + 1);

			tmp.pop_back();
			connected[lines[i].first][lines[i].second] = false;
		}
	}

}

void solve() {
	func(0, 0);
	if (answer > 3)
		cout << -1;
	else
		cout << answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	answer = 4;
	input();
	solve();
	
	return 0;
}