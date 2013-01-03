#include "animals.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

vector<vector<int> > graph;
vector<bool> removed;
bool is_line;
vector<pair<int,int> > segments;
multiset<int> lengths;

void init(int N, int E[][2])
{
    graph.resize(N);
    is_line = true;
    for(int i = 0; i < N-1; ++i) {
        graph[E[i][0]].push_back(E[i][1]);
        graph[E[i][1]].push_back(E[i][0]);
        if(E[i][0] != i || E[i][1] != i+1) is_line = false;
    }
    removed.resize(N, false);
    if(is_line) {
        segments.push_back(make_pair(0, N-1));
        lengths.insert(N);
    }
}

int dfs(int pos, vector<bool> &used) {
    int res = 1;
    used[pos] = true;
    for(vector<int>::iterator it = graph[pos].begin(); it != graph[pos].end(); ++it) {
        if(removed[*it] || used[*it]) continue;
        res += dfs(*it, used);
    }
    return res;
}

ostream& operator <<(ostream &o, const pair<int,int> &p) {
    return o << '(' << p.first << ',' << p.second << ')';
}

int solve_for_line(int v) {
    int left = 0, right = segments.size();
    while(left < right) {
        int center = (left+right)/2;
        if(segments[center].first <= v && v <= segments[center].second) {
            left = right = center;
            break;
        }

        if(segments[center].first < v) {
            left = center+1;
        }
        else {
            right = center;
        }
    }

    int i = left;
    //cout << segments[i] << endl;
    lengths.erase(lengths.find(segments[i].second - segments[i].first + 1));

    pair<int,int> leftseg(segments[i].first, v-1); // to be inserted
    pair<int,int> rightseg(v+1, segments[i].second); // to be at segments[i]
    //cout << leftseg << ' ' << rightseg << endl;
    if(rightseg.first > rightseg.second) {
        segments.erase(segments.begin()+i);
    }
    else {
        segments[i] = rightseg;
        lengths.insert(rightseg.second - rightseg.first + 1);
    }

    if(leftseg.second >= leftseg.first) {
        segments.insert(segments.begin()+i, leftseg);
        lengths.insert(leftseg.second - leftseg.first + 1);
    }

    return *lengths.rbegin();
}

int query(int v)
{
    if(is_line) {
        return solve_for_line(v);
    }

    removed[v] = true;
    vector<bool> used(graph.size(), false);
    int res = 0;
    for(int i = 0; i < graph.size(); ++i) {
        if(removed[i] || used[i]) continue;
        res = max(res, dfs(i, used));
    }

    return res;
}
