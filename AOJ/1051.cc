//Name: Citation Format
//Level: 2
//Category: 実装
//Note:

/**
 * 数値が連続している間を検出する。
 */
#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    int prev = -1;
    int cur_start = -1;
    bool first = true;
    for(int i = 0; i < N; ++i) {
        int p;
        cin >> p;
        if(p != prev+1) {
            if(prev != -1) {
                if(!first) cout << ' ';
                if(prev == cur_start) cout << prev;
                else cout << cur_start << '-' << prev;
                first = false;
            }
            cur_start = p;
        }
        prev = p;
    }
    if(!first) cout << ' ';
    if(prev == cur_start) cout << prev;
    else cout << cur_start << '-' << prev;
    cout << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
