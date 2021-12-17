#include <bits/stdc++.h>

using namespace std;

// 1 -> ��, 2 -> �Ʒ�, 3 -> ����, 4 -> ������
vector<vector<vector<int>>> sp(401, vector<vector<int>>(5, vector<int>(5))); // �� ����� ���� �켱����
vector<tuple<int, int, int>> shark(401); // ����� ��ġ, ����
vector<vector<pair<int, int>>> board(21, vector<pair<int, int>>(21)); // first -> ��� ��ȣ , second -> ������ ���� �ð�, third -> ��� ���� ����
int N, M, K, scount;

void decSmell() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // �ش� ��ġ�� ������ ���� ���
            if (board[i][j].first == 0)
                continue;

            board[i][j].second--;
            if (board[i][j].second == 0)
                board[i][j].first = 0;
        }
    }
}

void moveSharks() {
    vector<tuple<int, int, int>> movePos(401); // �ش� �� �������� �̵��� ��ġ�� ����

    for (int i = M; i >= 1; i--) {
        // �ش� �� �Ѱܳ� ���
        if (get<2>(shark[i]) == -1)
            continue;

        bool noWhere = true; // 4���� ���� �� �� ������ �ִ��� ����
        vector<tuple<int, int, int>> tmp; // �ڽŰ� ���� ��ȣ�� ������ ����
        for (int j = 1; j <= 4; j++) {
            switch (sp[i][get<2>(shark[i])][j]) {
            case 1: {// ��
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // ���� ��� ��ġ
                int xpos = cur.first - 1;
                int ypos = cur.second;

                if (xpos < 1 or xpos > N or ypos < 1 or ypos > N)
                    continue;
                if (board[xpos][ypos].first > 0) {
                    // �ڽŰ� ���� ��ȣ�� ��� ����
                    if (board[xpos][ypos].first == i)
                        tmp.push_back({ xpos,ypos,1 });
                    continue;
                }

                movePos[i] = { xpos,ypos,1 };
                noWhere = false;
                break;
            }
            case 2: { // �Ʒ�
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // ���� ��� ��ġ
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
            case 3: { // ����
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // ���� ��� ��ġ
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
            case 4: { // ������
                pair<int, int> cur = { get<0>(shark[i]), get<1>(shark[i]) }; // ���� ��� ��ġ
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
        // ���� 4���� ���� �� �� ������ ���� ���
        if (noWhere)
            movePos[i] = tmp[0];
    }

    decSmell();

    for (int i = M; i >= 1; i--) {
        // �̹� �Ѱܳ� ����� ���
        if (get<2>(shark[i]) < 0)
            continue;

        int xpos = get<0>(movePos[i]);
        int ypos = get<1>(movePos[i]);
        int dir = get<2>(movePos[i]);

        // ��� ��ġ ������Ʈ
        shark[i] = movePos[i];

        // �̵��Ϸ��� ��ġ�� �ڽź��� ���ڰ� ū �� �ִ� ���
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

    // ���� ����� ���� �Է�
    for (int i = 1; i <= M; i++) {
        cin >> get<2>(shark[i]);
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= 4; j++) {
            for (int k = 1; k <= 4; k++) {
                // i�� ����� j������ �켱���� �Է�
                cin >> sp[i][j][k];
            }
        }
    }

    int answer = 0;
    scount = M; // ����� ������
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