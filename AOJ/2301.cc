#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

bool inRange(double l, double c, double r) {
    return l <= c && c <= r;
}

double dfs(int K, double R, double L, double P, double E, double T, double prob) {
    double center = (R+L) / 2;
    double ans = 0;

    if(inRange(T-E, R, T+E) && inRange(T-E, L, T+E)) return prob;
    if(T+E < R || T-E > L) return 0;
    if(K == 0) {
        if(inRange(T-E, center, T+E)) return prob;
        return 0;
    }
    
    if(center < T) {
        return dfs(K-1, center, L, P, E, T, prob*(1-P)) + dfs(K-1, R, center, P, E, T, prob*P);
    }
    else {
        return dfs(K-1, center, L, P, E, T, prob*P) + dfs(K-1, R, center, P, E, T, prob*(1-P));
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    int K, R, L;
    cin >> K >> R >> L;
    double P, E, T;
    cin >> P >> E >> T;

    printf("%.6f\n", dfs(K, R, L, P, E, T, 1.0));

    return 0;
}
