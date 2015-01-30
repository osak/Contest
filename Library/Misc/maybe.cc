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
    bool update(const T &v, Cond cond) {
        if(!valid || cond(v, val)) {
            val = v;
            valid = true;
            return true;
        }
        return false;
    }

    bool update(const T &v) {
        return update(v, less<T>());
    }
};/*}}}*/
