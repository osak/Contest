#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

map<string, bool> visited;
void merge(const string &grp, map<string, vector<string> > &m, set<string> &members) {
    if(visited[grp]) return;

    const vector<string> &v = m[grp];
    for(int i = 0; i < v.size(); ++i) {
        string name = v[i];
        if(m.count(name) > 0) {
            merge(name, m, members);
        }
        else {
            members.insert(name);
        }
    }
    visited[grp] = true;
}

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        map<string, vector<string> > m;
        string first;
        for(int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            int colon = s.find(":");
            string group = s.substr(0, colon);
            string members = s.substr(colon+1);
            members.erase(members.size()-1);
            for(int j = 0; j < members.size(); ++j) {
                if(members[j] == ',') members[j] = ' ';
            }

            istringstream is(members);
            string name;
            vector<string> &v = m[group];
            while(is >> name) {
                v.push_back(name);
            }
            if(i == 0) first = group;
        }

        visited.clear();
        set<string> members;
        merge(first, m, members);
        cout << members.size() << endl;
    }

    return 0;
}
