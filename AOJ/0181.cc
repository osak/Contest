//Name: Persistence
//Level: 2
//Category: 二分探索,貪欲法,Greedy
//Note:

/*
 * 幅が決まれば，本の入れ方は上から入れられるだけ入れていくのが最適である．
 * (あえてスペースを余らせても，後ろがつかえるだけである)
 * よって，幅に関して二分探索すればよい．
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int M, N;
        cin >> M >> N;
        if(!M && !N) break;
        vector<int> books(N);
        for(int i = 0; i < N; ++i) {
            cin >> books[i];
        }
        int left = 0, right = 1500000;
        while(left < right) {
            int len = (left+right)>>1;
            bool ok = true;
            int pos = 1, acc = 0;
            for(int i = 0; i < N; ++i) {
                if(len < books[i]) {
                    ok = false;
                    break;
                }
                int nacc = acc + books[i];
                if(nacc > len) {
                    ++pos;
                    acc = books[i];
                } else {
                    acc = nacc;
                }
                if(pos > M) {
                    ok = false;
                    break;
                }
            }
            if(ok) right = len;
            else left = len+1;
        }
        cout << left << endl;
    }
    return 0;
}
