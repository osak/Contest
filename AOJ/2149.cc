//Name: Luck Manipulator
//Level: 1
//Category: シミュレーション
//Note:

/*
 * 10000ターン分シミュレーションする。
 */
#include <iostream>
#include <vector>

using namespace std;

int A, B, C;
int X;

int myrand() {
    int res = X;
    X = (A*X + B) % C;
    return res;
}

bool solve() {
    int N;
    cin >> N >> A >> B >> C >> X;
    if(!N && !A && !B && !C && !X) return false;

    vector<int> ys(N);
    for(int i = 0; i < N; ++i) {
        cin >> ys[i];
    }
    int turn = 0;
    int pos = 0;
    for(; turn <= 10000; ++turn) {
        int rv = myrand();
        if(rv == ys[pos]) {
            ++pos;
            if(pos == N) break;
        }
    }
    cout << (turn > 10000 ? -1 : turn) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    for(int case_num = 1; solve(); ++case_num) ;
    return 0;
}
