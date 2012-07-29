//Name: Ball
//Level: 1
//Category: 全探索,シミュレーション
//Note:

/*
 * 10個しかないので、全てのボールについて左右それぞれ全探索すればよい。
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    while(N--) {
        vector<int> v(10);
        for(int i = 0; i < 10; ++i) cin >> v[i];
        bool ok = false;
        for(int pat = 0; pat < (1<<10); ++pat) {
            bool sorted = true;
            int prev = -1;
            for(int i = 0; i < 10; ++i) {
                if(pat & (1<<i)) {
                    if(v[i] < prev) {
                        sorted = false;
                        break;
                    }
                    prev = v[i];
                }
            }
            prev = -1;
            for(int i = 0; i < 10; ++i) {
                if(~pat & (1<<i)) {
                    if(v[i] < prev) {
                        sorted = false;
                        break;
                    }
                    prev = v[i];
                }
            }
            if(sorted) {
                ok = true;
                break;
            }
        }

        cout << (ok?"YES":"NO") << endl;
    }
    return 0;
}
