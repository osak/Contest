//Name: Stammering Aliens
//Level: 4
//Category: 文字列,String,Suffix Array
//Note:

/**
 * 「文字列Sのi文字目から始まる長さlの部分文字列の出現回数を求める」という問題は、Suffix Array上で考えると、
 * i文字目を先頭とするsuffixが出現する箇所の前後で、LCPの長さがl以上で連続している範囲の大きさを求める問題になる。
 * ここで、LCPとはLongest Common Prefixの略である。
 *
 * この問題では、上記の問題に加えて「出現回数がM回以上のもののうち、最長の部分文字列を求める」という条件が付いている。
 * これは、Suffix Array上で隣り合ったSuffixのLCPを長方形と見ると「縦幅がM以上で、横幅がもっとも長いものを求める」という問題である。
 * したがって、スタックを用いたO(N)解法が可能である。
 * (参考: POJ3776, AOJ0116等)
 * 最も右の出現位置は、関与したSuffixのインデックスのうち、最大のものを状態として追加でもてば良い。
 *
 * オーダーはO(N log N)。
 * ただし、これはSuffix Array構築のオーダーであり、LCPの算出と本質部分はともにO(N)である。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

int N;
// Suffix Array {{{
struct SAComp {
    const int *grp;
    int h;
    SAComp(const int *grp, int h) : grp(grp), h(h) {}

    bool operator ()(int a, int b) const {
        int va = grp[a];
        int vb = grp[b];
        int vah = a+h < N ? grp[a+h] : INT_MIN;
        int vbh = b+h < N ? grp[b+h] : INT_MIN;
        return (va == vb) ? vah < vbh : va < vb;
    }
};

// Suffix Arrayを構築する．
// A Fast Algorithm for Making Suffix Arrays and for Burrows-Wheeler Transformation
// (Kunihiko Sadakane, 1998)
// の実装．ただし，以下の変更を加えている．
// ・同じグループごとにソートするのではなく，Suffix Array全体を一度にソートする．
// saの中身は開始インデックス．
//
// 計算量O(N (log N)^2)
int _group[40000], _group2[40000];
void suffix_array(const char *str, int *sa) {
    int *group = _group, *next = _group2;
    for(int i = 0; i < N; ++i) {
        sa[i] = i;
        group[i] = str[i];
    }
    {
        SAComp cmp(group, 0);
        sort(sa, sa+N, cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        swap(group, next);
    }

    for(int h = 1; h < N && group[N-1] != N-1; h <<= 1) {
        //Generate <_{2*h} ordered array from <_{h} ordered array
        //この中身はcmpのコンストラクタ引数以外，上のブロックと同じ．
        SAComp cmp(group, h);
        sort(sa, sa+N, cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        swap(group, next);
    }
}

// LCPを計算する。
// O(N)
int inv[40000];
void lcp(const char *str, const int *sa, int *lcpa) {
    for(int i = 0; i < N; ++i) {
        inv[sa[i]] = i;
    }
    int h = 0;
    for(int i = 0; i < N; ++i) {
        const int next = inv[i]+1 < N ? sa[inv[i]+1] : -1;
        if(next == -1) {
            h = 0;
            lcpa[inv[i]] = -1;
        } else {
            if(h > 0) --h;
            const int lim = min(N-i, N-next);
            for(int j = h; j < lim; ++j) {
                if(str[i+j] != str[next+j]) break;
                ++h;
            }
            lcpa[inv[i]] = h;
        }
    }
}

struct Tag {
    int maxp, start, last, len;
    Tag() {}
    Tag(int m, int s, int l, int len) : maxp(m), start(s), last(l), len(len) {}
};

vector<Tag> stk;
bool solve() {
    int M;
    scanf("%d ", &M);
    if(!M) return false;

    static char str[40010];
    static int sa[40000], lcpa[40000];
    fgets(str, 40010, stdin);
    N = strlen(str);
    while(!islower(str[N-1])) {
        str[N-1] = '\0';
        --N;
    }
    if(M == 1) {
        cout << N << ' ' << 0 << endl;
        return true;
    }
    suffix_array(str, sa);
    lcp(str, sa, lcpa);
    /*
    for(int i = 0; i < N; ++i) {
        cout << str.substr(sa[i]) << ' ' << lcpa[i] << endl;
    }
    */

    int ans_len = 0, ans_pos = 0;
    stk.clear();
    for(int i = 0; i < N; ++i) {
        //cout << str+sa[i] << ' ' << lcpa[i] << endl;
        const int l = lcpa[i];
        int cnt = 1;
        int s = i;
        int pos = sa[i];
        while(!stk.empty() && stk.back().len >= l) {
            pos = max(pos, stk.back().maxp);
            cnt += stk.back().last - stk.back().start + 1;
            s = stk.back().start;
            int curl = stk.back().len;
            //cout << curl << ' ' << cnt << ' ' << pos << endl;
            stk.pop_back();
            if(curl >= ans_len && cnt >= M) {
                if(ans_len == curl) {
                    ans_pos = max(ans_pos, pos);
                } else {
                    ans_len = curl;
                    ans_pos = pos;
                }
            }
        }
        //cout << "push " << pos << ' ' << s << ' ' << i << ' ' << l << endl;
        stk.push_back(Tag(pos, s, i, l));
    }

    if(ans_len == 0) {
        cout << "none" << endl;
    } else {
        cout << ans_len << ' ' << ans_pos << endl;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(solve()) ;
    return 0;
}
