#include <bits/stdc++.h>

using namespace std;

vector<int> water;	// ���� ��ġ
vector<long long> distances;	// ���� ����� �����κ����� �Ÿ��� ������ ���� (���� ���X)

// �ش� ��ġ�� ���� ���� �� �ִ��� �Ǻ��ϴ� ����
// ���� �ּ� ��ġ�� 100050000�̰� �ִ� ��ġ�� 100050000�̹Ƿ� ũ�⸦ 200100005���� �ߴ�.
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

	queue<pair<int,int>> q;	// ù ��° ���Ҵ� ��ġ, �� ��° ���Ҵ� �ش� ��ġ���� ���� ����� ������ ��ġ
	int house_count = 0;
	for (int i = 0; i < water.size(); i++) 
		q.push({ water[i], water[i] });
	
	while (house_count < K) {
		pair<int,int> cur_pos = q.front();
		q.pop();

		int left_pos = cur_pos.first - 1;
		int right_pos = cur_pos.first + 1;

		if (!ishouse[left_pos + 100050000]) {	// ���ʿ� ���� ���� �� �ִ� ���
			ishouse[left_pos + 100050000] = true;
			house_count++;
			distances.push_back(abs(left_pos - cur_pos.second));
			q.push({ left_pos,cur_pos.second });
		}

		// ��� ���� ������ �� �����Ƿ� Ȯ��
		if (house_count >= K)
			break;
		
		if (!ishouse[right_pos + 100050000]) {	// �����ʿ� ���� ���� �� �ִ� ���
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