#include <iostream>
#include <algorithm>

using namespace std;

struct Fraction {
    int numer, denom;

    Fraction(int n, int d) : numer(n), denom(d) { normalize(); }

    void normalize() {
        int gcd = __gcd(numer, denom);
        numer /= gcd;
        denom /= gcd;
    }

    double value() const {
        return (double)numer / denom;
    }

    Fraction& operator -=(const Fraction &other) {
        int gcd = __gcd(denom, other.denom);
        int lcm = denom*other.denom / gcd;
        
        numer *= (lcm/denom);
        numer -= other.numer*lcm/other.denom;
        denom = lcm;
        normalize();

        return *this;
    }

    bool operator < (const Fraction &other) const {
        return (long long)numer*other.denom < (long long)other.numer*denom;
    }

    bool operator == (const Fraction &other) const {
        return numer == other.numer && denom == other.denom;
    }

    bool operator <= (const Fraction &other) const {
        return *this == other || *this < other;
    }
};

Fraction operator - (const Fraction &f1, const Fraction &f2) {
    Fraction res = f1;
    res -= f2;
    return res;
}

ostream& operator <<(ostream &os, const Fraction &f) {
    os << f.numer << "/" << f.denom;
    return os;
}

int N, A;

int dfs(const Fraction &frac, int a, int n, int m) {
    if(a > A) return 0;
    if(n == N) {
        //cout << frac << ' ' << a << ' ' << n << endl;
        if(frac.numer == 1 && frac.denom >= m && (long long)a*frac.denom <= A) return 1;
        return 0;
    }

    //cout << frac << ' ' << a << ' ' << n <<  ' ' << m << endl;
    int cnt = 0;
    if(frac.numer == 1 && frac.denom >= m && (long long)frac.denom*a <= A) ++cnt;

    for(int i = m; frac <= Fraction(N-n+1, i); ++i) {
        if((long long)a*i > A) break;
        Fraction next = frac - Fraction(1, i);
        if(next.value() < 0) continue;
        if(next.numer == 0) continue;
        //cout << "Select " << Fraction(1,i) << endl;;
        cnt += dfs(next, a*i, n+1, i);
    }
    return cnt;
}

int main() {
    while(true) {
        int p, q;
        cin >> p >> q >> A >> N;
        if(!p && !q && !A && !N) break;

        cout << dfs(Fraction(p, q), 1, 1, 1) << endl;
    }

    return 0;
}
