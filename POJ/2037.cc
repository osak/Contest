//Name: Roll Playing Games
//Level: 4
//Category: 探索,半分全列挙
//Note: POJではTLE(-O2でジャッジデータ食わせたら一致した)

/*
 * サイコロが全部で20+1個なので，可能な合計値は高々1050．
 * 決定しているサイコロを順に処理することで，これらを用いて合計sを出すパターンは計算できる．
 * 最後のサイコロの面は，R/2個のパターンを半分全列挙してマッチさせる．
 *
 * オーダーは O(50^(R/2) log 50^(R/2))  くらい．
 */

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

typedef map<vector<long long>, vector<int> > Dict;

long long tbl[2][1051];
int M;
long long *tblptr;
pair<int,int> constraints[10];

void gendict(int depth, int lim, vector<int> &pat, Dict &dict) {
    if(depth == 0) {
        vector<long long> acc(M, 0);
        FOREACH(it, pat) {
            for(int j = 0; j < M; ++j) {
                const int idx = constraints[j].first;
                if(idx-*it >= 0) acc[j] += tblptr[idx-*it];
            }
        }
        Dict::iterator it = dict.find(acc);
        if(it == dict.end()) dict[acc] = pat;
    } else {
        for(int i = lim; i <= 50; ++i) {
            pat.push_back(i);
            gendict(depth-1, i, pat, dict);
            pat.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        long long *cur = tbl[0], *prev = tbl[1];
        fill_n(prev, 1051, 0);
        prev[0] = 1;
        for(int i = 0; i < N; ++i) {
            int F;
            cin >> F;
            fill_n(cur, 1051, 0);
            while(F--) {
                int val;
                cin >> val;
                for(int j = 0; j <= 1050-val; ++j) {
                    cur[j+val] += prev[j];
                }
            }
            swap(cur, prev);
        }
        tblptr = prev;

        int R;
        cin >> R >> M;
        vector<int> ans(R, 51);
        Dict dicta, dictb;
        for(int i = 0; i < M; ++i) {
            pair<int,int> &p = constraints[i];
            cin >> p.first >> p.second;
            if(p.first > 1050) {
                goto impossible;
            }
        }

        if(R == 4) {
            vector<int> pat;
            gendict(2, 1, pat, dicta);
            dictb = dicta;
        } else if(R == 5) {
            vector<int> pat;
            gendict(2, 1, pat, dicta);
            gendict(3, 1, pat, dictb);
        } else if(R == 6) {
            vector<int> pat;
            gendict(3, 1, pat, dicta);
            dictb = dicta;
        }
        {
            vector<long long> need(M, 0);
            FOREACH(it, dicta) {
                const vector<long long> &acc = it->first;
                const vector<int> &pat = it->second;
                for(int i = 0; i < M; ++i) {
                    need[i] = constraints[i].second - acc[i];
                }
                Dict::const_iterator match = dictb.find(need);
                if(match != dictb.end()) {
                    vector<int> cand(pat);
                    cand.insert(cand.end(), match->second.begin(), match->second.end());
                    sort(cand.begin(), cand.end());
                    if(ans > cand) ans = cand;
                }
            }
        }
        if(ans[0] <= 50) {
            cout << "Final die face values are";
            FOREACH(it, ans) {
                cout << ' ' << *it;
            }
            cout << endl;
            continue;
        }
impossible:
        cout << "Impossible" << endl;
    }
    return 0;
}
