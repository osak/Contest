#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Road {
    int from, to, c;
};

int main() {
    int N;
    cin >> N;

    vector<Road> roads;
    int all_cost = 0;
    for(int i = 0; i < N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        Road r;
        r.from = a;
        r.to = b;
        r.c = c;
        roads.push_back(r);
        all_cost += c;
    }

    int curr = 1;
    int cost = 0;
    vector<bool> used(N, false);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(used[j]) continue;
            if(roads[j].from == curr || roads[j].to == curr) {
                int next = roads[j].from == curr ? roads[j].to : roads[j].from;
                if(roads[j].to == curr) cost += roads[j].c;
                curr = next;
                used[j] = true;
                break;
            }
        }
    }

    cout << min(cost, all_cost-cost) << endl;
    return 0;
}
