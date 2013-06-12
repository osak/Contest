//Name: Fibonatti Numbers
//Level: 5
//Category: DP,数え上げ
//Note:

/*
 * ある文字列にpが何回出現するかはKMP法で計算できる．
 *
 * F(k)がpの長さより長い場合，F(k)内のpの個数は
 * ・F(k-1)内のpの個数
 * ・F(k-2)内のpの個数
 * ・F(k-1)のsuffix len(p)-1文字とF(k-2)のprefix len(p)-1文字を結合した文字列内のpの個数
 * の合計となる．
 * suffix, prefixは再帰的に，簡単に生成することが可能．
 * pは高々10^5文字なので，N ≦100ですべてのsuffix, prefixを生成しても十分メモリに乗る．
 *
 * F(k)がpの長さと比べて短い場合，3つ以上の結合をまたいでpが出現する可能性がある．
 * これは，F(k)がpの長さより短い場合は実際にF(k)を生成してしまい，直接出現数を数えてその値を使うことで回避できる．
 *
 * len(p) == 1のときは上記の議論が通用しないため，
 * 0と1の個数がフィボナッチ数列で増加していくことを利用して特別に処理する．
 *
 * オーダーは O(N|p|) 程度．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

#define TIMES(i,n) for(int i=0; (i) < (n); ++(i))
#define FOREACH(it,v) for(typeof((v).begin()) it=(v).begin(); (it) != (v).end(); ++(it))

typedef unsigned long long ULL;

ULL memo[200];
bool visited[200];
vector<string> fib;
vector<string> prefix, suffix;

const int SHORT_N = 27;
void init() {
    // Enumerate fibonatti string from N = 0 to 32
    // to avoid triple connection which yields pattern
    fib.resize(SHORT_N+1);
    fib[0] = "0";
    fib[1] = "1";
    for(int i = 2; i < SHORT_N+1; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    assert(fib[SHORT_N].size() == 317811);
}

ULL kmp_match_count(const string &str, const vector<vector<int> > &kmp, int *pos = NULL) {
    const int L = kmp.size()-1;
    int cur = pos ? *pos : 0;
    ULL ans = 0;
    FOREACH(it, str) {
        cur = kmp[cur][*it - '0'];
        if(cur == L) {
            ++ans;
        }
    }
    if(pos) *pos = cur;
    return ans;
}

void fill_memo(int n, const string &str, const vector<vector<int> > &kmp) {
    memo[n] = kmp_match_count(str, kmp);
    visited[n] = true;
}

void build_presuf(int cur, const int L, const int N) {
    // prefix
    const int needP = L - prefix[cur-1].size();
    prefix[cur] = prefix[cur-1];
    if(needP > 0) prefix[cur] += prefix[cur-2].substr(0, needP);

    // suffix
    const int needS = L - prefix[cur-2].size();
    if(needS > 0) suffix[cur] = suffix[cur-1].substr(max(0, (int)suffix[cur-1].size()-needS));
    suffix[cur] += suffix[cur-2];

    if(cur+1 <= N) build_presuf(cur+1, L, N);
}

ULL calc(int n, const vector<vector<int> > &kmp) {
    if(visited[n]) return memo[n];

    ULL ans = calc(n-1, kmp) + calc(n-2, kmp);
    //const string mid = suffix[n-1] + prefix[n-2];
    int pos = 0;
    if(suffix[n-1].size() + prefix[n-2].size() >= kmp.size()-1) {
        ULL tmp = kmp_match_count(suffix[n-1], kmp, &pos);
        assert(tmp == 0);
        ans += kmp_match_count(prefix[n-2], kmp, &pos);
    }
    visited[n] = true;
    return memo[n] = ans;
}

ULL len_1(const int N, const char c) {
    if(N == 0) {
        return c == '0';
    } else if(N == 1) {
        return c == '1';
    } else {
        ULL a = 1, b = 1;
        TIMES(_, N-2) {
            ULL tmp = a+b;
            a = b;
            b = tmp;
        }
        return (c == '0') ? a : b;
    }
}

ULL solve(const int N) {
    string pattern;
    cin >> pattern;
    const int L = pattern.size();

    // Corner case
    if(L == 1) {
        return len_1(N, pattern[0]);
    }

    // Build KMP
    vector<vector<int> > kmp(L+1, vector<int>(2, 0));
    int shadow = 0;
    TIMES(i, L) {
        const int correct = pattern[i]-'0';
        kmp[i][correct] = i+1;
        if(i > 0) {
            TIMES(j, 2) {
                if(j == correct) continue;
                kmp[i][j] = kmp[shadow][j];
            }
            shadow = kmp[shadow][correct];
        }
    }
    TIMES(j, 2) {
        kmp[L][j] = kmp[shadow][j];
    }

    fill_n(memo, 200, 0);
    fill_n(visited, 200, false);

    if(N <= SHORT_N) {
        return kmp_match_count(fib[N], kmp);
    }

    // Fill memo
    fill_memo(SHORT_N-1, fib[SHORT_N-1], kmp);
    fill_memo(SHORT_N, fib[SHORT_N], kmp);

    // Build prefix and suffix list
    prefix.clear();
    suffix.clear();
    prefix.resize(101);
    suffix.resize(101);
    prefix[0] = suffix[0] = "0";
    prefix[1] = suffix[1] = "1";
    build_presuf(2, L-1, N);
    /*
    TIMES(i, 20) {
        cout << prefix[i] << ' ' << suffix[i] << endl;
    }
    */

    // Recursive
    return calc(N, kmp);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    int cn = 1;
    init();
    while(cin >> N) {
        ULL result = solve(N);
        cout << "Case " << cn << ": " << result << endl;
        ++cn;
    }
    return 0;
}
