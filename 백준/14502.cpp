#include <bits/stdc++.h>

using namespace std;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

vector<vector<int>> lab(8, vector<int>(8));	// 연구소
int N, M, answer;

// 바이러스 갯수 체크
void checkVirus(vector<vector<int>> board) {
	vector<vector<bool>> visited(8, vector<bool>(8, false));	// 바이러스 방문 표시
	queue<pair<int, int>> vq;	// 바이러스의 위치를 저장하는 큐

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// 바이러스가 아닌 경우 스킵
			if (board[i][j] != 2)
				continue;

			// 바이러스인 경우 방문 표시 후 큐에 삽입
			visited[i][j] = true;
			vq.push({ i,j });

			// 바이러스 퍼뜨리는 작업
			while (!vq.empty()) {
				auto cur = vq.front();
				vq.pop();

				for (int k = 0; k < 4; k++) {
					int xpos = cur.first + dx[k];
					int ypos = cur.second + dy[k];

					if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= M)
						continue;
					if (visited[xpos][ypos] or board[xpos][ypos] == 1)
						continue;

					// 해당 위치에 바이러스 감염
					board[xpos][ypos] = 2;
					visited[xpos][ypos] = true;
					vq.push({ xpos, ypos });
				}
			}
		}
	}

	// 안전 영역의 크기
	int scount = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0)
				scount++;
		}
	}

	answer = max(scount, answer);
}

void func(int depth, int next) {
	// 세운 벽의 갯수가 3개인 경우 바이러스를 퍼뜨린 후 안전 영역을 계산한다.
	if (depth == 3) {
		checkVirus(lab);
		return;
	}

	// 중복을 허용하지 않는 조합을 사용
	for (int i = next / M; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (lab[i][j] == 2 or lab[i][j] == 1)
				continue;

			// 해당 위치에 벽을 세우고 재귀함수 호출
			lab[i][j] = 1;
			func(depth + 1, i * M + j+1);
			lab[i][j] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	answer = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int num;
			cin >> num;
			lab[i][j] = num;
		}
	}

	func(0, 0);

	cout << answer;

	return 0;
}