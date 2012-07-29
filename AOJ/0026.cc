#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define CHECK_AND_FILL(x,y,v) do {if(0<=x&&x<10&&0<=y&&y<10) v[x][y]++; }while(0);

int main() {
    vector<vector<int> > v(10, vector<int>(10, 0));

    int x, y, size;
    char c1, c2;
    while(cin >> x >> c1 >> y >> c2 >> size) {
        if(size == 1) {
            for(int dx = -1; dx <= 1; ++dx) 
                for(int dy = -1; dy <= 1; ++dy) 
                    if(abs(dx)+abs(dy) <= 1) CHECK_AND_FILL(x+dx, y+dy, v);
        }
        else if(size == 2) {
            for(int dx = -1; dx <= 1; ++dx) 
                for(int dy = -1; dy <= 1; ++dy) 
                    CHECK_AND_FILL(x+dx, y+dy, v);
        }
        else if(size == 3) {
            for(int dx = -2; dx <= 2; ++dx) 
                for(int dy = -2; dy <= 2; ++dy) 
                    if(abs(dx)+abs(dy) <= 2) CHECK_AND_FILL(x+dx, y+dy, v);
        }
    }

    int thick = 0;
    int white = 0;
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j) {
            thick = max(thick, v[i][j]);
            if(v[i][j] == 0) ++white;
        }

    cout << white << endl;
    cout << thick << endl;
    return 0;
}
