//Name: Balancing the Scale
//Level: 4
//Category: 探索,組み合わせ
//Note:

/*
 * ある8つの数字を選んだ時に，条件を満たす並べ方が何通りあるか求められれば答えは容易に算出できる．
 * この並べ方の数は，まず与えられた数列から得られる16P4通りの数字の組全てに対し，
 * 問題文の数式が与える値を算出してこの値ごとにグルーピングしておく．
 * （全ての数字が異なるという条件に注意）
 * 次に，各グループ内で，共通部分をもたないパターンの組があれば，それは8つの数字を条件を満たすように
 * 並べる並べ方を表す．
 *
 * 与えられる数値に重複を許した時は最悪(16P4)^2程度のループが回るが，全ての数値が異なる時は
 * 適度にばらけるため，高速に終わるようである．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

vector<int> cb16c4;
void init() {
    TIMES(i, 1<<16) {
        if(__builtin_popcount(i) == 4) {
            cb16c4.push_back(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();
    vector<int> buf(16);
    for(int CASE = 1; ; ++CASE) {
        TIMES(i, 16) {
            cin >> buf[i];
        }
        if(!buf[0]) break;
        sort(buf.begin(), buf.end());

        vector<long long> valid_count_of(1<<16, 0);
        vector<vector<int> > patterns_of(10240);
        FOREACH(it, cb16c4) {
            vector<int> tmp;
            TIMES(i, 16) {
                if(*it & (1<<i)) tmp.push_back(buf[i]);
            }
            do {
                int sum = 0;
                TIMES(i, 4) {
                    sum += (i+1) * tmp[i];
                }
                patterns_of[sum].push_back(*it);
            } while(next_permutation(tmp.begin(), tmp.end()));
        }
        FOREACH(it, patterns_of) {
            const vector<int> &v = *it;
            const int N = v.size();
            TIMES(i, N) {
                TIMES(j, i) {
                    if((v[i] & v[j]) == 0) valid_count_of[v[i]|v[j]]++;
                }
            }
        }
        long long ans = 0;
        TIMES(pat, 1<<16) {
            ans += valid_count_of[pat] * valid_count_of[0xffff ^ pat];
        }
        cout << "Case " << CASE << ": " << ans/2 << endl;
    }
    return 0;
}
