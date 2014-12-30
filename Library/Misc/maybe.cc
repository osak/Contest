template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }

    operator T() {
        return valid ? val : T();
    }

    template<typename Cond>
    void update(const T &v, Cond cond) {
        if(!valid || cond(v, val)) {
            val = v;
            valid = true;
        }
    }

    void update(const T &v) {
        update(v, less<T>());
    }
};/*}}}*/
