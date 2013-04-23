//Name: Everlasting Zero
//Level: 4
//Category: Greedy,貪欲法
//Note:

/*
 * 各アクションが各スキルについて必要なポイントは，完全に1つの範囲として考えて良い．
 * （そう考えられない入力は必ず矛盾する）
 * したがって，スキルを貪欲に上げていき，どれかのアクションの範囲から外れてしまうギリギリで止め，
 * その段階で覚えられるアクションを全て覚える，という操作を繰り返すことで全てのアクションを覚えるか，
 * 途中で無理なパターンが生じるかのどちらかになる．
 *
 * オーダーは O(NMK)．
 */
#define _GLIBCXX_DEBUG
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

enum EventType {
    EVENT_CLOSE,
    EVENT_OPEN,
    EVENT_NUM
};

const int INF = 1000;
struct Event {
    EventType type;
    int action_id, skill_id;
    int val;

    Event() {}
    Event(EventType t, int aid, int sid, int v) : type(t), action_id(aid), skill_id(sid), val(v) {}

    bool operator <(const Event &other) const {
        if(val != other.val) return val < other.val;
        return type < other.type;
    }
};

int find_not_pending_skill(const vector<set<int> > &v, const vector<deque<Event> > &events) {
    const int N = v.size();
    for(int i = 0; i < N; ++i) {
        if(events[i].size() > 0 && v[i].size() == 0) return i;
    }
    return -1;
}

bool solve(int M, int N) {
    vector<deque<Event> > events(N);
    vector<vector<pair<int,int> > > conditions(M, vector<pair<int,int> >(N, make_pair(0, INF)));
    bool contradiction = false;
    for(int aid = 0; aid < M; ++aid) {
        vector<pair<int,int> > &ranges = conditions[aid];
        int K;
        cin >> K;
        while(K--) {
            int skill_id, val;
            string op;
            cin >> skill_id >> op >> val;
            --skill_id;
            if(op == ">=") {
                ranges[skill_id].first = max(ranges[skill_id].first, val); 
            } else {
                ranges[skill_id].second = min(ranges[skill_id].second, val);
            }
        }

        for(int sid = 0; sid < N; ++sid) {
            if(ranges[sid].second < ranges[sid].first) {
                contradiction = true;
            }
            //events[sid].push_back(Event(EVENT_OPEN, aid, sid, ranges[sid].first));
            events[sid].push_back(Event(EVENT_CLOSE, aid, sid, ranges[sid].second));
        }
    }
    if(contradiction) return false;

    for(int i = 0; i < N; ++i) {
        sort(events[i].begin(), events[i].end());
    }
    int cnt = 0;
    vector<unsigned char> learned(M, 0);
    vector<set<int> > pendings(N);
    vector<int> sp(N, 0);
    while(true) {
        const int idx = find_not_pending_skill(pendings, events);
        if(idx == -1) { // Check conditions
            bool erased = false;
            for(int i = 0; i < M; ++i) {
                if(learned[i]) continue;
                bool flag = true;
                for(int j = 0; j < N; ++j) {
                    if(conditions[i][j].first <= sp[j] && sp[j] <= conditions[i][j].second) {
                        // Pass
                    } else {
                        flag = false;
                    }
                }
                if(flag) {
                    for(int j = 0; j < N; ++j) {
                        pendings[j].erase(i);
                    }
                    learned[i] = 1;
                    //cout << "eliminate " << i << endl;
                    erased = true;
                    ++cnt;
                }
            }
            if(cnt == M) return true;
            if(!erased) return false;
        } else {
            while(events[idx].size() > 0) {
                const Event evt = events[idx][0];
                events[idx].pop_front();
                //cout << evt.type << ' ' << evt.skill_id << ' ' << evt.val << endl;
                if(learned[evt.action_id]) continue;
                if(evt.type == EVENT_OPEN) {
                    sp[evt.skill_id] = evt.val;
                } else if(evt.type == EVENT_CLOSE) {
                    pendings[evt.skill_id].insert(evt.action_id);
                    sp[evt.skill_id] = evt.val;
                    break;
                } else {
                    assert(false);
                }
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int M, N;
    while(cin >> M >> N) {
        if(solve(M, N)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
