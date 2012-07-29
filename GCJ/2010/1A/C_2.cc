#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

//int cache[1000000][1000000];

bool canwin(int a, int b) {
    if(a == b) return 0;
    if(a == 1 || b == 1) return 1;
   // if(cache[a][b] == -1) {
        int maxnum = max(a, b);
        int minnum = min(a, b);

        if(maxnum % minnum == 0) return 1;

        //cache[b][a] = cache[a][b] = 0;
        for(int i = maxnum-minnum; i > 0; i -= minnum) {
            if(!canwin(i, minnum)) {
                //cache[b][a] = cache[a][b] = 1;
                return 1;
                break;
            }
        }
        return 0;
   // }
    //return cache[a][b];
}

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;

        int arange = a2-a1+1;
        int brange = b2-b1+1;
        vector<vector<bool> > dp(a2-a1+1, vector<bool>(b2-b1+1, false));

        /*
        for(int i = 0; i < 100; ++i) {
            for(int j = 0; j < 100; ++j) {
                cache[i][j] = -1;
                if(i == 1 || j == 1) cache[i][j] = 1;
                if(i == j) cache[i][j] = 0;
            }
        }
        */
        int cnt = 0;
        for(int a = a1; a <= a2; ++a) {
            for(int b = b1; b <= b2; ++b) {
                if(canwin(a, b)) {
                    ++cnt;
                    //cout << a << "  " << b << endl;
                }
                cerr << a << " " << b << endl;
            }
        }

        printf("Case #%d: %d\n", C, cnt);
    }
}
