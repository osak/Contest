#include <cstdio>//{{{
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <cassert>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <utility>
#include <algorithm>
#include <numeric>
#include <complex>
#include <functional>
#include <memory>
#include <sstream>
#include <cctype>//}}}
#define REP(i,b,n) for(int i=(int)(b);(i)<(int)(n);++(i))//{{{
#define rep(i,n) REP(i,0,n)
#define foreach(i,v) for(typeof(v.begin()) i=v.begin();i!=v.end();i++)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()//}}}
using namespace std;
static const int INF = 1<<25;
static const double EPS = 1e-5;
typedef long long ll;//{{{
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef pair<int,pii> pipii;//}}}


#define L first
#define R second

int n, q;
vector<pii> I, Q;
vector<map<int, int> > succ(1);
void pre(){
    vector<pair<int, int> > ps;
    rep(i, n){
        ps.pb(make_pair(I[i].R, i));
        ps.pb(make_pair(I[i].L, n+i));
    }
    sort(all(ps));
    int last = -1;
    for(int i = n+n-1; i >= 0; --i){
        int id = ps[i].second;
        if(id < n){
            succ[0][id] = last;
        }else{
            id -= n;
            if(last < 0 || I[last].R > I[id].R){
                last = id;
            }
        }
    }
    for(int i = 1; (1<<i) <= n; ++i){
        succ.pb(map<int, int>());
        rep(j, n) succ[i][j] = succ[i-1][succ[i-1][j]];
    }
}

void solve(pii in){
    int t = 0;
    rep(i, n){
        if(I[i].L <= in.L){
            if(t < 0 || I[t].R > I[i].R){
                t = i;
            }
        }
    }
    int res = 0;
    for(int i = succ.size()-1; i >= 0; --i){
        if(I[succ[i][t]].R <= in.R){
            t = succ[i][t];
            res += 1<<i;
        }
    }
    cout << res << endl;
}

int main(){
    cin >> n >> q;
    I.resize(n); Q.resize(q);
    rep(i, n) cin >> I[i].L >> I[i].R;
    rep(i, q) cin >> Q[i].L >> Q[i].R;
    pre();
    rep(i, q) solve(Q[i]);
    return 0;
}
/* vim:set foldmethod=marker commentstring=//%s : */
