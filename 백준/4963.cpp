#include <bits/stdc++.h>

using namespace std;

int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);


	while (true) {
		int w, h;
		cin >> w >> h;
		if (w == 0 and h == 0)
			break;

		vector<vector<int>> board(h, vector<int>(w));
		vector<vector<bool>> visited(h, vector<bool>(w, false));
		int answer = 0;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> board[i][j];
			}
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (visited[i][j] or board[i][j] == 0)
					continue;
				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = true;
				answer++;

				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();

					for (int k = 0; k < 8; k++) {
						int xpos = cur.first + dx[k];
						int ypos = cur.second + dy[k];

						if (xpos < 0 or xpos >= h or ypos < 0 or ypos >= w)
							continue;
						if (visited[xpos][ypos] or board[xpos][ypos] == 0)
							continue;
						visited[xpos][ypos] = true;
						q.push({ xpos,ypos });
					}
				}
			}
		}

		cout << answer << '\n';
	}

	return 0;
}