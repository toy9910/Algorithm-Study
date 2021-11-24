#include <bits/stdc++.h>

using namespace std;


struct node {
    node* parent; // �θ� ���
    vector<node> *childs = new vector<node>(); // �ڽ� ����
    int num; // �ش� ����� ��ȣ
};

int N;

// ���� ����� ������ ���ϴ� �Լ�
int leafCount(node& node) {
    int counts = 0;

    // �ش� ��尡 ���� ����� ���
    if (node.childs->empty())
        return 1;

    // �ش� ����� �ڽ� ��尡 ������ ���
    for (auto n : *node.childs) {
        counts += leafCount(n);
    }
    return counts;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<node> v(51); // ��� ���� �迭

    int root; // ��Ʈ ����� ��ȣ
    cin >> N;

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        if (num == -1) { // ��Ʈ ����� ���
            root = i;
            v[root].num = root;
            v[root].parent = NULL;
        }
        else { // ��Ʈ ��尡 �ƴ� ���
            v[i].parent = &v[num];
            v[i].num = i;
            v[num].num = num;
            v[num].childs->push_back(v[i]);
        }
    }

    int num;
    cin >> num;
    
    // ������� �ϴ� ��尡 ��Ʈ ����� ���
    if (num == root) {
        cout << 0;
        return 0;
    }

    // ������� �ϴ� ��尡 �θ� ����� ���° �ڽ� ������� ���Ѵ�.
    int index;
    vector<node> vv = *v[num].parent->childs;
    for (int i = 0; i < vv.size(); i++) {
        if (vv[i].num == num) {
            index = i;
            break;
        }
    }

    // �ش� ��带 �θ� ����� childs �迭���� �����.
    auto it = v[num].parent->childs->begin();
    v[num].parent->childs->erase(next(it, index));

    cout << leafCount(v[root]);


    return 0;
}