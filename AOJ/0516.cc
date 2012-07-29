//Name: Maximum Sum
//Level: 2
//Category: 尺取法,しゃくとり法,連続整数和の最大化
//Note:

#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int n, k;
        cin >> n >> k;
        if(!n && !k) break;

        int sum = 0;
        int ans = 0;
        queue<int> q;
        for(int i = 0; i < n; ++i) {
            int num;
            scanf("%d", &num);

            sum += num;
            if(i == k-1) ans = sum;
            if(i >= k) {
                sum -= q.front();
                q.pop();
                ans = max(ans, sum);
            }
            q.push(num);
        }

        cout << ans << endl;
    }
    return 0;
}

