#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;

        int cnt = 0;
        for(int i = a1; i <= a2; ++i) {
            for(int j = b1; j <= b2; ++j) {
                int a = min(i, j);
                int b = max(i, j);
                
                int div = b/a-1;
                int c = b-a*div;
                if(c == b) continue;
                if(c % (c-b) == 0) {
                    ++cnt;
                    continue;
                }

                ++div;
                c = b-a*div;
                if(c % (a-c) == 0) {
                    ++cnt;
                }
            }
        }

        cout << cnt << endl;
    }
}
