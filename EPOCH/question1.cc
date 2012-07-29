#include <set>
#include <cstring>
#include <cstdio>

using namespace std;

struct Tag {
    unsigned flags[32];
    void set(int n) {
        flags[n/32] |= 1<<(n%32);
    }

    bool operator < (const Tag &other) const {
        for(int i = 0; i < 32; ++i) {
            if(flags[i] != other.flags[i]) return flags[i] < other.flags[i];
        }
        return false;
    }

    bool operator == (const Tag &other) const {
        for(int i = 0; i < 32; ++i) {
            if(flags[i] == other.flags[i]) return false;
        }
        return true;
    }

    Tag() {
        memset(flags, 0, sizeof(flags));
    }
};

int main() {
    set<Tag> pattern;

    int N;
    scanf("%d", &N);

    while(N--) {
        Tag t;
        while(true) {
            int i;
            scanf("%d", &i);
            if(i == -1) break;
            t.set(i);
        }
        pattern.insert(t);
    }
    printf("%d\n", pattern.size());
    return 0;
}

