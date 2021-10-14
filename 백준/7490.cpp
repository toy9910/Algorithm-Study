#include <bits/stdc++.h>

using namespace std;

int T, N;
char operation[3] = { '+','-',' ' };
vector<char> oper;	// ���� �� ������
vector<int> num;	// ���� �� ����
vector<string> answers;	// 0�� �Ǵ� �ĵ�
string answer = "";

void func(int depth) {
	if (depth == N - 1) {
		deque<int> dn;	// ���� ���� ����� �� �ֵ��� ��ȯ�� ��
		deque<int> doper;	// ���� ���� ����� �� �ֵ��� ��ȯ�� ������
		for (int i = 0; i < oper.size(); i++) {
			switch (oper[i]) {
			case '-': {
				answer += to_string(num[i]);
				answer += "-";
				if (i == 0) {
					dn.push_back(num[i]);
				}
				else {
					// �� ������ �� ĭ�� �ƴ� ���
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
					// �� ������ �� ĭ�� �ƴ� ���
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

				if (i > 0 and oper[i - 1] == ' ') {	// �� ĭ�� �� ĭ�� ���
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

		// ����ϴ� �ڵ�
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
		
		// �ƽ�Ű �� ����
		sort(answers.begin(), answers.end());
		for (auto s : answers)
			cout << s << '\n';
		cout << '\n';

		num.clear();
		answers.clear();
	}


	return 0;
}