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

		vector<string> numbers; // ��ȭ��ȣ ���
		for (int i = 0; i < n; i++) {
			string num;
			cin >> num;
			numbers.push_back(num);
		}

		// ���̼����� ����
		sort(numbers.begin(), numbers.end(), cmp);

		unordered_map<string, bool> m; // ��ȭ��ȣ ���� ����
		vector<int> lengths; // ��ȭ��ȣ ���� ���
		vector<bool> isexist(11, false); // ��ȭ��ȣ ���� ���� ����
		bool flag = true; // �ϰ��� ����

		for (string str : numbers) {
			// ù ��ȭ��ȣ�� ���
			if (lengths.empty()) {
				m[str] = true;// ��ȭ��ȣ ���
				lengths.push_back(str.length()); // ��ȭ��ȣ ���� ��Ͽ� �ش� ��ȭ��ȣ ���� �߰�
				isexist[str.length()] = true; // �ش� ��ȭ��ȣ ���� ���� ���� üũ
			}
			else { // 2��° ��ȭ��ȣ ����
				for (auto num : lengths) {
					// ��ȭ��ȣ ���� ��Ͽ� �����ϴ� ���� ����
					// �ش� ���̸�ŭ ��ȭ��ȣ�� �߶�
					// �ڸ� ��ȭ��ȣ�� �����ϴ��� Ȯ��
					if (m[str.substr(0, num)]) {
						cout << "NO\n";
						flag = false;
						break;
					}
				}
				// �ش� ��ȭ��ȣ�� ���̰� �������� �ʴ� ���
				if (!isexist[str.length()]) {
					isexist[str.length()] = true;
					lengths.push_back(str.length());
				}
				// ��ȭ��ȣ ���
				m[str] = true;
			}
			// �ϰ����� ���� ���
			// �ڿ� ��ȭ��ȣ�� �� �ʿ䰡 �����Ƿ� break
			if (!flag)
				break;
		}
		// �ϰ����� ������ YES ���
		if (flag)
			cout << "YES\n";
	}

	return 0;
}