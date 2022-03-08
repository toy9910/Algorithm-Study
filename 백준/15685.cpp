#include <bits/stdc++.h>

using namespace std;


vector<tuple<int, int, int, int>> v; // ������, ����, ����
int visited[101][101]; // �ش� ������ �巡�� Ŀ������
int N, x, y, d, g;

// �Է�
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		v.push_back({ y,x,d,g });
	}
}

// �ð� �������� ȸ�� �� �ٲ�� �Ǵ� ����
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

// �ð� �������� ȸ��
void doCurve(tuple<int, int, int, int> t) {
	// ����� ���� ����
	vector<int> dirs;
	dirs.push_back(get<2>(t));

	// ���� �� ��ŭ ȸ��
	for (int i = 0; i < get<3>(t); i++) {
		// �� ����鿡 ���� ȸ���� ���Ⱚ�� �߰��� �ִ´�.
		queue<int> tdir;
		for (auto it = dirs.rbegin(); it != dirs.rend(); it++) 
			tdir.push(changeDir(*it));

		while (!tdir.empty()) {
			int d = tdir.front();
			tdir.pop();

			dirs.push_back(d);
		}
	}

	// ���������� ������ �а� �巡�� Ŀ�긦 �׸���.
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

// ���簢���� ������ ����.
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