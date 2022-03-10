#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> connected(12, vector<bool>(31)); // i, i+1번 세로줄이 j번 점선에 위치
vector<pair<int, int>> lines; // 그을 수 있는 선들을 저장하는 배열
vector<pair<int, int>> tmp; // 선을 선택한 경우의 수
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
			if (!connected[j][i]) // i번 점선에 j, j+1번 세로줄을 연결할 수 있으므로 lines에 넣는다.
				lines.push_back({ j,i });
}

// 사다리 결과 확인
bool check() {
	for (int i = 1; i <= N; i++) {
		// 현재 줄의 번호
		int line = i;
		for (int j = 1; j <= H; j++) {
			// 오른쪽으로 연결되어 있으면 + 1
			if (connected[line][j]) 
				line++;
			// 왼쪽으로 연결되어 있으면 - 1
			else if (connected[line - 1][j])
				line--;
		}
		// 시작 번호와 다를 경우 false 리턴
		if (line != i)
			return false;
	}
	return true;
}

void func(int depth, int next) {
	// 결과 확인
	if (check()) 
		answer = min(answer, static_cast<int>(tmp.size()));

	if (tmp.size() == 3)
		return;

	for (int i = next; i < lines.size(); i++) {
		// 양 옆에 그어진 선이 없을 경우 선을 긋는다.
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