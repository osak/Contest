//Name: Match Throwing Game
//Level: 4
//Category: 数学,Math
//Note:

/**
 * ビュフォンの針。
 *
 * マッチ棒の中心と、近いほうの直線との距離をx, 角度をθとすると、交差するための条件は
 *   (L/2)sinθ ≧ x
 * となる。
 * ここで、マッチ棒の中心を基準点に取っているため、近い方の直線だけを考えて良いことに注意。
 * このとき、xは[0, 1/2], θは[0, π/2]の間で等確率に分布する。
 * したがって、二重積分
 *   π/4∫[θ=[0, π/2]] ∫[x=[0, min(L/2sinθ, 1/2)]] dxdθ
 * を計算することで、マッチ棒を1本投げた時の確率が求められる。
 *
 * 求めなければならないのは、尤度を最大とするPなので、二項係数を用いて確率を計算する。
 * 単に(1000×確率)では不十分である。
 *
 * オーダーは前処理にO(N^2)、計算にO(N)。
 * ただしN=1000。
 */
#include <cstdio>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);
double cb[1001][1001];

int main() {
    cb[0][0] = 1;
    for(int n = 1; n <= 1000; ++n) {
        for(int k = 0; k <= n; ++k) {
            cb[n][k] = cb[n-1][k];
            if(k > 0) cb[n][k] += cb[n-1][k-1];
        }
    }
    double L;
    while(scanf("%lf", &L) != EOF) {
        double prob = 0;
        if(L <= 1) {
            prob = 2*L/PI;
        } else {
            const double a = asin(1 / L);
            const double l = L-sqrt(L*L-1);
            const double r = PI/2 - a;
            prob = 2 * (l + r) / PI;
        }
        double maxp = 0;
        int ans = 0;
        for(int i = 0; i <= 1000; ++i) {
            double p = pow(prob, i) * pow(1-prob, 1000-i) * cb[1000][i];
            if(p > maxp) {
                ans = i;
                maxp = p;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
