#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>

typedef long double LD;

int sgn(int a) {
    return a == 0 ? 0 : a<0 ? -1 : 1;
}

void solve() {
    int a_, b_, c_;
    scanf("%d %d %d", &a_, &b_, &c_);

    if(a_ == 0) {
        if(b_ == 0) {
            if(c_ == 0) {
                puts("3");
            } else {
                puts("0");
            }
            return;
        } else {
            printf("1 %.9Lf\n", -static_cast<long double>(c_)/b_);
            return;
        }
        return;
    }

    if(abs(b_) % 2 == 0) {
        const long long b2 = static_cast<long long>(b_/2) * (b_/2);
        if(sgn(a_) * sgn(c_) != -1) {
            if(b2 % abs(a_) == 0 && b2 / abs(a_) == abs(c_)) {
                printf("1 %.9Lf\n", -static_cast<long double>(b_) / 2 / a_);
                return;
            }
        }
    }
    const long double b2 = static_cast<long double>(b_) * b_;
    const long double ac = static_cast<long double>(a_) * c_;
    const long double det = b2 - 4.0*ac;
    if(det < 0) {
        puts("0");
        return;
    }
    //printf("%Lf %Lf %Lf %Lf\n", b2, ac, det, sqrtl(det));
    long double a1, a2;
    if(b_ > 0) {
        a1 = (-1.0*b_ - sqrtl(det)) / (2.0*a_);
        a2 = 4.0*ac / (2.0*a_*(-1.0*b_ - sqrtl(det)));
    } else {
        a1 = (-1.0*b_ + sqrtl(det)) / (2.0*a_);
        a2 = 4.0*ac / (2.0*a_*(-1.0*b_ + sqrtl(det)));
    }
    if(a1 > a2) std::swap(a1, a2);
    printf("2 %.9Lf %.9Lf\n", a1, a2);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
