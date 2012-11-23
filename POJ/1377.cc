//Name: Good Approximation Problem
//Level: 3
//Category: 分数
//Note:

/*
 * |p/q - y/x| を最小化することは |px/q - y| の最小化と等しい．
 * このとき，y は floor(px/q) か floor(px/q)+1 のどちらかであるから，両方試して小さいほうを採用する．
 * あとは x を 1 から順に見ていき，最小の差が更新されたら解を1増やせばよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int gcd(long long a, long long b) {
    if(a < b) swap(a, b);
    while(b != 0) {
        long long tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

struct Fraction {
    long long numer, denom;
    Fraction() {}
    Fraction(int n, int d) : numer(n), denom(d) { normalize(); }

    void normalize() {
        if(denom < 0) {
            denom = -denom;
            numer = -numer;
        }
        const long long g = gcd(llabs(numer), llabs(denom));
        numer /= g;
        denom /= g;
    }

    bool operator <(const Fraction &f) const {
        return numer*f.denom < f.numer*denom;
    }
};

// Assume both a and b are positive
Fraction operator - (const Fraction &a, const Fraction &b) {
    long long denom = a.denom*b.denom / gcd(a.denom, b.denom);
    long long numer = a.numer * (denom/a.denom) - b.numer * (denom/b.denom);
    return Fraction(numer, denom);
}

Fraction abs(const Fraction &a) {
    return Fraction(llabs(a.numer), llabs(a.denom));
}

ostream& operator <<(ostream &o, const Fraction &f) {
    return o << f.numer << '/' << f.denom;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    while(N--) {
        Fraction alpha;
        {
            cin >> alpha.numer >> alpha.denom;
        }
        int ans = 0;
        Fraction best(10000, 1);
        for(int x = 1; x <= alpha.denom; ++x) {
            Fraction f(alpha.numer*x, alpha.denom);
            long long y = f.numer / f.denom;
            //cout << y << endl;
            const Fraction d1 = abs(f - Fraction(y, 1));
            const Fraction d2 = abs(f - Fraction(y+1, 1));
            //cout << d1 << ' ' << d2 << endl;
            if(d1 < d2) {
                if(d1 < best) {
                    ++ans;
                    best = d1;
                    //cout << d1 << endl;
                }
            } else {
                if(d2 < best) {
                    ++ans;
                    best = d2;
                    //cout << d2 << endl;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
