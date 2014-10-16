//Name: Next Mayor
//Level: 2
//Category: シミュレーション
//Note:

/**
 * 100万ステップ以内に終わることが分かっているので、素直にシミュレーションすればよい。
 * オーダーは O(TN)。
 * ただしTは終了までのターン数。
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N, P;
        cin >> N >> P;
        if(!N && !P) break;

        vector<int> v(N, 0);
        int cup = P;
        int pos = 0;
        int winner = 0;
        while(true) {
            if(cup > 0) {
                v[pos] += 1;
                cup -= 1;
                if(cup == 0) {
                    bool win = true;
                    for(int i = 0; i < N; ++i)
                        if(i != pos && v[i]) win = false;
                    if(win) {
                        winner = pos;
                        break;
                    }
                }
            }
            else {
                cup = v[pos];
                v[pos] = 0;
            }
            pos = (pos+1) % N;
        }

        cout << winner << endl;
    }
    return 0;
}
