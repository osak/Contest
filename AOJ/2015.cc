//Name: Square Route
//Level: 3
//Category: データ構造,二分探索
//Note:

/**
 * 縦方向と横方向のそれぞれについて、構成可能な幅をすべて列挙し、それぞれの幅について何通りの構成方法があるかを記録しておく。
 * すると、大きさsである正方形の構成方法は、縦方向と横方向でそれぞれsを構成できればこれらの組み合わせは任意なので、個数の積が組み合わせ数となる。
 * これはmapを使うことで効率的に求められる。
 *
 * オーダーは O(N^2 log M)。
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<int> hs(N), ws(M);
    for(int i = 0; i < N; ++i) {
        cin >> hs[i];
        if(i > 0) hs[i] += hs[i-1];
    }
    for(int i = 0; i < M; ++i) {
        cin >> ws[i];
        if(i > 0) ws[i] += ws[i-1];
    }

    map<int,int> hmap;
    for(int i = -1; i < N; ++i) {
        const int hi = i >= 0 ? hs[i] : 0;
        for(int j = i+1; j < N; ++j) {
            hmap[hs[j] - hi]++;
        }
    }
    int ans = 0;
    for(int i = -1; i < M; ++i) {
        const int wi = i >= 0 ? ws[i] : 0;
        for(int j = i+1; j < M; ++j) {
            ans += hmap[ws[j] - wi];
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
