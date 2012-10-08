//Name: Get a Rectangular Field
//Level: 2
//Category: 累積和,連続区間
//Note: 類題 POJ1964 AOJ0116

/*
 * AOJ0116 の解説参照．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    while(N--) {
        vector<int> acc(6, 0); // acc[5] is sentinel.
        int ans = 0;
        for(int r = 0; r < 5; ++r) {
            for(int c = 0; c < 5; ++c) {
                int v;
                cin >> v;
                if(v == 0) acc[c] = 0;
                else ++acc[c];
            }
            stack<pair<int,int> > stk;
            for(int i = 0; i <= 5; ++i) {
                int len = 0;
                while(!stk.empty() && stk.top().first >= acc[i]) {
                    len += stk.top().second;
                    ans = max(ans, len*stk.top().first);
                    stk.pop();
                }
                stk.push(make_pair(acc[i], len+1));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
