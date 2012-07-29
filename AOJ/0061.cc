//Name: Rank Checker
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
    return a.second > b.second;
}

int main() {
    vector<pair<int,int> > v;

    int team, score;
    char comma;
    while(cin >> team >> comma >> score) {
        if(!team && !score) break;
        v.push_back(make_pair(team, score));
    }

    sort(v.begin(), v.end(), cmp);

    int N;
    while(cin >> N) {
        int rank = 1;
        for(int i = 0; i < v.size(); ++i) {
            if(i>0 && v[i-1].second != v[i].second) ++rank;
            if(v[i].first == N) break;
        }
        cout << rank << endl;
    }
    return 0;
}
