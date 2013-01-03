#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Tag {
    int probno, point, t;
    bool operator <(const Tag &other) const {
        if(point != other.point) return point < other.point;
        return probno < other.probno;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, T;
    cin >> N >> T;
    vector<int> ps(N);
    for(int i = 0; i < N; ++i) {
        cin >> ps[i];
    }
    const int p_sum = accumulate(ps.begin(), ps.end(), 0);
    vector<Tag> v(p_sum);
    {
        int idx = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < ps[i]; ++j) {
                cin >> v[idx].point;
                v[idx].probno = i;
                ++idx;
            }
        }
    }
    {
        int idx = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < ps[i]; ++j) {
                cin >> v[idx].t;
                ++idx;
            }
        }
    }
    sort(v.begin(), v.end());
    vector<int> score(N, 0);
    for(vector<Tag>::iterator it = v.begin(); it != v.end(); ++it) {
        //cout << it->point << endl;;
        T -= it->t;
        if(T < 0) break;
        score[it->probno] = it->point;
    }
    cout << accumulate(score.begin(), score.end(), 0) << endl;
    return 0;
}
