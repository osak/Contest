//Name: Sale Reult
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <map>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    map<int,long long> res;
    vector<int> ord;
    for(int i = 0; i < N; ++i) {
        int id, v, c;
        cin >> id >> v >> c;
        res[id] += ((long long)v)*c;
        ord.push_back(id);
    }

    bool exist = false;
    for(int id : ord) {
        if(res[id] >= 1000000) {
            cout << id << endl;
            res[id] = 0;
            exist = true;
        }
    }
    if(!exist) cout << "NA" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
