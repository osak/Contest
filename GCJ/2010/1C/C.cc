#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Rect {
    int x, y, e;
    Rect() {}
    Rect(int xx, int yy, int ee) : x(xx), y(yy), e(ee) {}
};

struct Bigint {
    unsigned bytes[128];
};


bool hitrect(const Rect &r1, const Rect &r2) {
    return ((r1.x < r2.x+r2.e) && (r1.x+r1.e > r2.x) && (r1.y < r2.y+r2.e) && (r1.y+r1.e > r2.y));
}

bool check(Bigint x, Bigint y, int size, vector<unsigned> checkmap, vector<unsigned> checkmap_y) {
    unsigned pattern = (1<<size)-1;
    unsigned p = pattern<<(N-x-size);
    unsigned py = (pattern-1)<<(N-x-size);
    bool valid = true;

    for(int dy = 0; dy < size-1; ++dy) {
        if((checkmap[y+dy] & p) != p) {
            valid = false;
            break;
        }
        if((checkmap_y[y+dy] & py) != py) {
            valid = false;
            break;
        }
    }
    if(valid) {
        if(numboards[size]++ == 0) {
            ++sizecnt;
        }
        //For efficiency
        if(size > 1) used.push_back(Rect(x, y, size));
        //printf("%d %d %d\n", x, y, size);
    }
nextx:
    ;
}

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int M, N;
        cin >> M >> N;

        vector<unsigned> field(M);
        for(int i = 0; i < M; ++i) {
            int n;
            scanf("%X", &n);
            field[i] = n;
        }

        vector<unsigned> checkmap(M-1);
        vector<unsigned> checkmap_y(M-1, 0);
        for(int i = 0; i < M-1; ++i) {
            checkmap[i] = field[i] ^ field[i+1];
            checkmap_y[i] = field[i] ^ (field[i]<<1);
        }

        int sizecnt = 0;
        vector<int> numboards(33, 0);
        vector<Rect> used;
        for(int size = min(M, N); size >= 1; --size) {
            unsigned pattern = (1<<size)-1;
            for(int y = 0; y <= M-size; ++y) {
                for(int x = 0; x <= N-size; ++x) {
                    unsigned p = pattern<<(N-x-size);
                    unsigned py = (pattern-1)<<(N-x-size);
                    bool valid = true;

                    for(int i = 0; i < used.size(); ++i) {
                        if(hitrect(Rect(x, y, size), used[i])) goto nextx;
                    }
                    for(int dy = 0; dy < size-1; ++dy) {
                        if((checkmap[y+dy] & p) != p) {
                            valid = false;
                            break;
                        }
                        if((checkmap_y[y+dy] & py) != py) {
                            valid = false;
                            break;
                        }
                    }
                    if(valid) {
                        if(numboards[size]++ == 0) {
                            ++sizecnt;
                        }
                        //For efficiency
                        if(size > 1) used.push_back(Rect(x, y, size));
                        //printf("%d %d %d\n", x, y, size);
                    }
nextx:
                    ;
                }
            }
        }

        printf("Case #%d: %d\n", C, sizecnt);
        for(int i = 32; i >= 1; --i) {
            if(numboards[i] != 0) {
                printf("%d %d\n", i, numboards[i]);
            }
        }
    }
    return 0;
}
