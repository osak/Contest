#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Fraction {
    int a, b;
    
    Fraction() : a(0), b(1) {}
    Fraction(int a_, int b_) : a(a_), b(b_) {}

    /*逆順にソートしたいため、判定条件を逆にする*/
    /*コメントアウトしてあるoperator<が正しい実装*/
    /*
    bool operator < (const Fraction &other) const {
        if(b*other.b < 0) return a*other.b > other.a*b;
        return a*other.b < other.a*b;
    }
    */

    bool operator < (const Fraction &other) const {
        if(b*other.b < 0) return a*other.b < other.a*b;
        return a*other.b > other.a*b;
    }
};

int main() {
    int N, n;
    scanf("%d %d", &N, &n);
    vector<Fraction> v(N);

    for(int i = 0; i < N; ++i) {
        scanf("%d/%d", &v[i].a, &v[i].b);
    }
    partial_sort(v.begin(), v.begin()+n, v.end());
    
    printf("%d/%d\n", v[n-1].a, v[n-1].b);

    return 0;
}
