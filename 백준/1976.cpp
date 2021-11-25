#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> board(202, vector<bool>(202)); // ���� �Է°�
vector<vector<int>> connected(202, vector<int>()); // �� ���ú� ����� ����
int N, M;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int num;
			cin >> num;
			if (num) { // 1 �Է� ���� ���
				board[i][j] = true;
				connected[i].push_back(j);
			}
			else // 0 �Է� ���� ���
				board[i][j] = false;
		}
	}

	// ��������� i ���÷κ��� j ���ñ��� �� �� �ִ����� ���� ����
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

			// cur ���ÿ� ����� ���õ��� �湮
			for (int k = 0; k < connected[cur].size(); k++) {
				if (visited[connected[cur][k]])
					continue;
				visited[connected[cur][k]] = true;
				canGo[i][connected[cur][k]] = true;
				q.push(connected[cur][k]);
			}
		}
	}

	// ���� ��θ� plan ���Ϳ� ����
	string str;
	getline(cin, str);
	getline(cin, str);

	vector<int> plan;
	stringstream ss(str);
	string tmp;
	while (getline(ss, tmp, ' ')) {
		plan.push_back(stoi(tmp));
	}

	// ù ��°���� ���� ��° ���÷� �� �� �ִ��� üũ
	for (auto it = plan.begin(); it != plan.end() - 1; it++) {
		if (!canGo[*it][*next(it, 1)]) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";

	return 0;
}