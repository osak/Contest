//Name: Sumsets
//Level: 3
//Category: 組み合わせ,半分全列挙
//Note:

/*
 * d-cの組を全列挙し、その値をキーとしてO(N)以下で引けるようにする。
 * （ここではソートと二分探索を使ってO(log N)）
 * すべてのa+bに対して同じ値を持つd-cの組を列挙し、条件を満たすものでansを更新する。
 *
 * オーダーは O(N log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Tag {
    int ci, di;
    Tag (int c, int d) : ci(c), di(d) {}
    bool operator <(const Tag &other) const {
        return ci < other.ci;
    }
};

struct Pred {
    bool operator ()(const pair<long long,Tag> &a, const pair<long long,Tag> &b) const {
        return a.first < b.first;
    }
};

typedef vector<pair<long long,Tag> > TagVector;
typedef TagVector::iterator Iterator;
typedef pair<Iterator,Iterator> Range;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<long long> v(N);
        for(int i = 0; i < N; ++i) {
            cin >> v[i];
        }

        vector<pair<long long,Tag> > tags;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(i != j) {
                    const long long diff = v[i] - v[j];
                    tags.push_back(make_pair(diff, Tag(j, i)));
                    //cout << diff << ' ' << j << ' ' << i << endl;
                }
            }
        }
        sort(tags.begin(), tags.end(), Pred());

        long long ans = -2000000000;
        bool found = false;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < i; ++j) {
                const long long sum = v[i] + v[j];
                Range range = equal_range(tags.begin(), tags.end(), pair<long long,Tag>(sum, Tag(0,0)), Pred());
                Iterator it = range.first;
                while(it != range.second) {
                    if(it->second.ci != i && it->second.ci != j && 
                       it->second.di != i && it->second.di != j) 
                    {
                        //cout << i << ' ' << j << ' ' << v[it->second.di] << endl;
                        ans = max(ans, v[it->second.di]);
                        found = true;
                    }
                    ++it;
                }
            }
        }
        if(found) cout << ans << endl;
        else cout << "no solution" << endl;
    }
    return 0;
}
