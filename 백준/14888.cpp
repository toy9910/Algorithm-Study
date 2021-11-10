#include <bits/stdc++.h>

using namespace std;

vector<int> numbers;	// 입력 받은 숫자 저장 배열
vector<int> tmp(101);	// 연산자 저장 배열
vector<int> oper_count;	// 연산자 갯수 [0] : + 갯수 , [1] : - 갯수 , [2] : * 갯수 , [3] : / 갯수
vector<int> answer;	// 계산값 저장 배열
int N;

void func(int depth) {
	// tmp 벡터에 저장된 연산자 갯수가 N-1일 때
	if (depth == N - 1) {
		int sum = numbers[0];
		for (int i = 0; i < N - 1; i++) {
			switch (tmp[i]) {
			case 0: {
				sum += numbers[i + 1];
				break;
			}
			case 1: {
				sum -= numbers[i + 1];
				break;
			}
			case 2: {
				sum *= numbers[i + 1];
				break;
			}
			default: {
				sum /= numbers[i + 1];
			}
			}
		}
		answer.push_back(sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		// 해당 연산자의 갯수가 남아있을 경우
		if (oper_count[i] > 0) {
			tmp[depth] = i;
			oper_count[i]--;
			func(depth + 1);
			oper_count[i]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		numbers.push_back(num);
	}

	for (int i = 0; i < 4; i++) {
		int num;
		cin >> num;
		oper_count.push_back(num);
	}
	
	func(0);

	sort(answer.begin(), answer.end());
	cout << *prev(answer.end()) << '\n';
	cout << *answer.begin();

	return 0;
}