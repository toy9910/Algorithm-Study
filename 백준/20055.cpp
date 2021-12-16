#include <bits/stdc++.h>

using namespace std;

vector<pair<int, bool>> belt(202);
int N, K, kcount;

void moveBelt() {
    if (belt[N].second)
        belt[N].second = false;

    auto tmp = belt[2 * N];
    for (int i = 2 * N; i > 1; i--)
        belt[i] = belt[i - 1];
    belt[1] = tmp;
    belt[1].second = false;

    if (belt[N].second)
        belt[N].second = false;
}

void moveRobot() {
    for (int i = N; i > 1; i--) {
        if (!belt[i-1].second) // 해당 칸에 로봇이 있는지 확인
            continue;

        if (belt[i].second) // 이동하려는 칸에 로봇이 있는 경우
            continue;

        if (belt[i].first < 1) // 이동하려는 칸의 내구도가 0인 경우
            continue;

        belt[i].second = true;
        belt[i-1].second = false;
        belt[i].first--;
        if (belt[i].first == 0)
            kcount++;
    }
    if (belt[N].second)
        belt[N].second = false;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    for (int i = 1; i <= 2 * N; i++) {
        cin >> belt[i].first;
        belt[i].second = false;
    }

    kcount = 0;
    int answer = 0;
    while (kcount < K) {
        moveBelt();
        moveRobot();
        if (belt[1].first > 0) {
            belt[1].first--;
            belt[1].second = true;
            if (belt[1].first == 0)
                kcount++;
        }
        answer++;
    }

    cout << answer;

    return 0;
}