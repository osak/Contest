#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<vector<int> > v(N, vector<int>(N, INT_MAX));
        for(int i = 0; i < N-1; ++i) {
            for(int j = i+1; j < N; ++j) {
                int d;
                cin >> d;
                v[i][j] = v[j][i] = d;
            }
        }

        vector<vector<int> > ans;
        for(int left = 0; left < N; ++left) {
            for(int right = left+1; right < N; ++right) {
                vector<vector<int> > neighbor(N);
                int cur = left;
                int prev = -1;
                int visit_cnt = 0;
                for(; cur != -1; ++visit_cnt) {
                    //Looped
                    if(neighbor[cur].size()) goto next;

                    int minimum = INT_MAX, second = INT_MAX;
                    int minpos, secondpos;
                    for(int i = 0; i < N; ++i) {
                        if(i == cur) continue;
                        if(v[cur][i] <= minimum) {
                            second = minimum; secondpos = minpos;
                            minimum = v[cur][i]; minpos = i;
                        }
                        else if(v[cur][i] <= second) {
                            second = v[cur][i]; secondpos = i;
                        }
                    }
                    if(cur == left || cur == right) secondpos = -1; //Guard

                    neighbor[cur].push_back(minpos);
                    if(secondpos != -1) neighbor[cur].push_back(secondpos);
                    if(cur != left && prev != minpos && prev != secondpos) goto next; //Inconsistent
                    int next = (prev != minpos) ? minpos : secondpos;
                    prev = cur;
                    cur = next;
                }
                if(visit_cnt != N) goto next;

                {
                    //Check consistency
                    cur = left;
                    vector<int> checked(N, 0);
                    vector<int> dv;
                    int sum = 0;
                    while(cur != right) {
                        if(checked[cur]) goto next;
                        int next = !checked[neighbor[cur][0]] ? neighbor[cur][0] : neighbor[cur][1];
                        dv.push_back(v[cur][next]);
                        sum += v[cur][next];
                        checked[cur] = 1;
                        cur = next;
                    }
                    vector<int> rev = dv;
                    cout << "come" << endl;
                    if(sum != v[left][right]) goto next; //Inconsistent
                    ans.push_back(dv);
                    reverse(rev.begin(), rev.end());
                    if(rev != dv) ans.push_back(rev);
                }
next:
                ;
            }
        }

        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); ++i) {
            for(int j = 0; j < ans[i].size(); ++j) {
                if(j != 0) cout << ' ';
                cout << ans[i][j];
            }
            cout << endl;
        }
        cout << "-----" << endl;
    }

    return 0;
}
