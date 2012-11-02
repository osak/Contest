//Name: So you want to be a 2n-aire?
//Level: 4
//Category: 数学
//Note:

/*
 * 途中でやめるパターンを考える必要があるので，f(n,a) := f(残り回数, 賞金)の値を考える．
 * ここで止めたときに得られる賞金は a．
 * 問題に答えたとき，答えられる確率をpとすると賞金の期待値は p*f(n-1,2*a)．
 * 止めるか答えるかの判断は，a と p*f(n-1,2*a) の値を比べて大きいほうを取ればよい．
 * pは[T,1]の中からuniformに選ばれるので，
 *   1
 * ∫  max(a, p*f(n-1, 2*a)) dp
 *   t
 * ここで f(n-1, 2*a) の値は固定値であることを考えると，pが単調に増加するとき
 * p*f(n-1,2*a) も単調増加である．
 * したがって p = a/f(n-1,2*a) で max の選ぶ値が切り替わることがわかる．
 * あとはこれらの積分を別々に計算すればよい．
 *
 * 参考：http://gt-mac.blog.163.com/blog/static/13925842620101156485731/
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

double calc(int n, int prize, double T) {
    if(n == 0) return prize;
    double next_exp = calc(n-1, 2*prize, T);
    double p = prize / next_exp;
    if(p < T) return next_exp*(1-T*T)/(1-T)/2;
    else return ((p-T)*prize + (1-p*p)*next_exp/2) / (1-T);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int N;
        double T;
        cin >> N >> T;
        if(!N) break;
        double ans = 1;
        if(T == 1.0) {
            ans = pow(2, N);
        } else {
            ans = calc(N, 1, T);
        }
        printf("%.3f\n", ans);
    }
    return 0;
}
