//Name: Patrol
//Level: 1
//Category: グラフ,Graph
//Note:

/*
 * オイラー路の有無は奇点の個数を数えれば判定できる．
 * ここではスタートとゴールが固定されているので，これらは奇点である必要がある．
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int A, B;
    while(cin >> A >> B) {
        vector<int> dim(200, 0);
        do {
            dim[A-1]++;
            dim[B-1]++;
            cin >> A >> B;
        } while(A != 0 || B != 0);
        int odds = 0;
        for(int i = 0; i < 200; ++i) {
            if(dim[i] % 2 == 1) ++odds;
        }
        if(dim[0] % 2 == 1 && dim[1] % 2 == 1 && odds == 2) {
            cout << "OK" << endl;
        } else {
            cout << "NG" << endl;
        }
    }
    return 0;
}
