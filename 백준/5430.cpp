#include <bits/stdc++.h>

using namespace std;
int T;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    while (T--) {
        // 명령어 입력
        string order;
        cin >> order;

        int n;
        cin >> n;

        // 숫자 입력
        string numbers;
        cin >> numbers;
        // 대괄호 제거
        numbers.erase(0, 1);
        numbers.erase(numbers.size() - 1, 1);

        deque<int> dq;

        // , 기준으로 split 후 dq에 삽입
        istringstream ss(numbers);
        string str;
        while (getline(ss, str, ',')) {
            dq.push_back(stoi(str));
        }

        bool eflag = false; // error 여부 확인
        int rcount = 0; // 짝수면 정순, 홀수면 역순

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

                if (rcount % 2 == 0) {  // 정순
                    dq.pop_front();
                }
                else {  // 역순
                    dq.pop_back();
                }
            }
            }
        }
        if (eflag)
            cout << "error\n";
        else {
            string answer = "[";
            if (rcount % 2 == 0) {  // 정순일 경우 차례대로 출력
                for (auto it = dq.begin(); it != dq.end(); it++) {
                    answer += to_string(*it);
                    answer += ",";
                }
            }
            else {  // 역순일 경우 순서를 거꾸로 해서 출력
                for (auto it = dq.rbegin(); it != dq.rend(); it++) {
                    answer += to_string(*it);
                    answer += ",";
                }
            }
            
            // 마지막 , 지우기
            if (!dq.empty())
                answer.erase(answer.size() - 1, 1);
            answer += "]";
            cout << answer << '\n';
        }
    }


    return 0;
}