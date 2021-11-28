#include <bits/stdc++.h>

using namespace std;

int t;

bool cmp(string s1, string s2) {
	return s1.length() < s2.length();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		vector<string> numbers; // 전화번호 목록
		for (int i = 0; i < n; i++) {
			string num;
			cin >> num;
			numbers.push_back(num);
		}

		// 길이순으로 저장
		sort(numbers.begin(), numbers.end(), cmp);

		unordered_map<string, bool> m; // 전화번호 존재 여부
		vector<int> lengths; // 전화번호 길이 목록
		vector<bool> isexist(11, false); // 전화번호 길이 존재 여부
		bool flag = true; // 일관성 여부

		for (string str : numbers) {
			// 첫 전화번호의 경우
			if (lengths.empty()) {
				m[str] = true;// 전화번호 등록
				lengths.push_back(str.length()); // 전화번호 길이 목록에 해당 전화번호 길이 추가
				isexist[str.length()] = true; // 해당 전화번호 길이 존재 여부 체크
			}
			else { // 2번째 전화번호 이후
				for (auto num : lengths) {
					// 전화번호 길이 목록에 존재하는 길이 별로
					// 해당 길이만큼 전화번호를 잘라서
					// 자른 전화번호가 존재하는지 확인
					if (m[str.substr(0, num)]) {
						cout << "NO\n";
						flag = false;
						break;
					}
				}
				// 해당 전화번호의 길이가 존재하지 않는 경우
				if (!isexist[str.length()]) {
					isexist[str.length()] = true;
					lengths.push_back(str.length());
				}
				// 전화번호 등록
				m[str] = true;
			}
			// 일관성이 없는 경우
			// 뒤에 전화번호는 볼 필요가 없으므로 break
			if (!flag)
				break;
		}
		// 일관성이 있으면 YES 출력
		if (flag)
			cout << "YES\n";
	}

	return 0;
}