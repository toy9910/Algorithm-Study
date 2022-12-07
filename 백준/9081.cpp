#include <bits/stdc++.h>

using namespace std;

int t;

void input() {
    cin >> t;
}

void solve()
{
    while (t--)
    {
        string s;
        cin >> s;

        if (!next_permutation(s.begin(), s.end())) 
            prev_permutation(s.begin(), s.end());
        cout << s << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    input();
    solve();

    return 0;
}