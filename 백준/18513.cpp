#include <bits/stdc++.h>

using namespace std;

vector<int> water;	// 샘물 위치
vector<long long> distances;	// 가장 가까운 샘물로부터의 거리를 저장한 벡터 (순서 상관X)

// 해당 위치에 집을 지을 수 있는지 판별하는 벡터
// 집의 최소 위치는 100050000이고 최대 위치는 100050000이므로 크기를 200100005으로 했다.
vector<bool> ishouse(200100005, false);	
int N, K;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		water.push_back(num);
		num += 100050000;
		ishouse[num] = true;
	}

	queue<pair<int,int>> q;	// 첫 번째 원소는 위치, 두 번째 원소는 해당 위치에서 가장 가까운 샘물의 위치
	int house_count = 0;
	for (int i = 0; i < water.size(); i++) 
		q.push({ water[i], water[i] });
	
	while (house_count < K) {
		pair<int,int> cur_pos = q.front();
		q.pop();

		int left_pos = cur_pos.first - 1;
		int right_pos = cur_pos.first + 1;

		if (!ishouse[left_pos + 100050000]) {	// 왼쪽에 집을 지을 수 있는 경우
			ishouse[left_pos + 100050000] = true;
			house_count++;
			distances.push_back(abs(left_pos - cur_pos.second));
			q.push({ left_pos,cur_pos.second });
		}

		// 모든 집을 지었을 수 있으므로 확인
		if (house_count >= K)
			break;
		
		if (!ishouse[right_pos + 100050000]) {	// 오른쪽에 집을 지을 수 있는 경우
			ishouse[right_pos + 100050000] = true;
			house_count++;
			distances.push_back(abs(right_pos - cur_pos.second));
			q.push({ right_pos,cur_pos.second });
		}
	}

	long long answer = 0;
	for (auto dis : distances) {
		answer += dis;
	}

	cout << answer;

	return 0;
}