#include <bits/stdc++.h>

using namespace std;

int dx[] = { 0,0,-1,-1,-1,0,1,1,1 };
int dy[] = { 0,-1,-1,0,1,1,1,0,-1 };
int cx[] = { -1,-1,1,1 };
int cy[] = { -1,1,-1,1 };

vector<pair<int, int>> goorm; // 구름 위치
vector<vector<int>> waters(51, vector<int>(51)); // 각 바구니에 들어있는 물의 양
vector<vector<bool>> check(51, vector<bool>(51, false)); // 3번에서 사라진 구름인지 확인, true -> 3번에서 사라진 구름

int N, M;

void moveGoorm(int dir, int dist) {
	for (int i = 0; i < goorm.size(); i++) {
		for (int k = 0; k < dist; k++) {
			goorm[i].first += dx[dir];
			if (goorm[i].first > N)
				goorm[i].first = 1;
			else if (goorm[i].first < 1)
				goorm[i].first = N;

			goorm[i].second += dy[dir];
			if (goorm[i].second > N)
				goorm[i].second = 1;
			else if (goorm[i].second < 1)
				goorm[i].second = N;
		}
	}
}

void doRain() {
	// 바구니에 저장된 물의 양이 1 증가
	for (auto g : goorm) 
		waters[g.first][g.second]++;
	
	// 대각선 방향으로 거리가 1인 칸에 물이 있는 바구니의 수만큼 바구니의 물이 양이 증가
	for (auto g : goorm) {
		check[g.first][g.second] = true;

		int counts = 0;
		for (int k = 0; k < 4; k++) {
			int xpos = g.first + cx[k];
			int ypos = g.second + cy[k];

			if (xpos < 1 or xpos > N or ypos < 1 or ypos > N)
				continue;
			if (waters[xpos][ypos])
				counts++;
		}
		waters[g.first][g.second] += counts;
	}

	goorm.clear();
}

void makeGoorm() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			// 3번 진행사항에서 체크한 구름이면 값을 false로 초기화 후 스킵
			if (check[i][j]) {
				check[i][j] = false;
				continue;
			}
			if (waters[i][j] < 2)
				continue;
			goorm.push_back({ i,j });
			waters[i][j] -= 2;
		}
	}
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> waters[i][j];
		}
	}

	goorm.push_back({ N,1 });
	goorm.push_back({ N,2 });
	goorm.push_back({ N-1,1 });
	goorm.push_back({ N-1,2 });

	for (int i = 0; i < M; i++) {
		int dir, dist;
		cin >> dir >> dist;
		moveGoorm(dir, dist);
		doRain();
		makeGoorm();
	}

	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			answer += waters[i][j];
		}
	}

	cout << answer;

	return 0;
}