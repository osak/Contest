//Name: Constellations
//Level: 4
//Category: ハッシュ,Rabin-Karp
//Note: 星座の種類のみ(出現回数ではない)を答える

/*
 * 普通に判定すると最大 1000*1000*100*50*50 で間に合わない．
 * 星座の大きさが固定なので，P*Qの区間についてRabin-Karp(ローリングハッシュ)でハッシュ値を計算して星座のハッシュ値と比べればよい．
 * ハッシュ値としてあり得る値は高々 1000*1000 + 100 通りなので，unsigned long long で持てばまず衝突しないと考えられる．
 *
 * オーダーは O(NM log T)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned long long LineType;

const LineType MUL = 1000000009;

LineType field[1000][1000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int CASE = 1; ; ++CASE) {
        int N, M, T, P, Q;
        cin >> N >> M >> T >> P >> Q;
        if(!N && !M && !T && !P && !Q) break;
        const LineType mask = (1LL<<Q)-1;
        for(int i = 0; i < N; ++i) {
            string line;
            cin >> line;
            LineType l = 0;
            for(int j = 0; j < M; ++j) {
                l <<= 1;
                l &= mask;
                if(line[j] == '*') l |= 1;
                if(j+1 >= Q) field[i][j+1-Q] = l;
            }
        }
        
        // constellations
        vector<LineType> cs;
        for(int k = 0; k < T; ++k) {
            LineType hash = 0;
            for(int i = 0; i < P; ++i) {
                string line;
                cin >> line;
                LineType l = 0;
                for(int j = 0; j < Q; ++j) {
                    l <<= 1;
                    if(line[j] == '*') l |= 1;
                }
                hash *= MUL;
                hash += l;
            }
            cs.push_back(hash);
        }
        sort(cs.begin(), cs.end());

        LineType topmul = 1;
        for(int i = 0; i < P-1; ++i) topmul *= MUL;

        int ans = 0;
        for(int c = 0; c < M-Q+1; ++c) {
            LineType hash = 0;
            for(int r = 0; r < N; ++r) {
                if(r >= P) hash -= topmul*field[r-P][c];
                hash *= MUL;
                hash += field[r][c];
                if(r+1 >= P) {
                    //if(hmap.count(hash)) ++ans;
                    pair<vector<LineType>::iterator,vector<LineType>::iterator> range = equal_range(cs.begin(), cs.end(), hash);
                    ans += range.second-range.first;
                    cs.erase(range.first, range.second);
                }
            }
        }

        cout << "Case " << CASE << ": " << ans << endl;
    }
    return 0;
}
