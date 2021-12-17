#include <bits/stdc++.h>

using namespace std;

// 1 -> 위, 2 -> 아래, 3 -> 왼쪽, 4 -> 오른쪽
vector<vector<vector<int>>> sp(401, vector<vector<int>>(5, vector<int>(5))); // 각 상어의 방향 우선순위
vector<tuple<int, int, int>> shark(401); // 상어의 위치, 방향
vector<vector<pair<int, int>>> board(21, vector<pair<int, int>>(21)); // first -> 상어 번호 , second -> 냄새의 남은 시간, third -> 상어 존재 여부
int N, M, K, scount;

void decSmell() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // 해당 위치에 냄새가 없을 경우
            if (board[i][j].first == 0)
                continue;

            board[i][j].second--;
            if (board[i][j].second == 0)
                board[i][j].first = 0;
        }
    }
}

void moveSharks() {
    vector<tuple<int, int, int>> movePos(401); // 해당 상어가 다음으로 이동할 위치를 저장

    for (int i = M; i >= 1; i--) {
        // 해당 상어가 쫓겨난 경우
        if (get<2>(shark[i]) == -1)
            continue;

        bool noWhere = true; // 4가지 방향 중 빈 공간이 있는지 여부
        vector<tuple<int, int, int>> tmp; // 자신과 같은 번호의 냄새를 저장
        for (int j = 1; j <= 4; j++) {
            switch (sp[i][get<2>(shark[i])][j]) {
            case 1: {// 위
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // 현재 상어 위치
                int xpos = cur.first - 1;
                int ypos = cur.second;

                if (xpos < 1 or xpos > N or ypos < 1 or ypos > N)
                    continue;
                if (board[xpos][ypos].first > 0) {
                    // 자신과 같은 번호일 경우 저장
                    if (board[xpos][ypos].first == i)
                        tmp.push_back({ xpos,ypos,1 });
                    continue;
                }

                movePos[i] = { xpos,ypos,1 };
                noWhere = false;
                break;
            }
            case 2: { // 아래
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // 현재 상어 위치
                int xpos = cur.first + 1;
                int ypos = cur.second;

                if (xpos < 1 or xpos > N or ypos < 1 or ypos > N)
                    continue;
                if (board[xpos][ypos].first > 0) {
                    if (board[xpos][ypos].first == i)
                        tmp.push_back({ xpos,ypos,2 });
                    continue;
                }

                movePos[i] = { xpos,ypos,2 };
                noWhere = false;
                break;
            }
            case 3: { // 왼쪽
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // 현재 상어 위치
                int xpos = cur.first;
                int ypos = cur.second - 1;

                if (xpos < 1 or xpos > N or ypos < 1 or ypos > N)
                    continue;
                if (board[xpos][ypos].first > 0) {
                    if (board[xpos][ypos].first == i)
                        tmp.push_back({ xpos,ypos,3 });
                    continue;
                }

                movePos[i] = { xpos,ypos,3 };
                noWhere = false;
                break;
            }
            case 4: { // 오른쪽
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // 현재 상어 위치
                int xpos = cur.first;
                int ypos = cur.second + 1;

                if (xpos < 1 or xpos > N or ypos < 1 or ypos > N)
                    continue;
                if (board[xpos][ypos].first > 0) {
                    if (board[xpos][ypos].first == i)
                        tmp.push_back({ xpos,ypos,4 });
                    continue;
                }

                movePos[i] = { xpos,ypos,4 };
                noWhere = false;
                break;
            }
            }
            if (!noWhere)
                break;
        }
        // 만약 4가지 방향 중 빈 공간이 없는 경우
        if (noWhere)
            movePos[i] = tmp[0];
    }

    decSmell();

    for (int i = M; i >= 1; i--) {
        // 이미 쫓겨난 상어인 경우
        if (get<2>(shark[i]) < 0)
            continue;

        int xpos = get<0>(movePos[i]);
        int ypos = get<1>(movePos[i]);
        int dir = get<2>(movePos[i]);

        // 상어 위치 업데이트
        shark[i] = movePos[i];

        // 이동하려는 위치에 자신보다 숫자가 큰 상어가 있는 경우
        if (board[xpos][ypos].first > i) {
            get<2>(shark[board[xpos][ypos].first]) = -1;
            scount--;
        }

        board[xpos][ypos].first = i;
        board[xpos][ypos].second = K;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> board[i][j].first;
            if (board[i][j].first > 0) {
                board[i][j].second = K;
                shark[board[i][j].first] = make_tuple(i, j, 0);
            }
            else
                board[i][j].second = 0;
        }
    }

    // 현재 상어의 방향 입력
    for (int i = 1; i <= M; i++) {
        cin >> get<2>(shark[i]);
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= 4; j++) {
            for (int k = 1; k <= 4; k++) {
                // i번 상어의 j방향의 우선순위 입력
                cin >> sp[i][j][k];
            }
        }
    }

    int answer = 0;
    scount = M; // 상어의 마릿수
    while (scount > 1 and answer <= 1000) {
        answer++;
        moveSharks();
    }

    if (answer > 1000)
        cout << -1;
    else
        cout << answer;


    return 0;
}