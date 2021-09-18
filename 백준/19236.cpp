#include <bits/stdc++.h>

using namespace std;

int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };

vector<vector<pair<int, int>>> board(4, vector<pair<int, int>>(4, make_pair(0, 0)));	// 4x4 공간
vector<pair<int, int>> location(17, make_pair(0, 0));	// 물고기들의 위치를 저장한 벡터
vector<bool> iseaten(17, false);	// 해당 물고기가 먹혔는지 판별하는 벡터
int answer = 0;

void movefish(vector<vector<pair<int, int>>>& arr, vector<pair<int, int>>& locat, vector<bool> eaten, pair<int, int> shark) {
	for (int i = 1; i <= 16; i++) {
		// 먹힌 물고기는 움직일 필요가 없다
		if (eaten[arr[locat[i].first][locat[i].second].first])
			continue;

		int xpos = locat[i].first + dx[arr[locat[i].first][locat[i].second].second];
		int ypos = locat[i].second + dy[arr[locat[i].first][locat[i].second].second];

		// 화살표 방향으로 옮길 수 있는지 체크
		while (xpos < 0 or xpos > 3 or ypos < 0 or ypos > 3 or shark == make_pair(xpos, ypos)) {
			arr[locat[i].first][locat[i].second].second++;
			if (arr[locat[i].first][locat[i].second].second > 8)
				arr[locat[i].first][locat[i].second].second = 1;
			xpos = locat[i].first + dx[arr[locat[i].first][locat[i].second].second];
			ypos = locat[i].second + dy[arr[locat[i].first][locat[i].second].second];
		}

		// 물고기 위치 바꾸기
		pair<int, int> tmp = arr[xpos][ypos];
		pair<int, int> tmp_pos = { xpos,ypos };
		pair<int, int> cur_fish = arr[locat[i].first][locat[i].second];
		pair<int, int> cur_pos = { locat[i].first,locat[i].second };

		arr[xpos][ypos] = cur_fish;	// 옮길 위치에 현재 물고기 배치
		arr[locat[i].first][locat[i].second] = tmp;	// 현재 물고기 위치에 옮길 물고기 배치
													
		// 위치 업데이트
		locat[i] = { xpos,ypos };
		locat[tmp.first] = cur_pos;
	}
}


void moveShark(vector<pair<int, int>> v, vector<vector<pair<int, int>>> arr, vector<pair<int, int>> locat, vector<bool> eaten, pair<int, int> shark, int sum) {
	if (v.size() == 0) {
		answer = max(answer, sum);
		return;
	}
	// 상어의 위치, 4x4 공간, 물고기 위치를 복사해놓는다.
	pair<int, int> tmp_shark = shark;
	vector<vector<pair<int, int>>> tmp_arr = arr;
	vector<pair<int, int>> tmp_locat = locat;

	for (int i = 0; i < v.size(); i++) {
		pair<int, int> fish = arr[v[i].first][v[i].second];	// 먹힐 물고기

		eaten[arr[v[i].first][v[i].second].first] = true;	// 해당 물고기는 먹혔다고 표시
		shark = { v[i].first,v[i].second };	// 상어 위치 업데이트
		sum += fish.first;	// 이때까지 먹은 물고기들의 합 업데이트
		movefish(arr, locat, eaten, shark);	// 물고기 이동

		vector<pair<int, int>> vv;	// 상어가 먹을 수 있는 물고기들을 저장하는 벡터
		int xpos = shark.first + dx[arr[shark.first][shark.second].second];
		int ypos = shark.second + dy[arr[shark.first][shark.second].second];

		while (xpos >= 0 and xpos < 4 and ypos >= 0 and ypos < 4) {
			if (!eaten[arr[xpos][ypos].first])	// 해당 물고기가 먹히지 않았다면 벡터에 추가
				vv.push_back({ xpos,ypos });
			xpos += dx[arr[shark.first][shark.second].second];
			ypos += dy[arr[shark.first][shark.second].second];
		}
		moveShark(vv, arr, locat, eaten, shark, sum);	// 상어 이동
		// 상어가 이동하기 전으로 값들을 초기화
		arr = tmp_arr;
		locat = tmp_locat;
		sum -= fish.first;
		shark = tmp_shark;
		eaten[arr[v[i].first][v[i].second].first] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> board[i][j].first >> board[i][j].second;
			location[board[i][j].first] = { i,j };
		}
	}

	vector<pair<int, int>> v;
	v.push_back({ 0,0 });
	moveShark(v, board, location, iseaten, { 0,0 }, 0);

	cout << answer;

	return 0;
}