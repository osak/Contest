//Name: The Brand New Function
//Level: 3
//Category: 全探索
//Note: Codeforces #150(Div 1)

/*
 * 連続した数の or を取るので，a_1からa_i, a_2からa_i，……の和全てから成る集合はそんなに要素数がないだろう，
 * という推測の下で書いたら通った．
 *
 * オーダーはちゃんと吟味してない(TODO)
 */
#include <iostream>
#include <set>
#include <cstdio>

using namespace std;

int main() {
    int N;
    while(scanf("%d", &N) != EOF) {
        set<int> ans;
        set<int> list;
        while(N--) {
            int a;
            scanf("%d", &a);
            set<int> next;
            next.insert(a);
            ans.insert(a);
            for(set<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
                const int val = *it | a;
                next.insert(val);
                ans.insert(val);
            }
            list.swap(next);
        }
        cout << ans.size() << endl;
    }
    return 0;
}
