#include <iostream>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = (1<<24) + 1;
int memo[MAXN];
bool visited[MAXN];

int main() {
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        fill(memo, memo+MAXN, 0);
        fill(visited, visited+MAXN, false);
        int A, B, C, N;
        cin >> A >> B >> C >> N;

        int ans = 1;
        stack<int> history;
        for(int start = 0; start < N; ++start) {
            int cur = start;
            while(!visited[cur]) {
                history.push(cur);
                visited[cur] = true;
                long long v = cur;
                long long next = (v*v % N) * A % N;
                next = (next + v*B) % N;
                next = (next + C) % N;
                //cout << cur << ' ' << next << endl;
                cur = (int)next;
            }
            if(memo[cur] == 0) {
                // visited[cur] && memo[cur] == 0 then must be in loop
                int loop_start = cur;
                stack<int> stk;
                while(history.top() != loop_start) {
                    stk.push(history.top());
                    history.pop();
                }
                stk.push(history.top());
                history.pop();

                int size = stk.size();
                ans = max(ans, size);
                while(!stk.empty()) {
                    memo[stk.top()] = size;
                    stk.pop();
                }
            }
            int val = memo[cur];
            while(!history.empty()) {
                memo[history.top()] = ++val;
                ans = max(ans, val);
                history.pop();
            }
        }
        cout << ans << endl;
    }

    return 0;
}
