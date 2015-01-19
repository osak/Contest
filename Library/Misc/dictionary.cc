// Dictionary for coordinate compression.
// 1. Dict::add to register coordinates.
// 2. Dict::freeze to perform compression
// After step 2, conversion can be performed by Dict::get (or Dict::operator [])
// and reverse conversion by Dict::rev.
//
// Amortized O(1) for step 1.
// O(N log N) for step 2.
struct Dict {
private:
    vector<int> buf;
    vector<int> dict;

public:
    void add(int v) {
        buf.push_back(v);
    }

    void freeze() {
        sort(begin(buf), end(buf));
        buf.erase(unique(begin(buf), end(buf)), end(buf));
        dict.resize(buf.back()+1, -1);
        const int N = buf.size();
        for(int i = 0; i < N; ++i) {
            dict[buf[i]] = i;
        }
    }

    int get(int v) const {
        return dict[v];
    }

    int operator[](int i) const {
        return get(i);
    }

    int rev(int v) const {
        return buf[v];
    }

    int size() const {
        return buf.size();
    }
};

// Not tested
