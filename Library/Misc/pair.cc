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

// vim:set fdm=marker:
