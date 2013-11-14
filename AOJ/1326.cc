//Name: Stylish
//Level: 2
//Category: 実装
//Note:

/**
 * インデント幅の組み合わせをすべて試す。
 * それぞれの組み合わせについて、まずお手本をインデントし、正しい結果になるかを調べる。
 * 正しい結果になるものについて、その組み合わせを使って問題のプログラムをインデントする。
 * どの組み合わせでも同じインデント深さになる行は、その深さで確定してよい。
 *
 * オーダーはO(I^3 (P+Q))。
 * ただしIはインデント幅の最大値(=20)。
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Line {
    int r, c, s;
    int indent;
    Line() : r(0), c(0), s(0), indent(0) {}
};

vector<Line> read_program(int N) {
    vector<Line> lines(N);
    for(int i = 0; i < N; ++i) {
        string str;
        getline(cin, str);
        bool top = true;
        for(char c : str) {
            if(top && c == '.') ++lines[i].indent;
            if(c != '.') top = false;
            if(c == '(') ++lines[i].r;
            else if(c == ')') --lines[i].r;
            else if(c == '{') ++lines[i].c;
            else if(c == '}') --lines[i].c;
            else if(c == '[') ++lines[i].s;
            else if(c == ']') --lines[i].s;
        }
    }
    return lines;
}

vector<int> do_indent(int r, int c, int s, const vector<Line> &lines) {
    static vector<int> res;
    res.clear();
    Line cur;
    res.push_back(0);
    for(const Line &l : lines) {
        cur.r += l.r;
        cur.c += l.c;
        cur.s += l.s;
        if((cur.r > 0 && r == -1)
            || (cur.c > 0 && c == -1)
            || (cur.s > 0 && s == -1))
        {
            res.push_back(-1);
        } else {
            res.push_back(cur.r*r + cur.c*c + cur.s*s);
        }
    }
    res.pop_back();
    return res;
}

bool solve() {
    int P, Q;
    cin >> P >> Q;
    if(!P && !Q) return false;
    cin.ignore();
    vector<Line> original = read_program(P);
    vector<Line> to_indent = read_program(Q);
    vector<int> ans;
    for(int r = 1; r <= 20; ++r) {
        for(int c = 1; c <= 20; ++c) {
            for(int s = 1; s <= 20; ++s) {
                vector<int> indents = do_indent(r, c, s, original);
                bool ok = true;
                for(int i = 0; i < P; ++i) {
                    if(original[i].indent != indents[i]) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    vector<int> indents = do_indent(r, c, s, to_indent);
                    if(ans.size() == 0) {
                        ans = indents;
                    } else {
                        for(int i = 0; i < Q; ++i) {
                            if(indents[i] != ans[i]) {
                                ans[i] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < Q; ++i) {
        if(i > 0) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
