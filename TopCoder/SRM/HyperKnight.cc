/*
 * ナイトの移動先が盤面にはみ出るかどうかが変わるポイントは，行と列それぞれに高々5箇所しかない．
 * したがって変わり目でどのような状態になっているかを確認すると次の変わり目までは有効な動きの個数は変化しないので，区間の長さの積でマス数が出る．
 * a, bに対して盤面が小さすぎると面倒なことになりそうだが，制約から8方向に動けるマスが必ず1つは存在するのであまり考えなくてよい．
 *
 * オーダーは O(1)．
 */
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

struct Rect {
    int l, t, r, b; //all inclusive
    Rect() : l(0), t(0), r(1000000000), b(1000000000) {}
    Rect(int l, int t, int r, int b) : l(l), t(t), r(r), b(b) {}
};
struct HyperKnight {
    long long countCells(int a, int b, int R, int C, int k) {
        if(a < b) swap(a, b);
        vector<int> event_r;
        vector<int> event_c;
        event_r.push_back(0); event_r.push_back(b); event_r.push_back(a); event_r.push_back(R-a); event_r.push_back(R-b); event_r.push_back(R);
        event_c = event_r;
        event_c[3] = C-a;
        event_c[4] = C-b;
        event_c[5] = C;

        long long ans = 0;
        for(int ridx = 0; ridx < (int)event_r.size()-1; ++ridx) {
            for(int cidx = 0; cidx < (int)event_c.size()-1; ++cidx) {
                int cnt = 0;
                for(int dir = 0; dir < 8; ++dir) {
                    int pat = dir % 4;
                    int dr = (pat>=2) ? a : -a;
                    int dc = (pat%2) ? b : -b;
                    if(dir >= 4) swap(dr, dc);
                    const int r = event_r[ridx] + dr;
                    const int c = event_c[cidx] + dc;
                    if(0 <= r && r < R && 0 <= c && c < C) ++cnt;
                }
                if(cnt == k) {
                    //cout << ridx << ' ' << cidx << endl;
                    ans += static_cast<long long>(event_r[ridx+1]-event_r[ridx]) * (event_c[cidx+1]-event_c[cidx]);
                }
            }
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 8; int Arg3 = 8; int Arg4 = 4; long long Arg5 = 20LL; verify_case(0, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 8; int Arg3 = 8; int Arg4 = 2; long long Arg5 = 16LL; verify_case(1, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 3; int Arg2 = 7; int Arg3 = 11; int Arg4 = 0; long long Arg5 = 0LL; verify_case(2, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 10; int Arg3 = 20; int Arg4 = 8; long long Arg5 = 56LL; verify_case(3, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 4; int Arg2 = 100; int Arg3 = 10; int Arg4 = 6; long long Arg5 = 564LL; verify_case(4, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 1000000000; int Arg3 = 1000000000; int Arg4 = 8; long long Arg5 = 999999988000000036LL; verify_case(5, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	HyperKnight __test;
	__test.run_test(-1);
}
// END CUT HERE
