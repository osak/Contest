//Name: K Cards
//Level: 2
//Category: 全探索
//Note:

/**
 * 連続K枚の積を改善するには、もっとも小さい数を取り除き、K枚に入ってないものの中でもっとも大きい数を入れれば良い。
 * オーダーは O(N^2)。
 */
#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N, K;
    if(!(cin >> N >> K)) return false;
    if(!N && !K) return false;

    vector<int> cs(N);
    for(int i = 0; i < N; ++i) {
        cin >> cs[i];
    }

    int c1 = 0, c2 = 0;
    for(int i = 0; i <= N-K; ++i) {
        int c1_tmp = 1;
        int min_val = 100;
        for(int k = 0; k < K; ++k) {
            c1_tmp *= cs[i+k];
            min_val = min(min_val, cs[i+k]);
        }
        c1 = max(c1, c1_tmp);

        int to_swap = 0;
        for(int j = 0; j < N; ++j) {
            if(i <= j && j < i+K) continue;
            to_swap = max(to_swap, cs[j]);
        }
        c2 = max(c2, c1_tmp / min_val * to_swap);
    }
    if(c1 <= c2) {
        cout << c2-c1 << endl;
    } else {
        cout << "NO GAME" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
