#include <bits/stdc++.h>

using namespace std;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1,0, 1 };

struct Robot {
	int xpos, ypos;
	char dir;

	Robot(int _xpos, int _ypos, char _dir) {
		this->xpos = _xpos;
		this->ypos = _ypos;
		this->dir = _dir;
	}
};

int board[105][105], A, B, N, M;
vector<Robot> robots;
vector<tuple<int, char, int>> commands;

void input() {
	cin >> A >> B >> N >> M;
	robots.push_back(Robot(0, 0, 'R'));

	for (int i = 0; i < N; i++) {
		int x, y;
		char d;
		cin >> x >> y >> d;
		robots.push_back(Robot(y, x, d));
		board[y][x] = i + 1;
	}
	for (int i = 0; i < M; i++) {
		int num, repeat;
		char d;
		cin >> num >> d >> repeat;
		commands.push_back(make_tuple(num, d, repeat));
	}
}

char rotateLeft(char dir) {
	if (dir == 'N')
		return 'W';
	else if (dir == 'W')
		return 'S';
	else if (dir == 'S')
		return 'E';
	else
		return 'N';
}

char rotateRight(char dir) {
	if (dir == 'N')
		return 'E';
	else if (dir == 'E')
		return 'S';
	else if (dir == 'S')
		return 'W';
	else
		return 'N';
}

int moveRobot(tuple<int, char, int> command) {
	int num, repeat, k;
	char dir;
	tie(num, dir, repeat) = command;


	switch (robots[num].dir) {
	case 'N': {
		k = 0;
		break;
	}
	case 'W': {
		k = 1;
		break;
	}
	case 'S': {
		k = 2;
		break;
	}
	default: {
		k = 3;
		break;
	}
	}

	switch (dir) {
	case 'F': {
		for (int i = 0; i < repeat; i++) {
			int xpos = robots[num].xpos + dx[k], ypos = robots[num].ypos + dy[k];
			if (xpos < 1 or xpos > B or ypos < 1 or ypos > A) {
				cout << "Robot " << num << " crashes into the wall\n";
				return 0;
			}
			if (board[xpos][ypos] > 0) {
				cout << "Robot " << num << " crashes into robot " << board[xpos][ypos] << '\n';
				return 0;
			}

			board[robots[num].xpos][robots[num].ypos] = 0;
			robots[num].xpos = xpos; robots[num].ypos = ypos;
			board[xpos][ypos] = num;
		}
		break;
	}
	case 'L': {
		repeat %= 4;
		for (int i = 0; i < repeat; i++) 
			robots[num].dir = rotateLeft(robots[num].dir);
		break;
	}
	case 'R': {
		repeat %= 4;
		for (int i = 0; i < repeat; i++)
			robots[num].dir = rotateRight(robots[num].dir);
		break;
	}
	}

	return 1;
}

void solve() {
	for (auto command : commands) {
		if (moveRobot(command) < 1)
			exit(0);
	}
	cout << "OK\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}