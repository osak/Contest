#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <climits>
#include <map>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

struct Stamp {
    int color2idx(char c) const {
        switch(c) {
            case 'R': return 0;
            case 'G': return 1;
            case 'B': return 2;
        }
        return -1;
    }

    int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
        const int N = desiredColor.size();
        const int INF = 100000*100;
        int ans = INF;
        for(int L = 1; L <= N; ++L) {
            vector<vector<int> > dp(N, vector<int>(3, INF));
            for(int i = L-1; i < N; ++i) {
                // Check if valid stamping
                char color = '*';
                bool ok = true;
                for(int j = 0; j < L; ++j) {
                    if(desiredColor[i-j] != '*') {
                        if(color != '*' && color != desiredColor[i-j]) {
                            ok = false;
                            break;
                        }
                        color = desiredColor[i-j];
                    }
                }
                if(!ok) continue;
                // non-wrapping put
                int prev_cost = INF;
                if(i-L >= 0) {
                    for(int j = 0; j < 3; ++j) {
                        prev_cost = min(prev_cost, dp[i-L][j]);
                    }
                } else {
                    prev_cost = 0;
                }
                for(int j = 0; j < 3; ++j) {
                    if(color != '*' && color2idx(color) != j) continue;
                    dp[i][j] = prev_cost + pushCost;
                }
                // wrapping put
                for(int j = 0; j < 3; ++j) {
                    if(color != '*' && color2idx(color) != j) continue;
                    for(int k = i-L+1; k < i; ++k) {
                        dp[i][j] = min(dp[i][j], dp[k][j] + pushCost);
                    }
                }
            }
            for(int color = 0; color < 3; ++color) {
                ans = min(ans, dp[N-1][color]+stampCost*L);
            }
            //cout << L << ' ' << ans << endl;
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RRGGBB"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(0, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "R**GB*"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(1, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "BRRB"; int Arg1 = 2; int Arg2 = 7; int Arg3 = 30; verify_case(2, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "R*RR*GG"; int Arg1 = 10; int Arg2 = 58; int Arg3 = 204; verify_case(3, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "*B**B**B*BB*G*BBB**B**B*"; int Arg1 = 5; int Arg2 = 2; int Arg3 = 33; verify_case(4, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "*R*RG*G*GR*RGG*G*GGR***RR*GG"; int Arg1 = 7; int Arg2 = 1; int Arg3 = 30; verify_case(5, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	Stamp __test;
	__test.run_test(-1);
}
// END CUT HERE
