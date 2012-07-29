#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int scores[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

struct Driver {
    string name;
    int score;
    vector<int> rankcnt;

    Driver() {
        score = 0;
        rankcnt.resize(60);
        fill(rankcnt.begin(), rankcnt.end(), 0);
    }
};

int main() {
    map<string, Driver*> table;

    int t;
    cin >> t;
    int maxscore = 0;
    int max_firstplace = 0;
    for(int i = 0; i < t; ++i) {
        int n;
        cin >> n;
        for(int rank = 1; rank <= n; ++rank) {
            string str;
            cin >> str;
            Driver *d = table[str];
            if(d == NULL) {
                d = table[str] = new Driver;
                d->name = str;
            }
            if(rank <= 10) {
                d->score += scores[rank-1];
                maxscore = max(maxscore, d->score);
            }
            ++d->rankcnt[rank];
            if(rank == 1) {
                max_firstplace = max(max_firstplace, d->rankcnt[rank]);
            }
        }
    }
    vector<Driver*> old_winners;
    for(map<string,Driver*>::iterator it = table.begin(); it != table.end(); ++it) {
        Driver *d = it->second;
        if(d->score == maxscore) {
            old_winners.push_back(d);
        }
    }
    int cmprank = 1;
    while(old_winners.size() > 1) {
        vector<Driver*> tmp;
        int maxcnt = 0;
        for(int i = 0; i < old_winners.size(); ++i) {
            maxcnt = max(maxcnt, old_winners[i]->rankcnt[cmprank]);
        }
        for(int i = 0; i < old_winners.size(); ++i) {
            if(old_winners[i]->rankcnt[cmprank] == maxcnt) tmp.push_back(old_winners[i]);
        }
        old_winners = tmp;
        ++cmprank;
    }
    cout << old_winners[0]->name << endl;

    vector<Driver*> new_winners;
    maxscore = 0;
    for(map<string,Driver*>::iterator it = table.begin(); it != table.end(); ++it) {
        Driver *d = it->second;
        if(d->rankcnt[1] == max_firstplace) {
            new_winners.push_back(d);
            maxscore = max(maxscore, d->score);
        }
    }
    if(new_winners.size() > 1) {
        vector<Driver*> tmp;
        for(int i = 0; i < new_winners.size(); ++i) {
            Driver *d = new_winners[i];
            if(d->score == maxscore) {
                tmp.push_back(d);
            }
        }
        new_winners = tmp;
    }

    cmprank = 1;
    while(new_winners.size() > 1) {
        vector<Driver*> tmp;
        int maxcnt = 0;
        for(int i = 0; i < new_winners.size(); ++i) {
            maxcnt = max(maxcnt, new_winners[i]->rankcnt[cmprank]);
        }
        for(int i = 0; i < new_winners.size(); ++i) {
            if(new_winners[i]->rankcnt[cmprank] == maxcnt) tmp.push_back(new_winners[i]);
        }
        new_winners = tmp;
        ++cmprank;
    }
    cout << new_winners[0]->name << endl;

    return 0;
}
