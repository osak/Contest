//Name: Squares
//Level: 3
//Category: ハッシュ,高速化
//Note: TLE 厳しい

/*
 * ある2点を決めて，これを辺とする正方形ができるかを確かめる．
 * TLEが厳しいため，点の存在判定はハッシュテーブルで行なう．
 * また，あらかじめ点を座標でソートしておくと
 *   for(i in 0..N) for(j in (i+1)..N)
 * のループで点対を列挙したときにちょうど2回だけ同じ正方形を数え上げることが保証される．
 *
 * オーダーは O(N^2)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <cstdio>

using namespace std;

typedef complex<int> Vector;

bool veccmp(const Vector &a, const Vector &b) {
    if(a.real() != b.real()) return a.real() < b.real();
    return a.imag() < b.imag();
}

struct Hasher {
    unsigned operator ()(const Vector &point) {
        unsigned x = static_cast<unsigned>(point.real()+20000);
        unsigned y = static_cast<unsigned>(point.imag()+20000);
        return x*40001+y;
    }
};

// 削除のことを考えていない適当ハッシュテーブル
template<class T, class Hash>
struct HashTable {
    vector<T> elems;
    vector<unsigned char> used;
    int size;
    Hash hasher;

    HashTable(int size) : elems(size), used(size, 0), size(size) {}

    void add(const T &val) {
        unsigned hash = hasher(val) % size;
        while(used[hash]) hash = (hash+1) % size;
        used[hash] = 1;
        elems[hash] = val;
    }

    bool has(const T &val) {
        unsigned hash = hasher(val) % size;
        while(used[hash]) {
            if(elems[hash] == val) return true;
            ++hash;
        }
        return false;
    }
};

int main() {
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    while(true) {
        int N;
        scanf("%d", &N);
        if(!N) break;

        vector<Vector> points(N);
        HashTable<Vector,Hasher> dict(100003);
        for(int i = 0; i < N; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            points[i] = Vector(x, y);
            dict.add(points[i]);
        }
        sort(points.begin(), points.end(), veccmp);

        int ans = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = i+1; j < N; ++j) {
                if(i == j) continue;
                Vector v = points[j] - points[i];
                // Clockwise
                {
                    Vector nv(-v.imag(), v.real());
                    Vector pk = points[j] + nv;
                    if(dict.has(pk)) {
                        nv = -v;
                        Vector pl = pk + nv;
                        if(dict.has(pl)) ++ans;
                    }
                }
            }
        }

        printf("%d\n", ans/2);
    }

    return 0;
}
