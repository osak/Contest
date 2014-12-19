//Name: Alphametic
//Level: 2
//Category: 文字列,全探索,多倍長
//Note:

/**
 * Xに入る数字を全通り試し、実際に計算して等式が成立するかを確認する。
 * ただし数値がとても大きくなるため、計算は多倍長で行う必要がある。
 * 答えが0になることもあるので、preceding zeroの扱いで注意が必要。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

typedef string::const_iterator Iterator;

vector<int> number(Iterator &it) {
    vector<int> res;
    while(isdigit(*it)) {
        res.push_back(*it++ - '0');
    }
    reverse(begin(res), end(res));
    return res;
}

bool check(string s, int x) {
    for(char &c : s) {
        if(c == 'X') c = '0' + x;
    }

    Iterator it = s.begin();
    vector<int> n1 = number(it);
    assert(*it++ == '+');
    vector<int> n2 = number(it);
    assert(*it++ == '=');
    vector<int> ans = number(it);
    if((n1.size() >= 2 && n1.back() == 0) || (n2.size() >= 2 && n2.back() == 0) || (ans.size() >= 2 && ans.back() == 0)) return false;

    const int L = max(n1.size(), n2.size());
    vector<int> sum(L+1, 0);
    for(int i = 0; i < L; ++i) {
        if(i < n1.size()) sum[i] += n1[i];
        if(i < n2.size()) sum[i] += n2[i];
        if(sum[i] >= 10) {
            sum[i] -= 10;
            sum[i+1]++;
        }
    }
    while(sum.size() >= 2 && sum.back() == 0) sum.pop_back();
    return sum == ans;
}

bool solve() {
    string line;
    if(!(cin >> line)) return false;
    int ans = -1;
    for(int x = 0; x <= 9; ++x) {
        if(check(line, x)) {
            ans = x;
            break;
        }
    }
    if(ans == -1) cout << "NA" << endl;
    else cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
