//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cassert>
#include <cctype>
#include <set>

using namespace std;

template<typename T>
struct LogNArray {
    typedef pair<size_t, T> Element;
    struct Cmp {
        bool operator()(const Element &e1, const Element &e2) const {
            return e1.first < e2.first;
        }
    };
    set<pair<size_t, T>, Cmp> data;

    LogNArray(int size) {
        for(size_t i = 0; i < size; ++i) {
            data.insert(Element(i, T()));
        }
    }

    T& operator[](const size_t index) {
        return data.find(Element(index, T()))->second;
    }

    void erase(const size_t index) {
        data.erase(Element(index, T()));
    }

    void insert(const size_t index, const T &value) {
        data.insert(Element(index, value));
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    vector<int> as(N), bs(N);
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
    }
    for(int i = 0; i < N; ++i) {
        cin >> bs[i];
    }

    LogNArray<int> arr(N);
    for(int i = 0; i < N; ++i) {
        const auto it = upper_bound(bs.begin(), bs.end(), as[i]);
        const auto limit = it - bs.begin() - 1;
        arr[i] = limit;
    }

    int ans = 0;
    for(int i = N-1; i >= 0; --i) {
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) {
    }
    return 0;
}
