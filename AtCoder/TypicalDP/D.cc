//Name: サイコロ
//Level: 3
//Category: DP,動的計画法
//Note: Typical DP Contest D

/*
 * サイコロの目がもつ素因数は2, 3, 5のみ。
 * それぞれ個数の上限は200, 100, 100個なので、これを状態として確率をDPする。
 *
 * オーダーはO(N^4)。
 */
#include <iostream>
#include <cstdio>

using namespace std;

// dp[turn][twos][threes][fives]
double dp[2][201][101][101];
int DICE[6][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {2, 0, 0},
    {0, 0, 1},
    {1, 1, 0}
};

int main() {
    cin.tie(0);
    int N;
    unsigned long long D;
    cin >> N >> D;
    int twos = 0, threes = 0, fives = 0;
    while(D % 2 == 0) {
        D /= 2;
        ++twos;
    }
    while(D % 3 == 0) {
        D /= 3;
        ++threes;
    }
    while(D % 5 == 0) {
        D /= 5;
        ++fives;
    }
    if(D != 1) {
        puts("0");
        return 0;
    }

    for(int dice = 0; dice < 6; ++dice) {
        dp[1][DICE[dice][0]][DICE[dice][1]][DICE[dice][2]] = 1.0 / 6.0;
    }
    for(int i = 1; i < N; ++i) {
        const int cur = i % 2;
        const int next = 1 - cur;
        for(int two = 0; two < 201; ++two) {
            for(int three = 0; three < 101; ++three) {
                for(int five = 0; five < 101; ++five) {
                    dp[next][two][three][five] = 0;
                }
            }
        }
        for(int two = 0; two < 201; ++two) {
            for(int three = 0; three < 101; ++three) {
                for(int five = 0; five < 101; ++five) {
                    if(dp[cur][two][three][five] == 0) continue;
                    for(int dice = 0; dice < 6; ++dice) {
                        const int n_two = two + DICE[dice][0];
                        const int n_three = three + DICE[dice][1];
                        const int n_five = five + DICE[dice][2];
                        if(n_two < 201 && n_three < 101 && n_five < 101)
                            dp[next][n_two][n_three][n_five] += dp[cur][two][three][five] / 6;
                    }
                }
            }
        }
    }
    double ans = 0;
    for(int two = twos; two < 201; ++two) {
        for(int three = threes; three < 101; ++three) {
            for(int five = fives; five < 101; ++five) {
                ans += dp[N%2][two][three][five];
            }
        }
    }
    printf("%.7f\n", ans);
    return 0;
}
