//Name: DNA
//Level: 4
//Category: メモ化探索,動的計画法,DP
//Note:

/*
 * 非終端記号が他の非終端記号を含むときは，登場順で下のものしか含まないためこの形式文法は有限長の文字列しか生成しない．
 * また，遷移先の記号は決定的なので深さ優先探索で完全に展開できる．
 *
 * 非終端記号を展開して終端記号のみにしたら，ATGCをどのように割り当てるかという問題になるので割り当ての順番は関係ないことが分かる．
 * したがって状態となるのはA,T,G,Cそれぞれの残り個数のみ．
 * これをメモ化再帰で数え上げればよい．
 * ただし，非終端記号の展開時に非常に長い記号列を生成させることも可能なので，展開後の記号列がNa+Ng+Nt+Ncを超えた時点で展開を打ち切る必要がある．
 *
 * オーダーは O(Na*Ng*Nt*Nc)．
 * 実際には枝数4がかかるが，それでも十分に間に合う．
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

const int MOD = 1000000007;

int memo[51][51][51][51];
unordered_map<string, vector<string> > syms;
int LIMIT;

void expand(const string &name, vector<string> &out) {
    const vector<string> &v = syms[name];
    for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it) {
        const string &part = *it;
        if(isupper(part[0])) {
            out.push_back(part);
        } else {
            expand(part, out);
        }
        if(out.size() > LIMIT) throw "Over limit";
    }
}

int dfs(int A, int T, int G, int C, const vector<string> &v, int pos) {
    int &res = memo[A][T][G][C];
    if(res != -1) return res;
    if(pos == v.size()) {
        if(A+T+G+C == 0) return 1;
        else return 0;
    }
    const string &part = v[pos];
    res = 0;
    for(string::const_iterator it2 = part.begin(); it2 != part.end(); ++it2) {
        switch(*it2) {
            case 'A':
                if(A > 0) res += dfs(A-1, T, G, C, v, pos+1);
                break;
            case 'T':
                if(T > 0) res += dfs(A, T-1, G, C, v, pos+1);
                break;
            case 'G':
                if(G > 0) res += dfs(A, T, G-1, C, v, pos+1);
                break;
            case 'C':
                if(C > 0) res += dfs(A, T, G, C-1, v, pos+1);
                break;
        }
        res %= MOD;
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int A, T, G, C;
    cin >> A >> T >> G >> C;
    int M;
    cin >> M;
    cin.ignore();
    string toplevel;
    for(int i = 0; i < M; ++i) {
        string line;
        getline(cin, line);

        istringstream is(line);
        string name;
        is >> name;
        name.erase(name.end()-1);
        vector<string> parts;
        while(!is.eof()) {
            string token;
            is >> token;
            if(token[0] == '[') {
                parts.push_back(token.substr(1, (int)token.size()-2));
            } else {
                parts.push_back(token);
            }
        }
        syms[name] = parts;
        if(i == 0) toplevel = name;
    }
    for(int i = 0; i < 51; ++i)
        for(int j = 0; j < 51; ++j)
            for(int k = 0; k < 51; ++k)
                for(int l = 0; l < 51; ++l)
                    memo[i][j][k][l] = -1;
    try {
        vector<string> expanded;
        LIMIT = A+T+G+C;
        expand(toplevel, expanded);
        cout << dfs(A, T, G, C, expanded, 0) << endl;
    } catch(const char *err) {
        cout << 0 << endl;
    }
    return 0;
}
