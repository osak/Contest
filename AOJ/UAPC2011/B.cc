#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int ONE_WEEK = 60 * 24 * 7;

struct Tag {
    string name;
    int start;
    bool enable, important; 

    Tag() {}
    Tag(string name, int day, int start) : name(name), enable(true), important(false) {
        int dayh = 60 * 24 * day;
        this->start = dayh + (start/100*60) + start%100;
        this->start %= ONE_WEEK;
    }

    bool operator < (const Tag &other) const {
        if(start == other.start) return name < other.name;
        return start < other.start;
    }
};

int elapse(int a, int b) {
    if(a < b) swap(a, b);
    return (a+ONE_WEEK-b) % ONE_WEEK;
}

istream& operator >> (istream &is, Tag &t) {
    string name;
    int day, start;

    is >> name >> day >> start;
    t = Tag(name, day, start);
    return is;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Tag> progs;
        for(int i = 0; i < N; ++i) {
            Tag t;
            cin >> t;
            progs.push_back(t);
        }
        sort(progs.begin(), progs.end());

        int P;
        cin >> P;
        for(int i = 0; i < P; ++i) {
            string name;
            cin >> name;
            for(int j = 0; j < N; ++j) {
                if(progs[j].name == name) {
                    progs[j].important = true;
                    int s = progs[j].start;
                    for(int k = (j+1)%N; k != j && elapse(progs[k].start, s) < 30; k = (k+1) % N) {
                        progs[k].enable = false;
                    }
                    for(int k = (j+N-1)%N; k != j && elapse(s, progs[k].start) < 30; k = (k+N-1) % N) {
                        progs[k].enable = false;
                    }
                    break;
                }
            }
        }

        //check
        bool ok = true;
        int ans = 0;
        set<int> ans_set;
        for(int i = 0; i < N; ++i) {
            if(progs[i].important && !progs[i].enable) ok = false;
            if(progs[i].important) progs[i].enable = false;
        }
        if(!ok) {
            ans = -1;
        }
        else {
            vector<int> dp(N, 0);
            vector<set<int> > pr(N);
            for(int i = 0; i < N; ++i) {
                if(!progs[i].enable) continue;
                dp[i] = 1;
                for(int j = 0; j < i; ++j) {
                    if(!progs[j].enable) continue;
                    bool valid = true;
                    for(set<int>::iterator it = pr[j].begin(); it != pr[j].end(); ++it) {
                        if(elapse(progs[i].start, progs[*it].start) < 30) {
                            valid = false;
                            break;
                        }
                    }
                    if(valid) {
                        if(dp[i] < dp[j]+1) {
                            dp[i] = dp[j]+1;
                            pr[i] = pr[j];
                        }
                    }
                }
                pr[i].insert(i);
                if(ans < dp[i]) {
                    ans = dp[i];
                    ans_set = pr[i];
                }
            }
        }
        /*
        vector<Tag> v;
        for(set<int>::iterator it = ans_set.begin(); it != ans_set.end(); ++it) {
            //cout << progs[*it].name << ' ' << progs[*it].start << endl;
            v.push_back(progs[*it]);
        }
        sort(v.begin(), v.end());
        for(int i = 0; i < v.size(); ++i) cout << v[i].name << ' ' << v[i].start << endl;
        */
        cout << ans+P << endl;
    }
    return 0;
}
