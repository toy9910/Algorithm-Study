#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

vector<pair<int, int>> B;
char board[55][55];
bool visited[55][55][2];
int N, answer;


void input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		string tmp;
		cin >> tmp;

		for (int j = 0; j < tmp.length(); j++) {
			if (tmp[j] == 'B') {
				B.push_back({ i, j });
				board[i][j] = '0';
			}
			else {
				board[i][j] = tmp[j];
			}
		}
	}
}

bool isArrived(vector<pair<int, int>> B) {
	for (int i = 0; i < 3; i++)
		if (board[B[i].first][B[i].second] != 'E')
			return false;
	return true;
}


bool canMove(int dir, vector<pair<int, int>> B) {
	int x1, y1, x2 = B[1].first, y2 = B[1].second, x3, y3;

	if (dir < 4) {
		x1 = B[0].first + dx[dir], y1 = B[0].second + dy[dir];
		x2 = B[1].first + dx[dir], y2 = B[1].second + dy[dir];
		x3 = B[2].first + dx[dir], y3 = B[2].second + dy[dir];
	}
	else {
		for (int i = B[1].first - 1; i <= B[1].first + 1; i++) {
			for (int j = B[1].second - 1; j <= B[1].second + 1; j++) {
				if (board[i][j] == '1')
					return false;
			}
		}
		if (B[0].first == B[1].first) {
			x1 = B[1].first - 1, y1 = B[1].second;
			x3 = B[1].first + 1, y3 = B[1].second;
		}
		else {
			x1 = B[1].first, y1 = B[1].second - 1;
			x3 = B[1].first, y3 = B[1].second + 1;
		}
	}

	if (x1 < 0 or x1 >= N or x2 < 0 or x2 >= N or x3 < 0 or x3 >= N or
		y1 < 0 or y1 >= N or y2 < 0 or y2 >= N or y3 < 0 or y3 >= N)
		return false;

	if (board[x1][y1] == '1' or board[x2][y2] == '1' or board[x3][y3] == '1')
		return false;

	if (x1 == x2) {
		if (visited[x1][y1][0] and visited[x3][y3][0])
			return false;
	}
	else {
		if (visited[x1][y1][1] and visited[x3][y3][1])
			return false;
	}
	

	return true;
}

void move(int dir, vector<pair<int, int>>& B) {
	if (dir < 4) {
		int x1 = B[0].first + dx[dir], y1 = B[0].second + dy[dir];
		int x2 = B[1].first + dx[dir], y2 = B[1].second + dy[dir];
		int x3 = B[2].first + dx[dir], y3 = B[2].second + dy[dir];

		B[0] = { x1, y1 };
		B[1] = { x2, y2 };
		B[2] = { x3, y3 };
	}
	else {
		if (B[0].first == B[1].first) {
			B[0] = { B[1].first - 1, B[1].second };
			B[2] = { B[1].first + 1, B[1].second };
		}
		else {
			B[0] = { B[1].first, B[1].second - 1 };
			B[2] = { B[1].first, B[1].second + 1 };
		}
	}
}

bool checkVisited(vector<pair<int, int>> B) {
	if (B[0].first == B[1].first) {
		if (visited[B[0].first][B[0].second][0] and visited[B[2].first][B[2].second][0])
			return true;
	}
	else {
		if (visited[B[0].first][B[0].second][1] and visited[B[2].first][B[2].second][1])
			return true;
	}
	
	return false;
}

void solve() {
	priority_queue<pair<int, vector<pair<int, int>>>> pq;
	if (B[0].first == B[1].first) {
		visited[B[0].first][B[0].second][0] = true;
		visited[B[2].first][B[2].second][0] = true;
	}
	else {
		visited[B[0].first][B[0].second][1] = true;
		visited[B[2].first][B[2].second][1] = true;
	}
	
	pq.push({ 0, B });

	while (!pq.empty()) {
		auto cur = pq.top();
		int cost = -cur.first;
		pq.pop();

		if (isArrived(cur.second)) {
			answer = -cur.first;
			cout << answer;
			return;
		}

		for (int k = 0; k < 5; k++) {
			if (!canMove(k, cur.second))
				continue;

			vector<pair<int, int>> tmp = cur.second;

			move(k, tmp);
			if (tmp[0].first == tmp[1].first) {
				visited[tmp[0].first][tmp[0].second][0] = true;
				visited[tmp[2].first][tmp[2].second][0] = true;
			}
			else {
				visited[tmp[0].first][tmp[0].second][1] = true;
				visited[tmp[2].first][tmp[2].second][1] = true;
			}
			
			pq.push({ -(cost + 1), tmp });
		}
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