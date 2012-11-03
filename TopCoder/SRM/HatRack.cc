/*
 * ノードを置く場所とそのときの親が分かれば，それより下の置き方のパターン数が定まるのでこれらの情報をメモして再帰で計算する．
 * 子の数で枝刈りを入れたけど状態数的に不要だった．
 *
 * 木なので辺数は高々3(定数)であるから，オーダーは O(N^3)．
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

struct HatRack {
    int calc_children(int node, int parent, const vector<vector<int> > &edges, vector<vector<int> > &children_count) {
        if(children_count[node][parent] == -1) {
            children_count[node][parent] = 1;
            for(vector<int>::const_iterator it = edges[node].begin(); it != edges[node].end(); ++it) {
                if(*it == parent) continue;
                children_count[node][parent] += calc_children(*it, node, edges, children_count);
            }
        }
        return children_count[node][parent];
    }

    int calc_required(int pos, int N, vector<int> &v) {
        if(pos > N) return 0;
        return v[pos] = calc_required(pos*2, N, v) + calc_required(pos*2+1, N, v) + 1;
    }

    long long memo[52][52][52];
    long long calc(int pos, int node, int parent, const vector<vector<int> > &edges, const vector<int> &required, const vector<vector<int> > &children_count) {
        if(memo[pos][node][parent] == -1) {
            memo[pos][node][parent] = 0;
            if(required[pos] != children_count[node][parent]) goto end;
            if(required[pos] == 1) {
                memo[pos][node][parent] = 1;
                goto end;
            }

            vector<int> children;
            for(vector<int>::const_iterator it = edges[node].begin(); it != edges[node].end(); ++it) {
                if(*it != parent) children.push_back(*it);
            }
            if(required[pos] == 2) { // only have one child
                if(children.size() != 1) goto end;
                memo[pos][node][parent] += calc(pos*2, children[0], node, edges, required, children_count);
            } else {
                if(children.size() != 2) goto end;
                memo[pos][node][parent] += calc(pos*2, children[0], node, edges, required, children_count) * calc(pos*2+1, children[1], node, edges, required, children_count);
                memo[pos][node][parent] += calc(pos*2, children[1], node, edges, required, children_count) * calc(pos*2+1, children[0], node, edges, required, children_count);
            }
        }
end:
        return memo[pos][node][parent];
    }

    long long countWays(vector <int> knob1, vector <int> knob2) {
        const int N = knob1.size()+1;
        vector<vector<int> > edges(N+1);
        for(int i = 0; i < N-1; ++i) {
            edges[knob1[i]].push_back(knob2[i]);
            edges[knob2[i]].push_back(knob1[i]);
        }
        // [node][parent]
        vector<vector<int> > children_count(N+1, vector<int>(N+1, -1));
        for(int node = 1; node <= N; ++node) {
            for(int pidx = 0; pidx < (int)edges[node].size(); ++pidx) {
                calc_children(node, edges[node][pidx], edges, children_count);
            }
            calc_children(node, 0, edges, children_count);
        }
        vector<int> required(N+1, 0);
        calc_required(1, N, required);
        //cout << print_array(required) << endl;

        fill_n((long long*)memo, sizeof(memo)/sizeof(long long), -1);
        long long ans = 0;
        for(int root = 1; root <= N; ++root) {
            ans += calc(1, root, 0, edges, required, children_count);
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {6,6,6,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,4,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,2,2,11,11,8,8,3,3,4,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,11,8,12,13,9,10,4,5,7,6,14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 16LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	HatRack __test;
	__test.run_test(-1);
}
// END CUT HERE
