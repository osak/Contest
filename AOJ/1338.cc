//Name: Clock Hands
//Level: 4
//Category: 数学,Math
//Note:

/**
 * 時計回りにみたとき、短針―秒針―長針のパターンか、長針―秒針―短針のパターンかを調べる。
 * 前者のとき、この向きで見て0.5∠短長より短針側に秒針がいるときは、方程式を計算することで解が求められる。
 * そうでない場合、いったん長針を追い越してから後者のパターンで計算する。
 * 後者の時も同様。
 *
 * オーダーは O(1)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) {
    if(a < b) swap(a, b);
    while(b != 0) {
        LL tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

LL lcm(LL a, LL b) {
    return a / gcd(a, b) * b;
}

struct Fraction {
    LL num, den;
    explicit Fraction(LL num) : num(num), den(1) { normalize(); }
    Fraction(LL num, LL den) : num(num), den(den) { normalize(); }

    Fraction& operator +=(const Fraction &f) {
        const LL newd = lcm(den, f.den);
        num *= newd / den;
        num += f.num * (newd / f.den);
        den = newd;
        normalize();
        return *this;
    }

    Fraction& operator -=(const Fraction &f) {
        const LL newd = lcm(den, f.den);
        num *= newd / den;
        num -= f.num * (newd / f.den);
        den = newd;
        normalize();
        return *this;
    }

    Fraction& operator *=(const Fraction &f) {
        num *= f.num;
        den *= f.den;
        normalize();
        return *this;
    }

    bool operator ==(const Fraction &f) const {
        return (num == 0 && f.num == 0) || (num == f.num && den == f.den);
    }

    bool operator <(const Fraction &f) const {
        return num * f.den < den * f.num;
    }

    bool operator >(const Fraction &f) const {
        return num * f.den > den * f.num;
    }

    bool operator <=(const Fraction &f) const {
        return *this < f || *this == f;
    }

    bool operator >=(const Fraction &f) const {
        return *this > f || *this == f;
    }

    void normalize() {
        LL g = abs(gcd(num, den));
        num /= g;
        den /= g;
        if(den < 0) {
            num = -num;
            den = -den;
        }
        if(num == 0) den = 1;
    }

    Fraction strict() const {
        return Fraction(num % den, den);
    }
};

Fraction operator +(const Fraction &f, const Fraction &g) {
    Fraction ret = f;
    ret += g;
    return ret;
}

Fraction operator -(const Fraction &f, const Fraction &g) {
    Fraction ret = f;
    ret -= g;
    return ret;
}

Fraction operator /(const Fraction &f, LL d) {
    Fraction ret = f;
    ret *= Fraction(1, d);
    return ret;
}

Fraction operator /(const Fraction &f, const Fraction &d) {
    Fraction ret = f;
    ret *= Fraction(d.den, d.num);
    return ret;
}

ostream& operator <<(ostream &os, const Fraction &f) {
    return os << '(' << f.num << '/' << f.den << ')';
}

Fraction calc_hour_sec_min(int H, Fraction ah, Fraction am, Fraction as) {
    if(ah == am && am == as) return Fraction(0);
    while(as < ah) as += Fraction(1);
    while(am < as) am += Fraction(1);
    while(as >= ah + Fraction(1)) as -= Fraction(1);
    while(am > as + Fraction(1)) am -= Fraction(1);
    //cout << ah << as << am << endl;
    assert(ah <= as && as <= am);
    // calc (as-ah)+x*(1/60-1/3600H) == (am-as)+x*(1/3600-1/60)
    // is (1/60-1/3600H-1/3600+1/60)x = am-as-as+ah
    const Fraction rhs = am - as - as + ah;
    const Fraction coef = Fraction(1,60) - Fraction(1,3600*H) - Fraction(1,3600) + Fraction(1,60);
    return rhs / coef;
}

Fraction calc_min_sec_hour(int H, Fraction ah, Fraction am, Fraction as) {
    if(ah == am && am == as) return Fraction(0);
    while(as < am) as += Fraction(1);
    while(ah < as) ah += Fraction(1);
    while(as >= am + Fraction(1)) as -= Fraction(1);
    while(ah > as + Fraction(1)) ah -= Fraction(1);
    assert(am <= as && as <= ah);
    // calc (as-am)+x*(1/60-1/3600) == (ah-as)+x*(1/3600H-1/60)
    // is (1/60-1/3600-1/3600H+1/60)x == ah-as-as+am
    const Fraction rhs = ah - as - as + am;
    const Fraction coef = Fraction(1,60) - Fraction(1,3600) - Fraction(1,3600*H) + Fraction(1,60);
    return rhs / coef;
}

Fraction calc(int H, int h, int m, int s) {
    Fraction ah = Fraction(h*3600 + m*60 + s, H*3600);
    Fraction am = Fraction(m*60 + s, 3600);
    Fraction as = Fraction(s, 60);
    Fraction dmh = am - ah;
    Fraction dsh = as - ah;
    if(dmh.num < 0) dmh += Fraction(1);
    if(dsh.num < 0) dsh += Fraction(1);
    if(dmh > dsh) { // hour-sec-min
        if(as < ah) as += Fraction(1);
        if(am < as) am += Fraction(1);
        Fraction mid = (ah + am) / 2;
        if(as <= mid) {
            return calc_hour_sec_min(H, ah, am, as);
        } else {
            // calc as+x/60 == am+x/3600
            // is (1/60-1/3600)x == am-as
            const Fraction tmp = (am - as) / (Fraction(1,60) - Fraction(1,3600));
            const Fraction tmp2 = (ah - as + Fraction(1)) / (Fraction(1,60) - Fraction(1,3600*H));
            if(tmp < tmp2) {
                return tmp + calc_min_sec_hour(H, ah+tmp/(H*3600), am+tmp/3600, as+tmp/60);
            } else {
                return tmp2 + calc_hour_sec_min(H, ah+tmp2/(H*3600), am+tmp2/3600, as+tmp2/60);
            }
        }
    } else if(dmh <= dsh) { // min-sec-hour
        if(as < am) as += Fraction(1);
        if(ah <= as) ah += Fraction(1);
        Fraction mid = (ah + am) / 2;
        if(as <= mid) {
            return calc_min_sec_hour(H, ah, am, as);
        } else {
            // calc as+x/60 == ah+x/3600H
            // is (1/60-1/3600H)x == ah-as
            const Fraction tmp = (ah - as) / (Fraction(1,60) - Fraction(1,3600*H));
            const Fraction tmp2 = (am - as + Fraction(1)) / (Fraction(1,60) - Fraction(1,3600));
            if(tmp < tmp2) {
                return tmp + calc_hour_sec_min(H, ah+tmp/(H*3600), am+tmp/3600, as+tmp/60);
            } else {
                return tmp2 + calc_min_sec_hour(H, ah+tmp2/(H*3600), am+tmp2/3600, as+tmp2/60);
            }
        }
    }
    assert(false);
}

bool solve() {
    int H, h, m, s;
    if(!(cin >> H >> h >> m >> s)) return false;
    if(!H && !h && !m && !s) return false;

    Fraction pass = calc(H, h, m, s);
    //cout << pass << endl;
    s += pass.num / pass.den;
    pass -= Fraction(pass.num / pass.den);
    m += s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    h %= H;
    if(h == 0 && m == 0 && s == 0 && pass == Fraction(0,1)) {
        pass = calc(H, h, m, s);
        s += pass.num / pass.den;
        pass -= Fraction(pass.num / pass.den);
        m += s / 60;
        s %= 60;
        h += m / 60;
        m %= 60;
        h %= H;
    }
    pass += Fraction(s);
    cout << h << ' ' << m << ' ' << pass.num << ' ' << pass.den << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
