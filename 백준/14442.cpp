#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

#define INF 987654321

int N, M, K, board[1001][1001], dist[1001][1001][11], answer;

//struct cmp {
//	bool operator()(tuple<int, int, int> t1, tuple<int, int, int> t2) {
//		int tx1, ty1, tb1, tx2, ty2, tb2;
//		tie(tx1, ty1, tb1) = t1;	tie(tx2, ty2, tb2) = t2;
//		int dist1 = (N - tx1) + (M - ty1), dist2 = (N - tx2) + (M - ty2);
//		return dist1 > dist2;
//	}
//};

void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			board[i][j + 1] = str[j] - '0';
			for(int k=0;k<=K;k++)
				dist[i][j + 1][k] = INF;
		}
	}
}

void solve() {
	answer = INF;

	queue<tuple<int, int, int>> pq;
	pq.push({ 1,1,0 });
	dist[1][1][0] = 1;

	while (!pq.empty()) {
		int curx, cury, curb;
		tie(curx,cury,curb) = pq.front();
		pq.pop();

		if (curx == N and cury == M and curb <= K) {
			answer = min(answer, dist[N][M][curb]);
			continue;
		}

		for (int k = 0; k < 4; k++) {
			int xpos = curx + dx[k], ypos = cury + dy[k];
			if (xpos < 1 or xpos > N or ypos < 1 or ypos > M) continue;

			if (board[xpos][ypos] == 1) {
				if (curb == K) continue;
				if (dist[xpos][ypos][curb + 1] <= dist[curx][cury][curb] + 1) continue;
				dist[xpos][ypos][curb + 1] = dist[curx][cury][curb] + 1;
				pq.push(make_tuple(xpos, ypos, curb + 1));
			}
			else {
				if (dist[xpos][ypos][curb] <= dist[curx][cury][curb] + 1) continue;
				dist[xpos][ypos][curb] = dist[curx][cury][curb] + 1;
				pq.push(make_tuple(xpos, ypos, curb));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();
	if (answer == INF)
		answer = -1;
	cout << answer;

	return 0;
}