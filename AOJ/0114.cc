//Name: Electro-Fly
//Level: 2
//Category: 数学
//Note: 

/**
 * それぞれの座標軸について周期を求め、最小公倍数を取ればよい。
 * 周期は a^k ≡ 1 (mod m) となる最小の k>1 だが、これはシミュレーションで求められる。
 *
 * オーダーは O(M)。
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int period(int a, int m) {
    vector<int> p(m, -1);
    int cur = a % m;
    for(int i = 0; i < m; ++i) {
        if(p[cur] >= 0) return i - p[cur];
        p[cur] = i;
        cur = (cur * a) % m;
    }
    assert(false);
}

template<typename T>
T gcd(T a, T b) {
    if(a < b) swap(a, b);
    while(b > 0) {
        const T tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a*b / gcd(a,b);
}

bool solve() {
    int a1, m1, a2, m2, a3, m3;
    cin >> a1 >> m1 >> a2 >> m2 >> a3 >> m3;
    if(!a1 && !m1 && !a2 && !m2 && !a3 && !m3) return false;

    const int p1 = period(a1, m1);
    const int p2 = period(a2, m2);
    const int p3 = period(a3, m3);
    cout << lcm(p1, lcm(p2, p3)) << endl;

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
