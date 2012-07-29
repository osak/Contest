#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Team {
    int number;
    int corrects;
    int penalty;

    Team() : corrects(0), penalty(0) {}
    bool operator <(const Team &other) const {
        if(corrects != other.corrects) return corrects > other.corrects;
        else if(penalty != other.penalty) return penalty < other.penalty;
        return number < other.number;
    }
};

int main() {
    while(true) {
        int T, P, R;
        cin >> T >> P >> R;
        if(!T && !P && !R) break;

        vector<Team> teams(T);
        vector<vector<int> > wa_cnt(T, vector<int>(P, 0));
        for(int i = 0; i < T; ++i) {
            teams[i].number = i+1;
        }
        for(int i = 0; i < R; ++i) {
            int tid, pid, t;
            string message;
            cin >> tid >> pid >> t >> message;
            tid--; pid--;
            if(message == "WRONG") {
                wa_cnt[tid][pid]++;
            }
            else if(message == "CORRECT") {
                teams[tid].corrects++;
                teams[tid].penalty += t + 1200*wa_cnt[tid][pid];
            }
        }
        sort(teams.begin(), teams.end());

        for(int i = 0; i < T; ++i) {
            cout << teams[i].number << ' ' << teams[i].corrects << ' ' << teams[i].penalty << endl;
        }
    }

    return 0;
}
