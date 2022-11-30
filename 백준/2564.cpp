#include <bits/stdc++.h>

using namespace std;

int N, M, R;
pair<int, int> cur;
vector<pair<int, int>> stores;

void input() {
	cin >> M >> N >> R;
	int dir, dist;

	for (int i = 0; i < R; i++) {
		cin >> dir >> dist;
		stores.push_back({ dir, dist });
	}
	cin >> dir >> dist;
	cur = { dir, dist };
}

int calc(pair<int, int> p) {
	if (cur.first == p.first) 
		return abs(cur.second - p.second);
	
	switch (cur.first) {
	case 1: {
		if (p.first == 2) {
			return min(p.second + cur.second, (M - p.second) + (M - cur.second)) + N;
		}
		else if(p.first == 3) {
			return p.second + cur.second;
		}
		else {
			return M - cur.second + p.second;
		}
		break;
	}
	case 2: {
		if (p.first == 1) {
			int d = min(p.second + cur.second, (M - p.second) + (M - cur.second));
			return min(p.second + cur.second, (M - p.second) + (M - cur.second)) + N;
		}
		else if (p.first == 3) {
			return cur.second + N - p.second;
		}
		else {
			return M - cur.second + N - p.second;
		}
		break;
	}
	case 3: {
		if (p.first == 4) {
			return M + min(p.second + cur.second, (N - p.second) + (N - cur.second));
		}
		else if(p.first == 2) {
			return M - cur.second + p.second;
		}
		else {
			return cur.second + p.second;
		}
		break;
	}
	default: {
		if (p.first == 3) {
			return M + min(p.second + cur.second, (N - p.second) + (N - cur.second));
		}
		else if (p.first == 2) {
			return M - p.second + N - cur.second;
		}
		else {
			return cur.second + M - p.second;
		}
	}
	}
}

void solve() {
	int dist = 0;
	for (auto store : stores) {
		dist += calc(store);
	}
	cout << dist;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	solve();

	return 0;
}