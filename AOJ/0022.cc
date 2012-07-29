#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        queue<int> q;
        int ans = -100000;
        int sump = 0, sumn = 0;
        while(N--) {
            int n;
            cin >> n;
            q.push(n);
            if(n >= 0) sump += n;
            else sumn += -n;
            while(q.size() > 1 && (sump <= sumn || q.front() < 0)) {
                int np = q.front();
                if(np >= 0) sump -= np;
                else sumn -= -np;
                q.pop();
            }
            ans = max(ans, sump-sumn);
        }
        cout << ans << endl;
    }
    return 0;
}
