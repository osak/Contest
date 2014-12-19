//Name: Period
//Level: 2
//Category: 数学,メモ化
//Note:

/**
 * 筆算をシミュレーションしながら、これまでに出た余りと出た場所を覚えておく。
 * 同じ余りが出た場合、直前にその余りが出た場所から末尾までが循環節となる。
 *
 * オーダーは O(Q + log P)。
 */
#include <iostream>
#include <map>
#include <string>

using namespace std;

bool solve() {
    int P, Q;
    if(!(cin >> P >> Q)) return false;

    string ans, loop;
    map<int,int> dict;
    int rem = P * 10;
    for(int i = 0; ; ++i) {
        if(rem == 0) break;
        auto it = dict.find(rem);
        if(it != dict.end()) {
            for(int j = 0; j < it->second; ++j) loop += " ";
            for(int j = it->second; j < i; ++j) loop += "^";
            break;
        }
        dict[rem] = i;
        ans += '0' + (rem / Q);
        rem %= Q;
        rem *= 10;
    }
    cout << ans << endl;
    if(loop != "") cout << loop << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
