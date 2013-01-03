#include "grader.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

enum EventType { EVENT_OPEN, EVENT_CLOSE, EVENT_TERM };

struct Event {
    EventType type;
    int t;

    Event(EventType type, int t) : type(type), t(t) {}
    bool operator <(const Event &other) const {
        if(t != other.t) return t > other.t;
        return type > other.type;
    }
};

bool intersect(const pair<int,int> &a, const pair<int,int> &b) {
    return a.first < b.second && a.second > b.first;
}

void push_with_merge(vector<pair<int,int> > &v, const pair<int,int> &val) {
    if(v.size() > 0 && v.back().second == val.first) {
        v.back().second = val.second;
    }
    else {
        v.push_back(val);
    }
}

void schedule(int W, int N, int X[], int D[]) {
    priority_queue<Event> q;
    for(int i = 0; i < N; ++i) {
        q.push(Event(EVENT_OPEN, max(0, X[i]-D[i]+1)));
        if(X[i]+D[i] <= W) q.push(Event(EVENT_CLOSE, X[i]+D[i]));
    }
    q.push(Event(EVENT_TERM, W));

    int cnt = 0;
    int prev = 0;
    vector<vector<pair<int,int> > > ranges(N+1);
    while(!q.empty()) {
        int t = q.top().t;
        //cout << cnt << ' ' << prev << ' ' << t << endl;
        ranges[cnt].push_back(make_pair(prev, t));

        while(!q.empty() && q.top().t == t) {
            Event e = q.top();
            q.pop();

            if(e.type == EVENT_OPEN) {
                ++cnt;
            }
            else if(e.type == EVENT_CLOSE) {
                --cnt;
            }
        }
        prev = t;
    }

    for(int id = N; id >= 1; --id) {
        if(id < N) {
            vector<pair<int,int> >::iterator curit = ranges[id].begin();
            vector<pair<int,int> >::iterator previt = ranges[id+1].begin();

            vector<pair<int,int> > next;
            // prevをひとつずつcurにマージしていく
            for(; previt != ranges[id+1].end(); ++previt) {
                // 交差する区間の最初
                while(curit != ranges[id].end() && curit->first < previt->second && !intersect(*curit, *previt)) {
                    push_with_merge(next, *curit);
                    ++curit;
                }
                const vector<pair<int,int> >::iterator beginit = curit;

                // 交差するものがないとき
                if(beginit == ranges[id].end() || !intersect(*beginit, *previt)) {
                    push_with_merge(next, *previt);
                    continue;
                }

                // 交差するものが少なくとも1つあるとき
                // 交差する区間の最後
                while(curit != ranges[id].end() && curit->first < previt->second && intersect(*curit, *previt)) {
                    ++curit;
                }
                if(curit != ranges[id].begin()) --curit;

                pair<int,int> new_range = make_pair(min(beginit->first, previt->first), max(curit->second, previt->second));
                push_with_merge(next, new_range);
            }

            // 余りを詰める
            for(; curit != ranges[id].end(); ++curit) {
                push_with_merge(next, *curit);
            }

            ranges[id].swap(next);
        }

        pair<int,int> ans(0, -1);
        for(vector<pair<int,int> >::iterator it = ranges[id].begin(); it != ranges[id].end(); ++it) {
            //cout << id << ' ' << it->first << ' ' << it->second << endl;
            if(ans.second - ans.first < it->second - it->first) {
                ans = *it;
            }
        }
        if(ans.second == -1) ans = make_pair(0, 1);
        answer(id, ans.first, ans.second-1);
    }
}

