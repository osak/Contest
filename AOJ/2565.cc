//Name: Broken Audio Signal
//Level: 2
//Category: シミュレーション
//Note:

/**
 * xがとり得る値の上限と下限を覚えておきながら、数列を走査していく。
 * xが連続していたり、途中でxが絡まない矛盾が発生していたりすることに注意。
 * また、xのとり得る範囲はa_iがとり得る範囲よりすこし広い。
 *
 * オーダーは O(N)。
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

enum Type {
    NUM, X
};

struct Tag {
    Type type;
    int val;
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<Tag> v(N);
    for(int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        if(s == "x") {
            v[i].type = X;
        } else {
            v[i].type = NUM;
            v[i].val = stoi(s);
        }
    }

    pair<int,int> res(-1000000000-10, 1000000000+10);
    bool inconsistent = false;
    for(int i = 0; i < N; ++i) {
        if(v[i].type == X) {
            if(i % 2 == 1) {
                if(i > 0) res.first = max(res.first, v[i-1].val+1);
                if(i < N-1) res.first = max(res.first, v[i+1].val+1);
            } else {
                if(i > 0) res.second = min(res.second, v[i-1].val-1);
                if(i < N-1) res.second = min(res.second, v[i+1].val-1);
            }
            if(i > 0 && v[i-1].type == X) inconsistent = true;
        } else {
            if(i % 2 == 1) {
                if(i > 0 && v[i-1].type == NUM) inconsistent = inconsistent || (v[i-1].val >= v[i].val);
                if(i < N-1 && v[i+1].type == NUM) inconsistent = inconsistent || (v[i+1].val >= v[i].val);
            } else {
                if(i > 0 && v[i-1].type == NUM) inconsistent = inconsistent || (v[i-1].val <= v[i].val);
                if(i < N-1 && v[i+1].type == NUM) inconsistent = inconsistent || (v[i+1].val <= v[i].val);
            }
        }
        //cout << res.first << ' ' << res.second << endl;
    }
    if(inconsistent || res.first > res.second) {
        cout << "none" << endl;
    } else if(res.first == res.second) {
        cout << res.first << endl;
    } else {
        cout << "ambiguous" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
