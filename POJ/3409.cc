//Name: Broken line
//Level: 3
//Category: グラフ,Graph,文字列,連結性判定
//Note: Leading zeroがある。また、折れ線は複数存在することがある。

/**
 * 点の次数がすべて偶数になっていればよい。
 * 座標は文字列で扱うが、Leading zeroの存在に注意。
 * また、折れ線が複数存在することもあるので、全体が連結であるかも判定する必要がある。
 * (問題文にはa broken lineと書いてあるので、入力がおかしい気がする)
 *
 * オーダーはO(SN log N)。
 * ただし、Sは座標を表す文字列の最大長。
 */
#include <cstdio>
#include <map>
#include <utility>
#include <cctype>
#include <string>

using namespace std;

typedef unsigned long long ULL;

string read_num() {
    static char buf[300];
    scanf(" %s", buf);
    char *p = buf;
    while(*p && *p == '0') ++p;
    if(!*p) --p;
    return string(p);
}

int deg[3000*4];
int roots[3000*4];

int getroot(int x) {
    if(roots[x] == x) return x;
    return roots[x] = getroot(roots[x]);
}

int main() {
    int K;
    scanf("%d", &K);
    map<pair<string,string>,int> dict;
    for(int i = 0; i < 3000*4; ++i) {
        roots[i] = i;
    }
    int idx = 0;
    while(K--) {
        string x1, y1, x2, y2;
        x1 = read_num();
        y1 = read_num();
        x2 = read_num();
        y2 = read_num();
        const pair<string,string> p1(x1, y1), p2(x2, y2);
        if(dict.count(p1) == 0) dict[p1] = idx++;
        if(dict.count(p2) == 0) dict[p2] = idx++;
        deg[dict[p1]]++;
        deg[dict[p2]]++;
        roots[getroot(dict[p1])] = getroot(dict[p2]);
    }
    bool closed = true;
    for(int i = 0; i < idx; ++i) {
        if(deg[i] % 2 == 1 || getroot(i) != getroot(0)) {
            closed = false;
            break;
        }
    }
    puts(closed ? "1" : "0");
    return 0;
}
