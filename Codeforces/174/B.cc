#include <iostream>
#include <vector>

using namespace std;

struct Tag {
    bool visited;
    long long value;

    Tag() : visited(false), value(0) {}
};

int N;
int as[200002];
Tag memo[200002];

long long dfs(int x) {
    if(!memo[x].visited) {
        memo[x].visited = true;
        memo[x].value = -1;
        const int step2 = x + as[x];
        //cout << x << " --step2-> " << step2 << endl;
        if(step2 > N) {
            return memo[x].value = as[x];
        }
        const int step3 = step2 - as[step2];
        //cout << x << " --step3-> " << step3 << endl;
        if(step3 <= 0) {
            return memo[x].value = static_cast<long long>(as[x]) + as[step2];
        }
        const long long ret = dfs(step3);
        if(ret == -1) return -1;
        memo[x].value = static_cast<long long>(as[x]) + as[step2] + ret;
    }
    return memo[x].value;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> as[i+2];
    }

    for(int i = 1; i < N; ++i) {
        as[1] = i;
        memo[1].visited = false;
        cout << dfs(1) << endl;
    }
    return 0;
}
