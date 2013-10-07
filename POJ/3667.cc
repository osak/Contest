//Name: Hotel
//Level: 4
//Category: データ構造,Data Structure,平方分割,Square Decomposition
//Note:

/*
 * 部屋を平方分割して保持し、各バケットについて
 * ・バケット内の部屋が全て空き
 * ・バケット内の部屋が全て使用中
 * ・バケット内の部屋が部分的に使用中
 * の状態と、
 * ・先頭の連続空き部屋数
 * ・末尾の連続空き部屋数
 * ・最大連続空き部屋数
 * をメンテナンスできるようにしておく。
 * この構造の上で連続したD部屋を確保するためには、
 * ・あるバケット内部でD部屋確保する
 * ・バケットをまたいでD部屋確保する
 * の2つのパターンを調べればよい。
 * 内部の部屋を全て調べるバケット数は、前者では1、後者では高々2で抑えられる。
 *
 * オーダーはO(M * sqrt(N))。
 */
#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int PARTITION = 224;
const int MAX_ROOMS = PARTITION * PARTITION;
enum State {
    EMPTY,
    FULL,
    PARTIAL
};

int N;
bool rooms[MAX_ROOMS];
State part_state[PARTITION];
int max_seq[PARTITION];
int head[PARTITION], tail[PARTITION];

void recalculate(int part) {
    const int start = PARTITION*part;
    const int end = PARTITION*(part+1);

    head[part] = tail[part] = max_seq[part] = 0;
    // Head
    for(int i = start; i < end; ++i) {
        if(rooms[i]) break;
        ++head[part];
    }
    // Tail
    for(int i = end-1; i >= start; --i) {
        if(rooms[i]) break;
        ++tail[part];
    }
    // Maxseq
    int seq = 0;
    for(int i = start; i < end; ++i) {
        if(rooms[i]) {
            seq = 0;
        } else {
            ++seq;
        }
        max_seq[part] = max(max_seq[part], seq);
    }

    // Change state
    if(max_seq[part] == 0) part_state[part] = FULL;
    else if(max_seq[part] == end-start) part_state[part] = EMPTY;
    else part_state[part] = PARTIAL;
}

void fillup(int part, State state) {
    const int start = PARTITION * part;
    const int end = min(N, PARTITION * (part+1));
    for(int i = start; i < end; ++i) rooms[i] = (state == FULL);
}

void prepare(int part) {
    if(part_state[part] != PARTIAL) fillup(part, part_state[part]);
}

int fill_tail(int part) {
    prepare(part);
    int end = PARTITION*(part+1);
    int cnt = 0;
    for(int i = end-1; i >= 0; --i) {
        if(rooms[i]) break;
        rooms[i] = true;
        ++cnt;
    }
    assert(tail[part] == cnt);
    recalculate(part);
    return cnt;
}

void fill_head(int part, int cnt) {
    prepare(part);
    int start = PARTITION*part;
    for(int i = start; i < start+cnt; ++i) {
        rooms[i] = true;
    }
    recalculate(part);
}

int main() {
    int M;
    scanf("%d %d", &N, &M);
    const int LIM = (N+PARTITION-1) / PARTITION;
    for(int i = N; i < MAX_ROOMS; ++i) {
        rooms[i] = true;
    }
    for(int i = 0; i < PARTITION; ++i) {
        recalculate(i);
    }

    while(M--) {
        int cmd;
        scanf("%d", &cmd);
        if(cmd == 1) { // Check in
            int d;
            scanf("%d", &d);
            int part = 0;
            while(true) {
                if(part >= LIM) {
                    puts("0");
                    break;
                }
                if(part_state[part] == FULL) {
                    ++part;
                    continue;
                }
                //printf("part: %d %d %d\n", part, part_state[part], max_seq[part]);
                // Insert in here
                if(max_seq[part] >= d) {
                    const int start = PARTITION * part;
                    const int end = PARTITION * (part+1);
                    prepare(part);
                    int seq = 0;
                    int i;
                    for(i = start; i < end; ++i) {
                        if(rooms[i]) {
                            seq = 0;
                        } else {
                            ++seq;
                            if(seq == d) break;
                        }
                    }
                    for(int j = 0; j < d; ++j) {
                        rooms[i] = true;
                        --i;
                    }
                    ++i;
                    printf("%d\n", i+1);
                    recalculate(part);
                    break;
                }

                // Insert into some consecutive partitions
                int cur = part;
                // Head
                int acc = 0;
                if(part_state[cur] == EMPTY) {
                    acc += PARTITION;
                } else if(part_state[cur] == PARTIAL) {
                    acc += tail[cur];
                }
                ++cur;

                // Mid
                while(cur < LIM && part_state[cur] == EMPTY) {
                    acc += PARTITION;
                    ++cur;
                }

                // Tail
                if(cur < LIM && part_state[cur] == PARTIAL) {
                    acc += head[cur];
                }

                if(acc >= d) {
                    int i = part;
                    int rem = d;
                    int start = PARTITION * part;
                    //printf("%d %d\n", part, cur);
                    if(part_state[i] == PARTIAL) {
                        int t = fill_tail(i);
                        start = PARTITION * (part+1) - t;
                        rem -= t;
                        ++i;
                    }
                    for(; rem >= PARTITION && i < cur; ++i) {
                        part_state[i] = FULL;
                        rem -= PARTITION;
                    }
                    if(rem) {
                        fill_head(i, rem);
                    }
                    printf("%d\n", start+1);
                    break;
                } else {
                    part = cur;
                }
            }
        } else { // Check out
            int x, d;
            scanf("%d %d", &x, &d);
            --x;
            const int start = x / PARTITION;
            int rem = d;

            // Check out first partition
            const int next = (start+1)*PARTITION;
            prepare(start);
            for(int i = x; rem && i < next; ++i) {
                rooms[i] = false;
                --rem;
            }
            recalculate(start);

            // Check out remaining partition
            for(int i = start+1; rem; ++i) {
                if(rem >= PARTITION) {
                    part_state[i] = EMPTY;
                    rem -= PARTITION;
                } else {
                    prepare(i);
                    for(int j = PARTITION*i; rem; ++j) {
                        rooms[j] = false;
                        --rem;
                    }
                    recalculate(i);
                }
            }
        }
    }
    return 0;
}
