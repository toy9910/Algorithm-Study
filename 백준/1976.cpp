#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> board(202, vector<bool>(202)); // 도시 입력값
vector<vector<int>> connected(202, vector<int>()); // 각 도시별 연결된 도시
int N, M;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int num;
			cin >> num;
			if (num) { // 1 입력 받은 경우
				board[i][j] = true;
				connected[i].push_back(j);
			}
			else // 0 입력 받은 경우
				board[i][j] = false;
		}
	}

	// 결론적으로 i 도시로부터 j 도시까지 갈 수 있는지에 대한 벡터
	vector<vector<bool>> canGo(202, vector<bool>(202, false));

	for (int i = 1; i <= N; i++) {
		vector<bool> visited(202, false);
		queue<int> q;
		q.push(i);
		canGo[i][i] = true;
		visited[i] = true;

		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			// cur 도시와 연결된 도시들을 방문
			for (int k = 0; k < connected[cur].size(); k++) {
				if (visited[connected[cur][k]])
					continue;
				visited[connected[cur][k]] = true;
				canGo[i][connected[cur][k]] = true;
				q.push(connected[cur][k]);
			}
		}
	}

	// 여행 경로를 plan 벡터에 저장
	string str;
	getline(cin, str);
	getline(cin, str);

	vector<int> plan;
	stringstream ss(str);
	string tmp;
	while (getline(ss, tmp, ' ')) {
		plan.push_back(stoi(tmp));
	}

	// 첫 번째부터 다음 번째 도시로 갈 수 있는지 체크
	for (auto it = plan.begin(); it != plan.end() - 1; it++) {
		if (!canGo[*it][*next(it, 1)]) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";

	return 0;
}