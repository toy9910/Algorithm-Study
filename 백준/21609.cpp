#include <bits/stdc++.h>

using namespace std;

#define INF -5

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

int N, M, board[25][25], answer;
vector<vector<pair<int, int>>> groups;

bool cmp1(pair<int, int> p1, pair<int, int> p2) {
	if (p1.first != p2.first) return p1.first < p2.first;
	return p1.second < p2.second;
}

bool cmp2(vector<pair<int, int>> v1, vector<pair<int, int>> v2) {
	if (v1.size() != v2.size()) return v1.size() > v2.size();
	int cnt1 = 0, cnt2 = 0;
	for (auto p : v1) 
		if (board[p.first][p.second] == 0) cnt1++;
	for (auto p : v2)
		if (board[p.first][p.second] == 0) cnt2++;
	if (cnt1 != cnt2) return cnt1 > cnt2;

	sort(v1.begin(), v1.end(), cmp1);
	sort(v2.begin(), v2.end(), cmp1);

	pair<int, int> p1, p2;
	for (auto p : v1) {
		if (board[p.first][p.second] > 0) {
			p1 = p;
			break;
		}
	}

	for (auto p : v2) {
		if (board[p.first][p.second] > 0) {
			p2 = p;
			break;
		}
	}

	if (p1.first != p2.first) return p1.first > p2.first;
	return p1.second > p2.second;
}

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

void getGroups() {
	groups.clear();
	vector<vector<bool>> visited(25, vector<bool>(25, false));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] or board[i][j] < 1) continue;
			queue<pair<int, int>> q;
			vector<pair<int, int>> tmp;
			vector<vector<bool>> visited0(25, vector<bool>(25, false));

			visited[i][j] = true;
			q.push(make_pair(i, j));
			tmp.push_back({ i,j });

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k], ypos = cur.second + dy[k];

					if (xpos < 1 or xpos > N or ypos < 1 or ypos > N) continue;
					if (visited[xpos][ypos] or board[xpos][ypos] == -1) continue;
					if (board[xpos][ypos] > 0 and board[xpos][ypos] != board[i][j]) continue;
					if (board[xpos][ypos] > 0) {
						visited[xpos][ypos] = true;
						q.push({ xpos,ypos });
						tmp.push_back({ xpos,ypos });
					}
					else if(board[xpos][ypos] == 0) {
						if (!visited0[xpos][ypos]) {
							visited0[xpos][ypos] = true;
							q.push({ xpos,ypos });
							tmp.push_back({ xpos,ypos });
						}
					}
				}
			}
			if (tmp.size() > 1) groups.push_back(tmp);
		}
	}
}

void doGravity() {
	for (int j = 1; j <= N; j++) {
		for (int i = N - 1; i > 0; i--) {
			if (board[i][j] == -1 or board[i][j] == INF) continue;
			int next = i + 1, before = i;
			while (next <= N and board[next][j] == INF) {
				board[next][j] = board[before][j];
				board[before][j] = INF;
				next++; before++;
			}
		}
	}
}

void rotate() {
	int tmp[25][25];
	copy(&board[0][0], &board[0][0] + 625, &tmp[0][0]);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			board[N-j+1][i] = tmp[i][j];
		}
	}
}


void solve() {
	while (true) {
		getGroups();
		if (groups.empty()) break;

		sort(groups.begin(), groups.end(), cmp2);
		vector<pair<int, int>> bg = groups[0];

		for (auto p : bg)
			board[p.first][p.second] = INF;
		answer += (bg.size() * bg.size());
		doGravity();
		rotate();
		doGravity();
	}
	cout << answer;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}