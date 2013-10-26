//Name: Panda's Birthday Present
//Level: 4
//Category: 数学,Math,確率
//Note:

/**
 * 出たスコアから、元の色分けを推測することを考える。
 * 赤の個数の組み合わせをa(7^4通り), 出たスコアをb(5^2通り)とすると、ベイズの定理より
 *   P(A=a|B=b) = P(B=b|A=a)P(A=a) / P(B=b)
 * が成立する。
 * ここで、
 * ・P(B=b|A=a)は実際に色分けを全部試すことで計算可能
 * ・P(A=a)は組み合わせaに対し、各サイコロがその個数の赤い面をもつ確率を掛けることで計算可能
 * ・P(B=b)はP(B=b|A=a)をすべてのAについて合計することで計算可能
 * したがって、P(A=a|B=b)も計算可能である。
 * 求める期待値は、Sをスコアとして
 *   ΣP(A=a|B=b)ΣxP(S=x|A=a)
 * で求められる。
 *
 * サイコロの個数が4個、面の数が6面なので、(6+1)^4 = 2401通りの組み合わせがある。
 * 各パターンについてP(B=b|A=a)を計算するため、さらに4*4 = 16回のループを乗じることとなり、
 * 前処理には2401*16 = 38416回のループが必要となる。
 */
#include <cstdio>

using namespace std;

const int PATTERNS = 7*7*7*7;
const int ALL = 1<<24;
const int comb6[7] = {1, 6, 15, 20, 15, 6, 1};
double expected[PATTERNS];
double prob[PATTERNS][5];
double net_prob[25];
double pa[PATTERNS];

int main() {
    for(int pat = 0; pat < PATTERNS; ++pat) {
        int tmp = pat;
        prob[pat][0] = 1;
        pa[pat] = 1.0 / ALL;
        for(int i = 0; i < 4; ++i) {
            const int reds = tmp % 7;
            pa[pat] *= comb6[reds];
            const double p = reds / 6.0;
            for(int s = i+1; s >= 1; --s) {
                prob[pat][s] = (1-p) * prob[pat][s] + p * prob[pat][s-1];
            }
            prob[pat][0] = (1-p) * prob[pat][0];
            tmp /= 7;
        }
        for(int i = 0; i <= 4; ++i) {
            expected[pat] += prob[pat][i] * i;
            for(int j = 0; j <= 4; ++j) {
                net_prob[i*5+j] += prob[pat][i] * prob[pat][j] * pa[pat];
            }
        }
    }
    int T;
    scanf("%d", &T);
    while(T--) {
        int a, b;
        scanf("%d %d", &a, &b);
        double pb = net_prob[a*5+b];
        double res = 0;
        double pp = 0;
        for(int pat = 0; pat < PATTERNS; ++pat) {
            double p = prob[pat][a] * prob[pat][b] * pa[pat] / pb;
            pp += p;
            res += expected[pat] * p;
        }
        //printf("%f\n", pp);
        printf("%.3f\n", res);
    }
    return 0;
}
