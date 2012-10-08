//Name: ICPC: Ideal Coin Payment and Change
//Level: 2
//Category: 全探索
//Note:

/*
 * 
 * 硬貨の合計金額は高々(1+5+10+50+100+500)*1000 = 216000 円．
 * したがって払う金額を全て試しながら，最小の硬貨数で実現できるものを選べばよい．
 * 払えない金額が存在することに注意．
 *
 * オーダーは与えられる硬貨の合計金額に比例する．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int VALUE[] = {1, 5, 10, 50, 100, 500};
int coins[6];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        int P;
        cin >> P;
        int max_val = 0;
        for(int i = 0; i < 6; ++i) {
            cin >> coins[i];
            max_val += VALUE[i] * coins[i];
        }
        if(!P) break;

        int ans = max_val;
        for(int total = P; total <= max_val; ++total) {
            int use_coins = 0;
            int tmp = total;
            for(int i = 5; i >= 0; --i) {
                const int cost = VALUE[i] * coins[i];
                if(cost <= tmp) {
                    use_coins += coins[i];
                    tmp -= cost;
                } else {
                    const int use = tmp / VALUE[i];
                    use_coins += use;
                    tmp -= VALUE[i] * use;
                }
                if(tmp == 0) break;
            }
            if(tmp != 0) continue; // Cannot make #{total} yen.
            int residue = total - P;
            for(int i = 5; i >= 0; --i) {
                use_coins += residue / VALUE[i];
                residue %= VALUE[i];
            }
            ans = min(ans, use_coins);
        }
        cout << ans << endl;
    }
    return 0;
}
