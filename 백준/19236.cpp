#include <bits/stdc++.h>

using namespace std;

int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };

vector<vector<pair<int, int>>> board(4, vector<pair<int, int>>(4, make_pair(0, 0)));	// 4x4 ����
vector<pair<int, int>> location(17, make_pair(0, 0));	// �������� ��ġ�� ������ ����
vector<bool> iseaten(17, false);	// �ش� ����Ⱑ �������� �Ǻ��ϴ� ����
int answer = 0;

void movefish(vector<vector<pair<int, int>>>& arr, vector<pair<int, int>>& locat, vector<bool> eaten, pair<int, int> shark) {
	for (int i = 1; i <= 16; i++) {
		// ���� ������ ������ �ʿ䰡 ����
		if (eaten[arr[locat[i].first][locat[i].second].first])
			continue;

		int xpos = locat[i].first + dx[arr[locat[i].first][locat[i].second].second];
		int ypos = locat[i].second + dy[arr[locat[i].first][locat[i].second].second];

		// ȭ��ǥ �������� �ű� �� �ִ��� üũ
		while (xpos < 0 or xpos > 3 or ypos < 0 or ypos > 3 or shark == make_pair(xpos, ypos)) {
			arr[locat[i].first][locat[i].second].second++;
			if (arr[locat[i].first][locat[i].second].second > 8)
				arr[locat[i].first][locat[i].second].second = 1;
			xpos = locat[i].first + dx[arr[locat[i].first][locat[i].second].second];
			ypos = locat[i].second + dy[arr[locat[i].first][locat[i].second].second];
		}

		// ����� ��ġ �ٲٱ�
		pair<int, int> tmp = arr[xpos][ypos];
		pair<int, int> tmp_pos = { xpos,ypos };
		pair<int, int> cur_fish = arr[locat[i].first][locat[i].second];
		pair<int, int> cur_pos = { locat[i].first,locat[i].second };

		arr[xpos][ypos] = cur_fish;	// �ű� ��ġ�� ���� ����� ��ġ
		arr[locat[i].first][locat[i].second] = tmp;	// ���� ����� ��ġ�� �ű� ����� ��ġ
													
		// ��ġ ������Ʈ
		locat[i] = { xpos,ypos };
		locat[tmp.first] = cur_pos;
	}
}


void moveShark(vector<pair<int, int>> v, vector<vector<pair<int, int>>> arr, vector<pair<int, int>> locat, vector<bool> eaten, pair<int, int> shark, int sum) {
	if (v.size() == 0) {
		answer = max(answer, sum);
		return;
	}
	// ����� ��ġ, 4x4 ����, ����� ��ġ�� �����س��´�.
	pair<int, int> tmp_shark = shark;
	vector<vector<pair<int, int>>> tmp_arr = arr;
	vector<pair<int, int>> tmp_locat = locat;

	for (int i = 0; i < v.size(); i++) {
		pair<int, int> fish = arr[v[i].first][v[i].second];	// ���� �����

		eaten[arr[v[i].first][v[i].second].first] = true;	// �ش� ������ �����ٰ� ǥ��
		shark = { v[i].first,v[i].second };	// ��� ��ġ ������Ʈ
		sum += fish.first;	// �̶����� ���� �������� �� ������Ʈ
		movefish(arr, locat, eaten, shark);	// ����� �̵�

		vector<pair<int, int>> vv;	// �� ���� �� �ִ� �������� �����ϴ� ����
		int xpos = shark.first + dx[arr[shark.first][shark.second].second];
		int ypos = shark.second + dy[arr[shark.first][shark.second].second];

		while (xpos >= 0 and xpos < 4 and ypos >= 0 and ypos < 4) {
			if (!eaten[arr[xpos][ypos].first])	// �ش� ����Ⱑ ������ �ʾҴٸ� ���Ϳ� �߰�
				vv.push_back({ xpos,ypos });
			xpos += dx[arr[shark.first][shark.second].second];
			ypos += dy[arr[shark.first][shark.second].second];
		}
		moveShark(vv, arr, locat, eaten, shark, sum);	// ��� �̵�
		// �� �̵��ϱ� ������ ������ �ʱ�ȭ
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