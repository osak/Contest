#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>
#include <deque>
#include <queue>
#include <cstdio>

using namespace std;

const int INF = 1000;

inline bool in_range(int a, int x, int b) {
    return a <= x && x <= b;
}

//閉区間
struct Range {
    int start, end;
    int customer_id;
    bool in_use;

    Range() {}
    Range(int s, int e) : start(s), end(e), in_use(false) {}

    Range merge(const Range &other) {
        start = min(other.start, start);
        end = max(other.end, end);
        return Range(start, end);
    }

    /**
     * このRangeを[start, at]と(at, end]に分割する
     */
    pair<Range,Range> split(int at) const {
        //cout << start << ' ' << at << ' ' << end << endl;
        //assert(in_range(start, at, end));

        Range left = Range(start, at);
        Range right = Range(at+1, end);

        return make_pair(left, right);
    }

    int length() const {
        return end - start + 1;
    }

    bool valid() const { 
        return length() > 0;
    }
};

struct Counter {
    deque<Range> seats;

    Counter(int N) {
        seats.push_back(Range(1, N));
    }

    // (maximal_pos_of_range, (left_space, right_space))
    pair<int, pair<int,int> > maximal_pos(int N) const {
        pair<int,int> dist = make_pair(-1, -1);
        int pos = -1;
        for(int i = 0; i < seats.size(); ++i) {
            if(seats[i].in_use) continue;
            if(seats[i].length() < N) continue;

            //int center = seats[i].start + seats[i].length()/2;
            int center = (seats[i].start + seats[i].end) / 2;
            int left_edge = center - ((N-1)/2+1) + 1;
            int left = left_edge - seats[i].start; //左に偏るため by Criteria 4
            int right = seats[i].end - (left_edge + N-1);
            //cout << left << ' ' << right << endl;
            if(i == 0) {
                left = INF;
                right = seats[i].length()-N;
            }
            else if(i+1 == seats.size()) {
                left = seats[i].length()-N;
                right = INF;
            }

            int c1 = min(dist.first, dist.second) - min(left, right);
            int c2 = max(dist.first, dist.second) - max(left, right);
            if( (c1 < 0) || //Criteria 1
                (c1 == 0 && c2 < 0)) { //Criteria 2
                dist = make_pair(left, right);
                pos = i;
            }
        }

        return make_pair(pos, dist);
    }

    void insert(int pos, int N, int customer_id) {
        assert(!seats[pos].in_use);
        assert(seats[pos].length() >= N);

        int center = (seats[pos].start + seats[pos].end) / 2;
        int left = center - ((N-1)/2+1) + 1;
        int right = left + N-1;
        if(pos == 0) {
            left = 1;
            right = left+N-1;
        }
        else if(pos+1 == seats.size()) {
            right = seats[pos].end;
            left = right-N+1;
        }
        //cout << "insert " << N << " in " << left << endl;

        pair<Range,Range> left_range = seats[pos].split(left-1), right_range = left_range.second.split(right);
        right_range.first.customer_id = customer_id;
        right_range.first.in_use = true;

        seats.erase(seats.begin()+pos);
        if(right_range.second.valid()) seats.insert(seats.begin()+pos, right_range.second);
        seats.insert(seats.begin()+pos, right_range.first);
        if(left_range.first.valid()) seats.insert(seats.begin()+pos, left_range.first);

        //print();
    }

    int remove(int id) {
        for(int i = 0; i < seats.size(); ++i) {
            if(!seats[i].in_use) continue;
            if(seats[i].customer_id == id) {
                Range r = seats[i];
                if(i+1 < seats.size() && !seats[i+1].in_use) {
                    r = r.merge(seats[i+1]);
                    seats.erase(seats.begin()+i+1);
                }
                if(i > 0 && !seats[i-1].in_use) {
                    //cout << "merge left" << endl;
                    r = r.merge(seats[i-1]);
                    seats.erase(seats.begin()+i-1);
                    i--;
                }
                seats[i] = r;
                seats[i].in_use = false;
                break;
            }
        }
        //print();
    }

    void print() {
        for(int i = 0; i < seats.size(); ++i) {
            cout << "[" << seats[i].start << "," << seats[i].end << ":" << seats[i].in_use << "],";
        }
        cout << endl;
    }
};

struct Customer {
    int T, P, W, E;
    int counter;

    Customer(int T, int P, int W, int E) : T(T), P(P), W(W), E(E) {}
};

enum Event {
    EVENT_LEAVE,
    EVENT_COME,
};

struct Tag {
    int T;
    Event evt;
    int customer_id;

    Tag(int T, Event e, int id) : T(T), evt(e), customer_id(id) {}

    bool operator < (const Tag &other) const {
        if(T != other.T) return T > other.T;
        return evt > other.evt;
    }
};

int main() {
    ios::sync_with_stdio(0);

    while(true) {
        int N, M, T;
        cin >> N >> M >> T;
        if(!N && !M && !T) break;

        vector<Counter> counters;
        for(int i = 0; i < N; ++i) {
            int c;
            cin >> c;
            counters.push_back(Counter(c));
        }

        int all = 0;
        vector<Customer> customers;
        priority_queue<Tag> q;
        for(int id = 0; id < M; ++id) {
            int Ti, P, W, E;
            cin >> Ti >> P >> W >> E;
            customers.push_back(Customer(Ti, P, W, E));
            q.push(Tag(Ti, EVENT_COME, id));
            all += P;
        }

        double score = 0;
        int now = 0;
        queue<Tag> waiting;
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            switch(t.evt) {
                case EVENT_LEAVE:
                    //cout << "leave " << t.customer_id << endl;
                    counters[customers[t.customer_id].counter].remove(t.customer_id);
                    break;
                case EVENT_COME:
                    waiting.push(t);
                    break;
            }
            now = t.T;
            if(now >= T) break;

            while(!waiting.empty()) {
                Tag come = waiting.front();
                const Customer &customer = customers[come.customer_id];
                if(now - customer.T > customer.W) {
                    waiting.pop();
                    score -= 1 * customer.P;
                    continue;
                }

                pair<int, pair<int,int> > best = make_pair(0, make_pair(-1, -1));
                int bestcounter = -1;
                for(int i = 0; i < counters.size(); ++i) {
                    pair<int, pair<int,int> > cand = counters[i].maximal_pos(customer.P);
                    if(cand.first != -1) {
                        const pair<int,int> &best_s = best.second;
                        const pair<int,int> &tmp_s = cand.second;

                        int c1 = min(best_s.first, best_s.second) - min(tmp_s.first, tmp_s.second);
                        int c2 = max(best_s.first, best_s.second) - max(tmp_s.first, tmp_s.second);
                        if( (c1 < 0) || //Criteria 1
                            (c1 == 0 && c2 < 0)) {  //Criteria 2
                            best = cand;
                            bestcounter = i;
                        }
                    }
                }
                if(bestcounter != -1) {
                    counters[bestcounter].insert(best.first, customers[come.customer_id].P, come.customer_id);
                    customers[come.customer_id].counter = bestcounter;
                    //cout << come.customer_id << ": Waited " << (now - customer.T) << endl;
                    score += (double)(customer.W - (now - customer.T)) * customer.P / customer.W;
                    q.push(Tag(now + customer.E, EVENT_LEAVE, come.customer_id));
                    waiting.pop();
                }
                else {
                    // Give up in this turn
                    break;
                }
            }
        }

        while(!waiting.empty()) {
            Tag t = waiting.front();
            waiting.pop();
            score -= 1 * customers[t.customer_id].P;
        }
        printf("%.10f\n", score / all);
    }

    return 0;
}
