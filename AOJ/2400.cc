#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Team {
    int number, correct, penalty;

    bool operator <(const Team &t) const {
        if(correct != t.correct) return correct > t.correct;
        if(penalty != t.penalty) return penalty < t.penalty;
        return number < t.number;
    }
};

int main() {
    while(true) {
        int T, P, R;
        cin >> T >> P >> R;
        if(!T && !P && !R) break;

        vector<Team> teams(T);
        for(int i = 0; i < T; ++i) teams[i].number = i+1;
        vector<vector<int> > wa_count(T, vector<int>(P, 0));

        for(int i = 0; i < R; ++i) {
            int tid, pid, tim;
            string message;
            cin >> tid >> pid >> tim >> message;
            --tid; --pid;
            if(message == "CORRECT") {
                teams[tid].correct++;
                teams[tid].penalty += tim + wa_count[tid][pid] * 1200;
            }
            else {
                wa_count[tid][pid]++;
            }
        }

        sort(teams.begin(), teams.end());
        for(int i = 0; i < teams.size(); ++i) {
            cout << teams[i].number << ' ' << teams[i].correct << ' ' << teams[i].penalty << endl;
        }
    }

    return 0;
}
