#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<int>> board(51, vector<int>(51));
vector<pair<int, int>> virus;
vector<pair<int, int>> tmp(11);
vector<int> answers;
int N, M,answer, zcount;

void func(int depth, int next) {
	if (depth == M) {
		answer = 0;
		vector<vector<int>> dis(51, vector<int>(51, 0));
		vector<vector<bool>> visited(51, vector<bool>(51, false));
		queue<pair<int, int>> q;


		for (int i = 0; i < M; i++) {
			q.push({ tmp[i] });
			visited[tmp[i].first][tmp[i].second] = true;
		}

		int ccount = 0;
		
		
		while (!q.empty()) {
			auto cur = q.front();
			q.pop();

			for (int k = 0; k < 4; k++) {
				int xpos = cur.first + dx[k];
				int ypos = cur.second + dy[k];

				if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N)
					continue;
				if (board[xpos][ypos] == 1 or visited[xpos][ypos]) // 벽 또는 바이러스인 경우, 이미 방문한 경우
					continue;
				if (board[xpos][ypos] == 0) // 빈 칸 -> 바이러스 체크
					ccount++;
				dis[xpos][ypos] = dis[cur.first][cur.second] + 1;
				if (zcount == ccount) {
					answer = max(dis[xpos][ypos], answer);
					answers.push_back(answer);
					return;
				}
				dis[xpos][ypos] = dis[cur.first][cur.second] + 1;
				visited[xpos][ypos] = true;
				q.push({ xpos,ypos });
			}
		} 
		
		/*
		* cout << '\n';
		 for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << dis[i][j] << ' ';
			}
			cout << '\n';
		}
		 cout << '\n';
		*/
		
		
		
		
			
	}
	else {
		for (int i = next; i < virus.size(); i++) {
			tmp[depth] = virus[i];
			func(depth + 1, i + 1);
		}
	}
	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	zcount = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2)
				virus.push_back({ i,j });
			else if (board[i][j] == 0)
				zcount++;
		}
	}

	if (zcount == 0) {
		cout << 0;
		return 0;
	}

	func(0, 0);
	if (!answers.empty()) {
		sort(answers.begin(), answers.end());
		cout << answers[0];
	}
	else
		cout << -1;

	//for (auto num : answers)
		//cout << num << '\n';

	return 0;
}