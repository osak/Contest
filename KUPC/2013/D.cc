#include <iostream>
#include <stack>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    stack<int> stk;
    stk.push(0);
    int ans = 0;
    while(N--) {
        int a;
        cin >> a;
        while(!stk.empty() && a < stk.top()) {
            stk.pop();
            ++ans;
        }
        if(stk.empty() || a != stk.top()) stk.push(a);
    }
    while(stk.top() > 0) {
        stk.pop();
        ++ans;
    }
    cout << ans << endl;

    return 0;
}

