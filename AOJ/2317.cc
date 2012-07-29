#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<int, int> Segment;
typedef unsigned long long ULL;

enum EventType {
    EVENT_OPEN,
    EVENT_CLOSE,
    EVENT_SPLIT,
    EVENT_NUM
};

struct Event {
    EventType type;
    int pos;
    int data;

    Event() {}
    Event(EventType t, int p) : type(t), pos(p) {}
    Event(EventType t, int p, int d) : type(t), pos(p), data(d) {}

    bool operator < (const Event &e) const {
        if(pos != e.pos) return pos < e.pos;

        if(type == EVENT_SPLIT) return false;
        if(e.type == EVENT_SPLIT) return true;
        return type < e.type;
    }
};

ostream& operator << (ostream &os, const Event &e) {
    os << '(' << e.type << ' ' << e.pos << ' ' << e.data << ')';
    return os;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    vector<Segment> segments;
    vector<int> splits;
    vector<Event> events;
    for(int i = 0; i < N; ++i) {
        int s, t;
        scanf("%d %d", &s, &t);
        segments.push_back(Segment(s, t));
        events.push_back(Event(EVENT_OPEN, min(s, t), i));
        events.push_back(Event(EVENT_CLOSE, max(s, t), i));
    }
    for(int i = 0; i < M; ++i) {
        int p;
        scanf("%d", &p);
        splits.push_back(p);
        events.push_back(Event(EVENT_SPLIT, p));
    }
    sort(events.begin(), events.end());

    vector<int> spcnt(N, 0);
    {
        int acc = 0;
        for(int i = 0; i < events.size(); ++i) {
            const Event &e = events[i];
            if(e.type == EVENT_SPLIT) ++acc;
            else if(e.type == EVENT_OPEN) spcnt[e.data] = acc;
            else spcnt[e.data] = acc - spcnt[e.data];
        }
    }

    events.clear();
    for(int i = 0; i < N; ++i) {
        const Segment &s = segments[i];
        bool open_is_on = (s.first < s.second || spcnt[i] % 2 == 0);
        bool close_is_on = (s.second < s.first || spcnt[i] % 2 == 0);

        events.push_back(Event(EVENT_OPEN, min(s.first, s.second), open_is_on));
        events.push_back(Event(EVENT_CLOSE, max(s.first, s.second), close_is_on));
    }
    for(int i = 0; i < splits.size(); ++i) {
        events.push_back(Event(EVENT_SPLIT, splits[i]));
    }
    sort(events.begin(), events.end());

    int on = 0;
    int off = 0;
    int prev = 0;
    ULL ans = 0;
    for(int i = 0; i < events.size(); ++i) {
        const Event &e = events[i];
        //cout << e << endl;

        ans += on * (ULL)(e.pos - prev);
        if(e.type == EVENT_OPEN) {
            if(e.data) ++on;
            else ++off;
        }
        else if(e.type == EVENT_CLOSE) {
            if(e.data) --on;
            else --off;
        }
        else {
            swap(on, off);
        }
        //cout << on << ' ' << off << endl;
        prev = e.pos;
    }

    cout << ans << endl;

    return 0;
}
