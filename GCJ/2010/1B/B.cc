#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int N, K, B, T;
        cin >> N >> K >> B >> T;

        vector<int> pos(N);
        vector<int> speed(N);
        vector<bool> goalable(N, false);
        for(int i = 0; i < N; ++i) {
            cin >> pos[i];
        }
        for(int i = 0; i < N; ++i) {
            cin >> speed[i];
        }

        int swapcnt = 0;
        int goalcnt = 0;
        for(int i = N-1; i >= 0; --i) {
            int rem = (B-pos[i]) % speed[i];
            int timecnt = (B-pos[i]) / speed[i];
            if(rem != 0) ++timecnt;

            int over = speed[i]-rem;
            if(timecnt <= T) {
                int swapcnt_tmp = 0;
                for(int j = i+1; j < N; ++j) {
                    if(goalable[j]) {
                        continue;
                    }
                    int catchtime = (pos[j]-pos[i]) / (speed[i]-speed[j]);
                    int rem = (pos[j]-pos[i]) - (speed[i]-speed[j])*catchtime;
                    if(rem != 0) {
                        over -= (speed[i]-rem);
                        if(over < 0) {
                            ++timecnt;
                            over += speed[i];
                        }
                    }
                    ++swapcnt_tmp;
                }
                if(timecnt <= T) {
                    ++goalcnt;
                    swapcnt += swapcnt_tmp;
                    goalable[i] = true;
                    if(goalcnt >= K) break;
                }
            }
        }
        if(goalcnt >= K) {
            printf("Case #%d: %d\n", C, swapcnt);
        }
        else {
            printf("Case #%d: IMPOSSIBLE\n", C);
        }
    }

    return 0;
}

