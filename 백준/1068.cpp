#include <bits/stdc++.h>

using namespace std;


struct node {
    node* parent; // 부모 노드
    vector<node> *childs = new vector<node>(); // 자식 노드들
    int num; // 해당 노드의 번호
};

int N;

// 리프 노드의 개수를 구하는 함수
int leafCount(node& node) {
    int counts = 0;

    // 해당 노드가 리프 노드인 경우
    if (node.childs->empty())
        return 1;

    // 해당 노드의 자식 노드가 존재할 경우
    for (auto n : *node.childs) {
        counts += leafCount(n);
    }
    return counts;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<node> v(51); // 노드 저장 배열

    int root; // 루트 노드의 번호
    cin >> N;

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        if (num == -1) { // 루트 노드인 경우
            root = i;
            v[root].num = root;
            v[root].parent = NULL;
        }
        else { // 루트 노드가 아닌 경우
            v[i].parent = &v[num];
            v[i].num = i;
            v[num].num = num;
            v[num].childs->push_back(v[i]);
        }
    }

    int num;
    cin >> num;
    
    // 지우고자 하는 노드가 루트 노드인 경우
    if (num == root) {
        cout << 0;
        return 0;
    }

    // 지우고자 하는 노드가 부모 노드의 몇번째 자식 노드인지 구한다.
    int index;
    vector<node> vv = *v[num].parent->childs;
    for (int i = 0; i < vv.size(); i++) {
        if (vv[i].num == num) {
            index = i;
            break;
        }
    }

    // 해당 노드를 부모 노드의 childs 배열에서 지운다.
    auto it = v[num].parent->childs->begin();
    v[num].parent->childs->erase(next(it, index));

    cout << leafCount(v[root]);


    return 0;
}