//Name: Gather the Maps!
//Level: 3
//Category: グラフ,Graph,幅優先探索
//Note: 

/**
 * まとめた地図を誰が持っているかは、あとで都合がいいように変えれば良い。
 * ある子孫が持っている可能性のある地図集合は一意に定まる（もしも複数の可能性があるなら、
 * マージして1つの地図にまとめられる）ので、要するに非決定性オートマトンをたどるのと同じことになる。
 *
 * オーダーは O(N log N)。
 */
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

typedef bitset<50> State;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> members[30];
    vector<State> state(N);
    for(int i = 0; i < N; ++i) {
        int f;
        cin >> f;
        while(f--) {
            int d;
            cin >> d;
            --d;
            members[d].push_back(i);
        }
        state[i].set(i);
    }
    int ans = -1;
    if(N == 1) {
        ans = 1;
    } else {
        for(int d = 0; d < 30; ++d) {
            State s;
            for(int i : members[d]) {
                s |= state[i];
            }
            if(s.count() == N) {
                ans = d+1;
                break;
            }
            for(int i : members[d]) {
                state[i] = s;
            }
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
