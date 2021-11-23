#include <bits/stdc++.h>

using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

vector<vector<char>> board(51, vector<char>(51));
int R, C;

// 고슴도치가 해당 칸에 갈 수 있는지 확인하는 함수
// 해당 칸이 물이 찰 예정이면 갈 수 없다.
bool canGo(pair<int,int> cur) {
	for (int k = 0; k < 4; k++) {
		int xpos = cur.first + dx[k];
		int ypos = cur.second + dy[k];

		if (xpos < 0 or xpos >= R or ypos < 0 or ypos >= C)
			continue;
		if (board[xpos][ypos] == '*')
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C;

	pair<int, int> dPos, sPos;
	queue<tuple<int, int, int>> q; // 3번째 값은 0이면 고슴도치고 1이면 물이라는 뜻이다.
	vector<pair<int, int>> dv; // 물의 위치들 저장

	for (int i = 0; i < R; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < C; j++) {
			board[i][j] = str[j];

			switch (str[j]) {
			case 'D': {
				dPos = { i,j };
				break;
			}
			case 'S': {
				sPos = { i,j };
				// 고슴도치를 먼저 움직이기 위해 먼저 큐에 삽입
				q.push({ sPos.first,sPos.second,0 });
				break;
			}
			case '*': {
				dv.push_back({ i,j });
				break;
			}
			}
		}
	}

	
	vector<vector<int>> dis(51, vector<int>(51, 0)); // 고슴도치의 시작점으로부터의 거리
	vector<vector<bool>> visited(51, vector<bool>(51, false));

	// 물의 위치들을 큐에 삽입
	for (auto pos : dv) 
		q.push({ pos.first, pos.second, 1 });
	
	visited[sPos.first][sPos.second] = true;

	int answer = 0;

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();

		if (get<2>(cur) == 0 and get<0>(cur) == dPos.first and get<1>(cur) == dPos.second) {
			answer = dis[dPos.first][dPos.second];
			break;
		}

		for (int k = 0; k < 4; k++) {
			int xpos = get<0>(cur) + dx[k];
			int ypos = get<1>(cur) + dy[k];

			if (xpos < 0 or xpos >= R or ypos < 0 or ypos >= C)
				continue;
			if (board[xpos][ypos] == 'X')
				continue;

			if (get<2>(cur) == 0) { // 고슴도치인 경우 물로 갈 수 없다.
				if (board[xpos][ypos] == '*' or visited[xpos][ypos])
					continue;

				// 해당 위치가 D가 아니면서 갈 수 없으면 스킵
				if (!canGo({ xpos,ypos }) and board[xpos][ypos] != 'D')
					continue;

				visited[xpos][ypos] = true;
				dis[xpos][ypos] = dis[get<0>(cur)][get<1>(cur)] + 1;
				q.push({ xpos,ypos,0 });
			} 
			else { // 물인 경우 비버의 굴로 갈 수 없다.
				if (board[xpos][ypos] == 'D' or board[xpos][ypos] == '*')
					continue;
				board[xpos][ypos] = '*';
				q.push({ xpos,ypos,1 });
			}
		}
	}

	if (answer == 0)
		cout << "KAKTUS";
	else
		cout << answer;


	return 0;
}