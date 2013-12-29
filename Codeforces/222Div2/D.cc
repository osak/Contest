//Name: Prepare for the Contest
//Level: 3
//Category: 二分探索,貪欲
//Note:

/**
 * 日数が長ければ長いほどコストは減らすことができるので、二分探索できる。
 *
 * 日数をDに決めたとき、1人に割り当てられるバグの数はD個以下となる。
 * 生徒に割り当てられる区間は全て0から始まっていて終点のみが違うので、
 * 重いバグから順に割り当てていけばよい。
 * このとき、一番コストの安い人から順に、D個ずつ貪欲に割り当てていくことで
 * 最小コストを達成できる。
 *
 * オーダーはO(M logM log N)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

bool solve() {
    int N, M, S;
    if(!(cin >> N >> M >> S)) return false;
    if(!N && !M && !S) return false;

    vector<pair<int,int>> bugs; // (complexity, index)
    vector<pair<pair<int,int>,int>> students(N); // (ability, cost, index)
    for(int i = 0; i < M; ++i) {
        int b;
        cin >> b;
        bugs.push_back(make_pair(b, i));
    }
    for(int i = 0; i < N; ++i) {
        cin >> students[i].first.first;
    }
    for(int i = 0; i < N; ++i) {
        cin >> students[i].first.second;
        students[i].second = i;
    }
    sort(bugs.begin(), bugs.end());
    reverse(bugs.begin(), bugs.end());
    sort(students.begin(), students.end());
    reverse(students.begin(), students.end());
    if(students[0].first.first < bugs[0].first) {
        cout << "NO" << endl;
        return true;
    }

    int left = 0, right = 2*M;
    vector<int> ans(M, 0);
    vector<int> schedule(M, 0);
    vector<int> worked(N, 0);
    bool found = false;
    while(left+1 < right) {
        //cout << left << ' ' << right << endl;
        const int lim = (left+right) / 2;
        fill(worked.begin(), worked.end(), 0);

        auto sit = students.begin();
        priority_queue<pair<int,int>> q; // (-cost, index)
        bool ok = true;
        long long cost = 0;
        int cur = -1;
        for(auto bug : bugs) {
            //cout << "bug " << bug.first << endl;
            if(cur == -1 || worked[cur] >= lim) {
                while(sit != students.end() && sit->first.first >= bug.first) {
                    q.push(make_pair(-sit->first.second, sit->second));
                    ++sit;
                }
                if(q.empty()) {
                    ok = false;
                    break;
                }
                //cout << "top " << q.top().second << endl;
                cur = q.top().second;
                cost += -q.top().first;
                //cout << -q.top().first << ' ' << q.top().second << endl;
                if(cost > S) {
                    ok = false;
                    break;
                }
                q.pop();
            }
            ++worked[cur];
            schedule[bug.second] = cur;
        }
        if(ok && cost <= S) {
            right = lim;
            ans = schedule;
            /*
            for(int i = 0; i < M; ++i) {
                if(i > 0) cout << ' ';
                cout << ans[i]+1;
            }
            cout << endl;
            */
            found = true;
        } else {
            left = lim;
        }
    }
    if(!found) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(int i = 0; i < M; ++i) {
            if(i > 0) cout << ' ';
            cout << ans[i]+1;
        }
        cout << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
