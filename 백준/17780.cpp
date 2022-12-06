#include <bits/stdc++.h>

using namespace std;

int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

struct Horse {
	pair<int, int> pos;
	int num, dir;

	Horse(int _num, int _dir, pair<int,int> _pos) {
		this->num = _num;
		this->dir = _dir;
		this->pos = _pos;
	}
};

int N, K, board[15][15], answer;
vector<Horse> horses;
vector<int> hboard[15][15];

void input() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			cin >> board[i][j];
		
	
	for (int i = 0; i < K; i++) {
		int r, c, d;
		cin >> r >> c >> d;

		Horse horse = Horse(i, d, make_pair(r - 1,c - 1));
		hboard[r-1][c-1].push_back(i);
		horses.push_back(horse);
	}
}

int getPos(Horse horse) {
	if (horse.num == horses[hboard[horse.pos.first][horse.pos.second][0]].num)
		return 0;
	return -1;
}

bool isDone(pair<int, int> pos) {
	if (hboard[pos.first][pos.second].size() >= 4)
		return true;
	return false;
}

void redMove(int num, pair<int, int> next) {
	Horse horse = horses[num];
	pair<int, int> cur = horse.pos;
	vector<Horse> tmp;

	for (auto iter = hboard[cur.first][cur.second].rbegin(); iter != hboard[cur.first][cur.second].rend(); iter++) 
		tmp.push_back(horses[*iter]);

	for (auto h : tmp) {
		horses[h.num].pos = next;
		hboard[next.first][next.second].push_back(h.num);
	}

	if (isDone(next)) {
		cout << answer;
		exit(0);
	}

	hboard[cur.first][cur.second].clear();
}

void whiteMove(int num, pair<int, int> next) {
	Horse horse = horses[num];
	pair<int, int> cur = horse.pos;

	for (auto h : hboard[cur.first][cur.second]) {
		horses[h].pos = next;
		hboard[next.first][next.second].push_back(h);
	}
	if (isDone(next)) {
		cout << answer;
		exit(0);
	}

	hboard[cur.first][cur.second].clear();
}

void blueMove(int num, pair<int, int> next) {
	Horse horse = horses[num];
	pair<int, int> cur = horse.pos;

	if (horse.dir < 3) 
		horses[num].dir = 3 - horses[num].dir;
	else 
		horses[num].dir = 7 - horses[num].dir;

	next = make_pair(cur.first + dx[horses[num].dir], cur.second + dy[horses[num].dir]);

	if (next.first < 0 or next.first >= N or next.second < 0 or next.second >= N or board[next.first][next.second] == 2)
		return;

	if (board[next.first][next.second] == 0)
		whiteMove(num, next);
	else if(board[next.first][next.second] == 1)
		redMove(num, next);
}


void move(int num) {
	Horse horse = horses[num];
	int xpos = horse.pos.first + dx[horse.dir], ypos = horse.pos.second + dy[horse.dir];

	if (xpos < 0 or xpos >= N or ypos < 0 or ypos >= N) {
		blueMove(num, make_pair(xpos, ypos));
	}
	else {
		switch (board[xpos][ypos]) {
		case 0: 
			whiteMove(num, make_pair(xpos, ypos));
			break;
		case 1:
			redMove(num, make_pair(xpos, ypos));
			break;
		case 2:
			blueMove(num, make_pair(xpos, ypos));
			break;
		}
	}
}


void solve() {
	while (true) {
		answer++;
		if (answer > 1000) break;
		for (int i = 0; i < horses.size(); i++) {
			if (getPos(horses[i]) == 0) {
				move(i);
			}
		}
	}
	cout << -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}