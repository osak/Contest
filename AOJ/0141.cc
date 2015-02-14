//Name: Spiral Pattern
//Level: 2
//Category: シミュレーション
//Note: 

/**
 * n×nの領域を用意して、左下隅から渦巻きをたどるようにして埋めていく。
 * 現在の進行方向について、壁にぶつかるときか、もう1歩進むと他の線に干渉するというときには右に曲がる。
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ostream support for vector.
template<typename T>
ostream& operator <<(ostream &os, const vector<T> &v) {
    for(const T &t : v) {
        os << t << endl;
    }
    return os;
}

template<typename T>
struct Pair {
    T a, b;

    Pair() : a(T()), b(T()) {}
    Pair(const T &a, const T &b) : a(a), b(b) {}

    Pair& operator += (const Pair &p) {
        a += p.a;
        b += p.b;
        return *this;
    }

    friend Pair operator +(Pair p1, const Pair &p2) {
        p1 += p2;
        return p1;
    }

    friend ostream& operator <<(ostream &os, const Pair &p) {
        return os << "(" << p.a << ", " << p.b << ")";
    }

    /* vector accessor mixin {{{*/
    template<typename U>
    auto of(U &u) const -> decltype(u[a][b]) {
        return u[a][b];
    }

    template<typename U>
    bool valid_in(const U &u) const {
        return a < u.size() && b < u[0].size();
    }
    /*}}}*/
};

static const Pair<int> DELTA[4] = {
    Pair<int>(-1, 0), Pair<int>(0, -1), Pair<int>(1, 0), Pair<int>(0, 1)
};

bool solve(bool first) {
    if(!first) cout << endl;
    int N;
    cin >> N;

    vector<string> f(N, string(N, ' '));
    Pair<int> pos(N-1, 0);
    int dir = 1;
    bool stucked = false;
    while(true) {
        pos.of(f) = '#';
        auto next = pos + DELTA[dir];
        auto nn = next + DELTA[dir];
        auto nl = next + DELTA[(dir+3)%4];
        if(nl.valid_in(f) && nl.of(f) == '#') {
            break;
        }
        if(!next.valid_in(f) || (nn.valid_in(f) && nn.of(f) == '#')) {
            if(stucked) break;
            dir = (dir + 3) % 4;
            stucked = true;
        } else {
            stucked = false;
            pos = next;
        }
    }
    cout << f;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(2);

    bool first = true;
    int N;
    cin >> N;
    while(N-- && solve(first)) {
        first = false;
    }
    return 0;
}
