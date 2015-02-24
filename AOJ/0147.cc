//Name: Fukushimaken
//Level: 2
//Category: シミュレーション
//Note: 

/**
 * 問題文の通りにシミュレーションする。
 * グループの到着と、食事の終了イベントをpriority_queueに突っ込んで取り出すようにする。
 * 到着したグループは別途queueに突っ込み、席に空きができたら埋めていくようにする。
 *
 * 入力が小さいので、特に効率のよいデータ構造を使わなくても間に合う。
 * オーダーは O(NW log N)。
 * ただしNはグループ数で、N=100。Wは座席の幅で、W=17。
 */
#include <iostream>
#include <queue>

using namespace std;

struct Event {
    enum {
        ARRIVAL,
        FINISH
    } type;
    int t;
    int idx;

    bool operator <(const Event &e) const {
        return t > e.t;
    }
};

int gsize(int n) {
    return (n % 5 == 1 ? 5 : 2);
}

bool solve(bool first) {
    vector<int> res(100, -1);
    priority_queue<Event> eventq;
    for(int i = 0; i < 100; ++i) {
        eventq.push(Event{Event::ARRIVAL, i*5, i});
    }
    queue<int> q;
    vector<int> seats(17, -1);
    while(!eventq.empty()) {
        const int curt = eventq.top().t;
        while(!eventq.empty() && eventq.top().t == curt) {
            const Event e = eventq.top();
            eventq.pop();
            if(e.type == Event::ARRIVAL) {
                q.push(e.idx);
            } else {
                for(int i = 0; i < 17; ++i) {
                    if(seats[i] == e.idx) seats[i] = -1;
                }
            }
        }
        while(!q.empty()) {
            const int idx = q.front();
            const int s = gsize(idx);
            int acc = 0;
            int pos = -1;
            for(int i = 0; i < 17; ++i) {
                if(seats[i] == -1) {
                    ++acc;
                } else {
                    acc = 0;
                }
                if(acc == s) {
                    pos = i - s + 1;
                    break;
                }
            }
            if(pos == -1) break;
            for(int i = 0; i < s; ++i) {
                seats[pos+i] = idx;
            }
            res[idx] = curt - idx*5;
            eventq.push(Event{Event::FINISH, curt + 17*(idx%2) + 3*(idx%3) + 19, idx});
            q.pop();
            /*
               for(int i = 0; i < 17; ++i) {
               if(seats[i] == -1) cout << '-';
               else cout << seats[i]%10;
               }
               cout << endl;
               */
        }
    }

    int N;
    while(cin >> N) {
        cout << res[N] << endl;
    }
    return false;
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
