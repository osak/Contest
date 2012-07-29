//Name: Soccer
//Level: 2
//Category: データ処理
//Note:
#include <iostream>
#include <algorithm>

using namespace std;

struct Team {
    int id;
    int score;

    Team() {}
    bool operator <(const Team &other) const {
        return other.score < score; // Reversed order
    }
} teams[100];
int rank_of[100];

int main() {
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        teams[i].id = i;
    }
    for(int i = 0; i < N*(N-1)/2; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b;
        if(c == d) {
            teams[a].score += 1;
            teams[b].score += 1;
        }
        else if(c < d) {
            teams[b].score += 3;
        }
        else if(c > d) {
            teams[a].score += 3;
        }
    }

    sort(teams, teams+N);
    int rank = 1;
    int prevscore = teams[0].score;
    for(int i = 0; i < N; ++i) {
        if(teams[i].score < prevscore) rank = i+1;
        rank_of[teams[i].id] = rank;
        prevscore = teams[i].score;
    }
    for(int i = 0; i < N; ++i) {
        cout << rank_of[i] << endl;
    }
    return 0;
}
