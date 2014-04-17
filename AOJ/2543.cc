//Name: Ancient Scrolls
//Level: 5
//Category: 数学
//Note:

/**
 * 先頭から1文字ずつ決めていく。
 * このとき、考えるべき文字は、該当する場所にある3文字と大文字のAだけである。
 *
 * 1文字決めたとき、ハミング距離の条件を満たした上でそれ以降を決める方法があるかを判定する。
 * k文字目の状態は
 * ・全ての文字列が同じ文字
 * ・1つだけ違う文字がある(3通り)
 * ・すべての文字が違う
 * の5通り。
 * このうち、最初のパターンではその文字を当てはめればよい。
 * 残りのパターンが問題となるが、まずは貪欲に、1つだけ違う箇所(=2つが一致している箇所)を
 * 2つのほうに寄せるようにして考える。
 * このとき、各文字列について、これらの位置だけで考えたハミング距離(=文字列iだけ違うような場所の個数)をr_iとすると、
 * u_i = a - (D_i - r_i) 個以上を文字列iに寄せなければならない。
 * ここで、aは最後のパターンに該当する場所の数、D_iは文字列iが使えるハミング距離の最大値である。
 *
 * このとき、∑max(0, u_i) ≦ a であれば達成可能である。
 * そうでないとき、たとえばu_0のみが正であったとすると、aに該当する文字をすべて文字列0に寄せた上で、
 * 加えて文字列0の文字のみが異なるような箇所を文字列0に寄せることで、
 * u_0を1だけ減らし、u_1, u_2を1ずつ増やすことができる。
 * このとき、この操作はmin(-u_1, -u_2)回までなら上の総和を減らすことにつながるから、u_0 - min(r_i, -u_1, -u_2) ≦ a であればやはり達成可能となる。
 * u_1, u_2についても同様。
 * u_0, u_1の2つが正のときには、このような寄せ方をしても総和は減らないため、達成不可能である。
 *
 * オーダーは O(L)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool solve() {
    int L, D;
    if(!(cin >> L >> D)) return false;
    if(!L && !D) return false;

    string strs[3];
    for(int i = 0; i < 3; ++i) {
        cin >> strs[i];
    }

    vector<int> diff_by_one[3];
    vector<int> all_diff(L+1, 0);
    for(int i = 0; i < 3; ++i) {
        diff_by_one[i].resize(L+1, 0);
        const int next = (i+1) % 3;
        const int prev = (i+2) % 3;
        for(int j = 0; j < L; ++j) {
            if(strs[i][j] != strs[next][j] && strs[next][j] == strs[prev][j]) {
                diff_by_one[i][j] = 1;
            }
        }
        for(int j = L-1; j >= 0; --j) {
            diff_by_one[i][j] += diff_by_one[i][j+1];
        }
    }
    for(int i = 0; i < L; ++i) {
        if(strs[0][i] != strs[1][i] && strs[1][i] != strs[2][i] && strs[2][i] != strs[0][i]) {
            all_diff[i] = 1;
        }
    }
    for(int i = L-1; i >= 0; --i) {
        all_diff[i] += all_diff[i+1];
    }

    string res;
    vector<int> remain(3, D);
    for(int i = 0; i < L; ++i) {
        char ch = '\x7f';
        for(int idx = 0; idx < 4; ++idx) {
            const char test_ch = idx == 0 ? 'A' : strs[idx-1][i];
            int sum = 0;
            int r[3] = {0};
            int u[3] = {0};
            for(int j = 0; j < 3; ++j) {
                const int next_rem = remain[j] - (test_ch == strs[j][i] ? 0 : 1);
                r[j] = next_rem - diff_by_one[j][i+1];
                u[j] = all_diff[i+1] - r[j];
                sum += max(0, u[j]);
            }
            bool ok = sum <= all_diff[i+1];
            if(!ok) {
                if(u[0] <= 0 && u[1] <= 0) {
                    ok = sum - min({diff_by_one[2][i+1], -u[0], -u[1]}) <= all_diff[i+1];
                }
                if(u[1] <= 0 && u[2] <= 0) {
                    ok = sum - min({diff_by_one[0][i+1], -u[1], -u[2]}) <= all_diff[i+1];
                }
                if(u[2] <= 0 && u[0] <= 0) {
                    ok = sum - min({diff_by_one[1][i+1], -u[2], -u[0]}) <= all_diff[i+1];
                }
            }
            if(ok) {
                ch = min(ch, test_ch);
                //cout << i << ' ' << ch << endl;
            }
            if(ch == 'A') break;
        }
        if(ch == '\x7f') {
            res = "-1";
            break;
        } else {
            res += ch;
            //cout << res << endl;
            for(int j = 0; j < 3; ++j) {
                remain[j] -= (ch == strs[j][i] ? 0 : 1);
            }
        }
    }
    cout << res << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
