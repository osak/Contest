//Name: Fish
//Level: 3
//Category: 座標圧縮
//Note:

/*
 * X座標とY座標が決まった時、そこからZ方向に伸ばして条件を満たす部分の長さは、直方体の内部に入ったらカウンタを+1, 出たら-1とすることで求められる。
 * （同じZ座標で直方体の終わりと始まりが複数あるとき、一度に処理する必要があることに注意）
 * また、X座標を固定して考えると、直方体の辺のあるY座標をソートして考えた時、ys[i]からys[i+1]までは均一に広がっている。
 * したがって、ys[i]で上記のカウントを取り、ys[i+1]-ys[i]倍すると、あるX座標において条件を満たす部分の面積が求められる。
 * X座標についても同様の処理を行うことで、体積になる。
 *
 * オーダーは O(N^3)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rect {
    int x1, y1, z1, x2, y2, z2;

    bool operator <(const Rect &other) const {
        return z1 < other.z1;
    }
};

enum EventType {
    EVENT_CLOSE,
    EVENT_OPEN,
};

struct Event {
    int x1, y1, x2, y2;
    int z;
    EventType event;

    Event(int x1, int y1, int x2, int y2, int z, EventType ev) : x1(x1), y1(y1), x2(x2), y2(y2), z(z), event(ev) {}

    bool operator <(const Event &other) const {
        if(z != other.z) return z < other.z;
        return event < other.event;
    }
};

vector<Rect> rects;
vector<int> event_x, event_y;
vector<Event> event_z;
int K;

void sort_and_uniq(vector<int> &v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

inline bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

long long sweep_z(const int x, const int y) {
    const int N = event_z.size();
    long long ans = 0;
    int cnt = 0;
    int prev_z = 0;
    for(int i = 0; i < N; ) {
        const int z = event_z[i].z;
        if(cnt >= K) {
            ans += z - prev_z;
        }
        while(i < N && z == event_z[i].z) {
            const Event &ev = event_z[i];
            if(in_range(ev.x1, x, ev.x2) && in_range(ev.y1, y, ev.y2)) {
                if(ev.event == EVENT_CLOSE) --cnt;
                else ++cnt;
            }
            ++i;
        }
        prev_z = z;
    }
    return ans;
}

long long sweep_y(const int x) {
    const int N = event_y.size();
    long long ans = 0;
    for(int i = 0; i < N-1; ++i) {
        const int y = event_y[i];
        long long length = sweep_z(x, y);
        ans += length * (event_y[i+1] - y);
    }
    return ans;
}

long long sweep() {
    const int N = event_x.size();
    long long ans = 0;
    for(int i = 0; i < N-1; ++i) {
        const int x = event_x[i];
        long long area = sweep_y(x);
        ans += area * (event_x[i+1] - x);
    }
    return ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N >> K;
    rects.resize(N);
    for(int i = 0; i < N; ++i) {
        Rect &r = rects[i];
        cin >> r.x1 >> r.y1 >> r.z1 >> r.x2 >> r.y2 >> r.z2;
        event_x.push_back(r.x1);
        event_x.push_back(r.x2);
        event_y.push_back(r.y1);
        event_y.push_back(r.y2);
        event_z.push_back(Event(r.x1, r.y1, r.x2, r.y2, r.z1, EVENT_OPEN));
        event_z.push_back(Event(r.x1, r.y1, r.x2, r.y2, r.z2, EVENT_CLOSE));
    }
    sort_and_uniq(event_x);
    sort_and_uniq(event_y);
    sort(event_z.begin(), event_z.end());

    cout << sweep() << endl;
    return 0;
}
