//Name: Jeff and Furik
//Level: 3
//Category: 期待値,漸化式
//Note: Codeforces Round #204(Div.1)

/*
 * やっていることはバブルソートなので、転倒数を1ずつ増減させていくことと等しい。
 * [手番][転倒数]の状態からソート済みに持っていくための手数の期待値は、
 *   [Jeff][k] = 1 + [Furik][k-1]
 *   [Furik][k] = 1 + 0.5([Jeff][k+1] + [Jeff][k-1]) (k < L)
 *                1 + [Jeff][k-1]                    (k = L)
 * となる。ただし、Lは転倒数の最大値N*N(N-1)/2である。
 * この式を簡約すると、
 *   [Jeff][k] = 4 + [Jeff][k-2]
 *   [Furik][k] = 4 + [Furik][k-2]
 * となる。
 * 毎回Jeffから始まるため、実はk=LでFurikの手番が回ってくることはない。
 *
 * オーダーはO(N^2)。
 * これは転倒数を求めるオーダーである。
 */
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<int> v(N);
    int invnum = 0;
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
        for(int j = 0; j < i; ++j) {
            if(v[i] < v[j]) ++invnum;
        }
    }

    if(invnum % 2 == 0) {
        cout << invnum*2 << endl;
    } else {
        cout << 1 + (invnum-1)*2 << endl;
    }
    return 0;
}
