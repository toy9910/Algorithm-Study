#include <bits/stdc++.h>

using namespace std;


vector<tuple<int, int, int, int>> v; // 시작점, 방향, 세대
int visited[101][101]; // 해당 지점이 드래곤 커브인지
int N, x, y, d, g;

// 입력
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		v.push_back({ y,x,d,g });
	}
}

// 시계 방향으로 회전 시 바뀌게 되는 방향
int changeDir(int num) {
	switch (num) {
	case 0:
		return 1;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 0;
	}
}

// 시계 방향으로 회전
void doCurve(tuple<int, int, int, int> t) {
	// 저장된 방향 정보
	vector<int> dirs;
	dirs.push_back(get<2>(t));

	// 세대 수 만큼 회전
	for (int i = 0; i < get<3>(t); i++) {
		// 각 방향들에 대해 회전한 방향값을 추가로 넣는다.
		queue<int> tdir;
		for (auto it = dirs.rbegin(); it != dirs.rend(); it++) 
			tdir.push(changeDir(*it));

		while (!tdir.empty()) {
			int d = tdir.front();
			tdir.pop();

			dirs.push_back(d);
		}
	}

	// 시작점부터 방향을 읽고 드래곤 커브를 그린다.
	int xpos = get<0>(t);
	int ypos = get<1>(t);
	visited[xpos][ypos] = true;

	for (int dir : dirs) {
		switch (dir) {
		case 0: 
			ypos++;
			break;
		case 1:
			xpos--;
			break;
		case 2:
			ypos--;
			break;
		case 3:
			xpos++;
			break;
		}
		visited[xpos][ypos] = true;
	}
}

// 정사각형의 갯수를 센다.
int getCount() {
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			bool isRect = false;
			if (visited[i][j] and visited[i + 1][j] and visited[i][j + 1] and visited[i + 1][j + 1]) isRect = true;
			if (isRect) cnt++;
		}
	}
	return cnt;
}

void solve() {
	for (auto t : v)
		doCurve(t);
	cout << getCount();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}