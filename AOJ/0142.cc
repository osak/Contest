//Name: Nature of Prime Numbers
//Level: 1
//Category: やるだけ
//Note: 問題文が読みにくい

/**
 * 問題文がかなり分かりにくいが、要するに
 * ・a_i = i^2 mod n (1 ≦ i < n)
 * ・S = unique set of a_i
 * ・d_j = (a - b) mod n (a, b ∈ S, a≠b)
 * ・e_j = max(0, min(d_j, n-d_j))
 * としたとき、e_jのヒストグラムを作れば良い。
 * 問題文の残りの部分は、nが素数かつn≡3 (mod 4) のときに、e_jのヒストグラムが
 * 平らになることを主張している。
 */
#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    set<int> s;
    for(int i = 0; i < N-1; ++i) {
        s.insert((i+1)*(i+1) % N);
    }
    vector<int> hist((N-1)/2, 0);
    for(auto it1 = begin(s); it1 != end(s); ++it1) {
        for(auto it2 = begin(s); it2 != it1; ++it2) {
            int e = (*it1 - *it2 + N) % N;
            if(e > (N-1)/2) e = N - e;
            hist[e-1]++;
        }
    }
    for(int i : hist) {
        cout << i*2 << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(2);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
