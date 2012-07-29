//Name: Videotape
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <cstdio>

using namespace std;

void print_time(int sec) {
    printf("%02d:%02d:%02d\n", sec/3600, sec/60%60, sec%60);
}

int main() {
    while(true) {
        int h, m, s;
        cin >> h >> m >> s;
        if(h == -1 && m == -1 && s == -1) break;

        int rem = 120*60 - (h*3600 + m*60 + s);
        print_time(rem);
        print_time(rem*3);
    }
    return 0;
}
