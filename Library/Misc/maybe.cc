template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(const T &t) : val(t), valid(true) {}
    Maybe(const Maybe<T> &m) : valid(m.valid) {
        if(valid) val = m.val;
    }

    const T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return rv;
    }

    const Maybe<T>& operator =(const Maybe<T> &rv) {
        if(rv.valid) val = rv.val;
        valid = rv.valid;
        return rv;
    }

    operator T() const {
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
