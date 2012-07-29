#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const string ATOMS = "H  He  Li  Be      B   C   N   O   F   Ne Na  Mg      Al  Si  P   S   Cl  Ar K   Ca      Sc  Ti  V   Cr  Mn  Fe  Co  Ni  Cu  Zn  Ga  Ge  As  Se  Br  Kr Rb  Sr      Y   Zr  Nb  Mo  Tc  Ru  Rh  Pd  Ag  Cd  In  Sn  Sb  Te  I   Xe Cs  Ba      La  Ce  Pr  Nd  Pm  Sm  Eu  Gd  Tb  Dy  Ho  Er  Tm  Yb    Lu  Hf  Ta  W   Re  Os  Ir  Pt  Au  Hg  Tl  Pb  Bi  Po  At  Rn Fr  Ra Ac  Th  Pa  U   Np  Pu  Am  Cm  Bk  Cf  Es  Fm  Md  No";

map<string, int> atom2num;
vector<string> num2atom(200);
vector<int> srcs;
vector<int> dests;

void dfs(const vector<vector<int> > &pats, vector<int> &cur, int curpat, int idx) {
    if(idx == pats.size()) {
        cout << "YES" << endl;
        for(int i = 0; i < cur.size(); ++i) {
            int pat = cur[i];
            bool first = true;
            for(int j = 0; j < srcs.size(); ++j) {
                if(pat & (1<<j)) {
                    if(!first) cout << "+";
                    cout << num2atom[srcs[j]];
                    first = false;
                }
            }
            cout << "->" << num2atom[dests[i]] << endl;
        }
        exit(0);
    }
    for(int i = 0; i < pats[idx].size(); ++i) {
        if((curpat & pats[idx][i]) == 0) {
            cur[idx] = pats[idx][i];
            dfs(pats, cur, curpat|pats[idx][i], idx+1);
        }
    }
}

int main() {
    istringstream is(ATOMS);
    int idx = 1;
    while(!is.eof()) {
        string a;
        is >> a;
        atom2num[a] = idx;
        num2atom[idx] = a;
        ++idx;
    }

    int N, K;
    cin >> N >> K;

    for(int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        srcs.push_back(atom2num[s]);
    }
    for(int i = 0; i < K; ++i) {
        string s;
        cin >> s;
        dests.push_back(atom2num[s]);
    }

    vector<vector<int> > pats;
    for(int i = 0; i < K; ++i) {
        int dest = dests[i];
        vector<vector<int> > dp(dest+1);
        dp[0].push_back(0);

        for(int j = 1; j <= dest; ++j) {
            for(int k = 0; k < srcs.size(); ++k) {
                int idx = j - srcs[k];
                if(idx < 0) continue;
                for(int l = 0; l < dp[idx].size(); ++l) {
                    int pat = dp[idx][l] | (1<<k);
                    if(pat != dp[idx][l] && find(dp[j].begin(), dp[j].end(), pat) == dp[j].end()) dp[j].push_back(pat);
                }
            }
        }
        pats.push_back(dp[dest]);
    }

    vector<int> cur(dests.size());
    dfs(pats, cur, 0, 0);

    cout << "NO" << endl;
    return 0;
}
