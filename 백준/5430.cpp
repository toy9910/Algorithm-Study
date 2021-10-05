#include <bits/stdc++.h>

using namespace std;
int T;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    while (T--) {
        // ��ɾ� �Է�
        string order;
        cin >> order;

        int n;
        cin >> n;

        // ���� �Է�
        string numbers;
        cin >> numbers;
        // ���ȣ ����
        numbers.erase(0, 1);
        numbers.erase(numbers.size() - 1, 1);

        deque<int> dq;

        // , �������� split �� dq�� ����
        istringstream ss(numbers);
        string str;
        while (getline(ss, str, ',')) {
            dq.push_back(stoi(str));
        }

        bool eflag = false; // error ���� Ȯ��
        int rcount = 0; // ¦���� ����, Ȧ���� ����

        for (auto c : order) {
            if (eflag)
                break;
            switch (c) {
            case 'R': {
                rcount++;
                break;
            }
            case 'D': {
                if (dq.empty()) {
                    eflag = true;
                    break;
                }

                if (rcount % 2 == 0) {  // ����
                    dq.pop_front();
                }
                else {  // ����
                    dq.pop_back();
                }
            }
            }
        }
        if (eflag)
            cout << "error\n";
        else {
            string answer = "[";
            if (rcount % 2 == 0) {  // ������ ��� ���ʴ�� ���
                for (auto it = dq.begin(); it != dq.end(); it++) {
                    answer += to_string(*it);
                    answer += ",";
                }
            }
            else {  // ������ ��� ������ �Ųٷ� �ؼ� ���
                for (auto it = dq.rbegin(); it != dq.rend(); it++) {
                    answer += to_string(*it);
                    answer += ",";
                }
            }
            
            // ������ , �����
            if (!dq.empty())
                answer.erase(answer.size() - 1, 1);
            answer += "]";
            cout << answer << '\n';
        }
    }


    return 0;
}