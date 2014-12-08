//Name: Programming Contest Challenge Book
//Level: 3
//Category: 数学,Math,考察
//Note:

/**
 * 棒を長さの降順でソートしてから考える。
 * 以下、三角形の辺に関して長い方からp,q,rと呼ぶことにする。
 *
 * 三角形を1つ作るとき、棒iを辺pとして採用すると、三角不等式のうちp+q>rとp+r>qが満たされることは自明である。
 * q+r>pであるためにはbとcを可能な限り大きく取ればよいから、結局棒i+1とi+2を加えて三角形を構成できなければ、棒iを辺pとした三角形は構成できないことがわかる。
 *
 * この考察から、連続する3辺で三角形が作れるかを考えながら貪欲に構成していくという方法が思いつくが、これでは3 3 2 2 1 1のような列のときにうまくいかない。
 * すなわち、a_{i+3}≧a_{i+4}+a_{i+5}であるが、2つの三角形に割り当てる順番をうまく入れ替えてやるとちょうど割り当てられる場合である。
 * このような場合は、棒iから連続する6つの棒だけを使って2つの三角形を構成しないと意味がないため、全探索すればよい
 * （周長を最大化する制約から、この6つよりも短い棒を使っている場合、iを超えない範囲で長い棒に入れ替えることは安全であり、かつ得をする）。
 *
 * オーダーは O(N log N)。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    vector<long long> as(N);
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
    }
    sort(begin(as), end(as), greater<long long>());

    typedef vector<int> Choice;
    vector<pair<Choice,Choice>> choose_3;
    for(int pat = 0; pat < (1<<6); ++pat) {
        if(__builtin_popcount(pat) != 3) continue;
        Choice c1, c2;
        for(int i = 0; i < 6; ++i) {
            if(pat & (1<<i)) c1.push_back(i);
            else c2.push_back(i);
        }
        choose_3.emplace_back(c1, c2);
    }

    long long ans = 0;
    int composed = 0;
    for(int i = 0; i <= N-3; ++i) {
        // Check if all 6 sticks can be used
        if(composed == 0 && i <= N-6) {
            for(auto pat : choose_3) {
                const auto &c1 = pat.first;
                const auto &c2 = pat.second;
                if(as[i+c1[0]] < as[i+c1[1]]+as[i+c1[2]] && as[i+c2[0]] < as[i+c2[1]]+as[i+c2[2]]) {
                    ans = accumulate(begin(as)+i, begin(as)+i+6, 0LL);
                    composed = 2;
                    goto end;
                }
            }
        }
        // Check if 3 sticks can be used
        if(as[i] < as[i+1] + as[i+2]) {
            ans += as[i]+as[i+1]+as[i+2];
            if(++composed == 2) break;
            i += 2;
        }
    }
end:
    if(composed != 2) ans = 0;
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
