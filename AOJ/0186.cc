//Name: Aizu Chicken
//Level: 1
//Category: 全探索
//Note:

/*
 * 会津地鶏を買う量を1刻みで決めていき，それに対して条件を満たすように買えるか調べていく．
 */
#include <iostream>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        int Q1, B, C1, C2, Q2;
        cin >> Q1 >> B >> C1 >> C2 >> Q2;
        if(!Q1) break;

        bool found = false;
        for(int q2 = Q2; q2 >= 1; --q2) {
            const int cost1 = C1*q2;
            const int rem = B - cost1;
            if(rem < 0) continue;
            const int amount = rem / C2;
            //cout << q2 << ' ' << rem << ' ' << amount << endl;
            if(q2 + amount >= Q1) {
                cout << q2 << ' ' << amount << endl;
                found = true;
                break;
            }
        }
        if(!found) {
            cout << "NA" << endl;
        }
    }
    return 0;
}
