#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

int N, M;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	if (N == 1 and M == 1) {
		cout << 1;
		return 0;
	}

	vector<vector<int>> board(1001, vector<int>(1001, 0)); // 맵
	// 출발지 ~ 해당 위치까지의 거리
	// 3차원 배열의 0번째는 벽을 뚫지 않고 온 경우의 거리를 뜻하고
	// 1번째는 벽을 뚫고 온 경우의 거리를 뜻한다.
	// dis[5][3][1] = 10 인 경우 5,3까지 벽을 한 번 뚫고 10칸 걸린다는 뜻
	vector<vector<vector<int>>> dis(1001, vector<vector<int>>(1001, vector<int>(2, 0))); 

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;

		for (int j = 0; j < str.length(); j++) {
			board[i][j] = str[j] - '0';
		}
	}

	// 튜플은 { 행, 열, 현재 위치까지 벽을 뚫고 왔는지에 대한 여부 } 을 뜻한다.
	// 세번째 값이 0인 경우는 벽을 뚫고 오지 않음, 1인 경우 벽을 뚫고 왔다는 뜻
	queue<tuple<int,int,int>> q;
	q.push({ 0,0,0 });

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) {
			int xpos = get<0>(cur) + dx[k];
			int ypos = get<1>(cur) + dy[k];

			if (xpos == 0 and ypos == 0)
				continue;

			if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
				continue;

			if (get<2>(cur) > 0) {	// 벽을 부수고 온 경우
				if (board[xpos][ypos] < 1) { // 다음이 벽이 아닌 경우
					if (dis[xpos][ypos][1] == 0) {	// 다음 위치가 벽을 부수고 방문한 경우가 없을 때
						dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][1] + 1;
						q.push({ xpos,ypos,1 });
					}
					else { // 다음 위치가 벽을 부수고 방문한 경우가 있을 때
						// 거리를 비교한다.
						if (dis[xpos][ypos][1] > dis[get<0>(cur)][get<1>(cur)][1] + 1) {
							dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][1] + 1;
							q.push({ xpos,ypos,1 });
						}
					}
				}
			}
			else {	// 벽을 안부수고 온 경우
				if (board[xpos][ypos] < 1) { // 다음이 벽이 아닌 경우
					if (dis[xpos][ypos][0] == 0) {	// 다음 위치가 벽을 안부수고 방문한 경우가 없을 때
						dis[xpos][ypos][0] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
						q.push({ xpos,ypos,0 });
					}
					else { // 다음 위치가 벽을 안부수고 방문한 경우가 있을 때
						// 거리를 비교한다.
						if (dis[xpos][ypos][0] > dis[get<0>(cur)][get<1>(cur)][0] + 1) {
							dis[xpos][ypos][0] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
							q.push({ xpos,ypos,0});
						}
					}
				}
				else { // 다음 위치가 벽인 경우
					if (dis[xpos][ypos][1] > 0) { // 다음 위치가 벽을 부수고 방문한 경우가 있을 때
						// 거리를 비교한다.
						if (dis[xpos][ypos][1] > dis[get<0>(cur)][get<1>(cur)][0] + 1) {
							dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
							q.push({ xpos,ypos,1 });
						}
					}
					else { // 다음 위치가 벽을 부수고 방문한 경우가 없을 때
						dis[xpos][ypos][1] = dis[get<0>(cur)][get<1>(cur)][0] + 1;
						q.push({ xpos,ypos, 1 });
					}
				}
			}
		}
	}

	// 목적지에 도착을 못한 경우
	if (max(dis[N - 1][M - 1][0], dis[N - 1][M - 1][1]) == 0)
		cout << -1;
	else { // 목적지에 벽을 부수고 오거나, 벽을 부수지 않고 도착한 경우
		if (dis[N - 1][M - 1][0] > 0 and dis[N - 1][M - 1][1] > 0)
			// 벽을 부수고 온 경우와 벽을 부수고 오지 않은 경우 둘 다 있을 때
			// 둘 중 작은 것을 출력해야 한다.
			cout << min(dis[N - 1][M - 1][0], dis[N - 1][M - 1][1]) + 1;
		else
			// 벽을 부수고 온 경우와 벽을 부수고 오지 않은 경우 중 하나만 있을 때
			// 벽을 부수고 온 경우는 0이므로 둘 중 큰 값을 출력해야 한다.
			cout << max(dis[N - 1][M - 1][0], dis[N - 1][M - 1][1]) + 1;
	}

	return 0;
}