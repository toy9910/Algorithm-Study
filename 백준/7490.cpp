#include <bits/stdc++.h>

using namespace std;

int T, N;
char operation[3] = { '+','-',' ' };
vector<char> oper;	// 원래 식 연산자
vector<int> num;	// 원래 식 숫자
vector<string> answers;	// 0이 되는 식들
string answer = "";

void func(int depth) {
	if (depth == N - 1) {
		deque<int> dn;	// 원래 식을 계산할 수 있도록 변환한 수
		deque<int> doper;	// 원래 식을 계산할 수 있도록 변환한 연산자
		for (int i = 0; i < oper.size(); i++) {
			switch (oper[i]) {
			case '-': {
				answer += to_string(num[i]);
				answer += "-";
				if (i == 0) {
					dn.push_back(num[i]);
				}
				else {
					// 앞 연산이 빈 칸이 아닌 경우
					if (oper[i - 1] != ' ') {
						dn.push_back(num[i]);
					}
				}
				doper.push_back(oper[i]);
				

				break;
			}
			case '+': {
				answer += to_string(num[i]);
				answer += "+";

				
				if (i == 0) {
					dn.push_back(num[i]);
				}
				else {
					// 앞 연산이 빈 칸이 아닌 경우
					if (oper[i - 1] != ' ') {
						dn.push_back(num[i]);
					}
				}
				doper.push_back(oper[i]);
				break;
			}
			default: {
				answer += to_string(num[i]);
				answer += " ";

				if (i > 0 and oper[i - 1] == ' ') {	// 앞 칸이 빈 칸인 경우
					int n = dn.back();
					dn.pop_back();
					dn.push_back(n * 10 + num[i + 1]);
				}
				else
					dn.push_back(num[i] * 10 + num[i + 1]);

			}
			}
		}
		if (oper.back() != ' ') {
			dn.push_back(num.back());
		}
		answer += to_string(num.back());

		// 계산하는 코드
		for (int i = 0; i < doper.size(); i++) {
			switch (doper[i]) {
			case '-': {
				int num1 = dn.front();
				dn.pop_front();
				int num2 = dn.front();
				dn.pop_front();
				dn.push_front(num1 - num2);
				break;
			}
			case '+': {
				int num1 = dn.front();
				dn.pop_front();
				int num2 = dn.front();
				dn.pop_front();
				dn.push_front(num1 + num2);
				break;
			}
			}
		}

		if (dn.front() == 0)
			answers.push_back(answer);
		answer = "";
		return;
	}

	for (int i = 0; i < 3; i++) {
		oper.push_back(operation[i]);
		func(depth + 1);
		oper.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> T;

	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			num.push_back(i);
		}
		func(0);
		
		// 아스키 순 정렬
		sort(answers.begin(), answers.end());
		for (auto s : answers)
			cout << s << '\n';
		cout << '\n';

		num.clear();
		answers.clear();
	}


	return 0;
}