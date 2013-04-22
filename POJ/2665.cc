//Name: Trees
//Level: 1
//Category: 数学
//Note:

/*
 * ただの植木算．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int L, M;
    while(cin >> L >> M) {
        if(!L && !M) break;

        int removed = 0;
        TIMES(_, M) {
            int left, right;
            cin >> left >> right;
            removed += right - left + 1;
        }
        cout << L+1 - removed << endl;
    }
    return 0;
}
