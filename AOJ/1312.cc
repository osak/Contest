#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

int decode(char c) {
    if('A' <= c && c <= 'Z') return c-'A';
    if('a' <= c && c <= 'z') return 26+c-'a';
    if('0' <= c && c <= '9') return 52+c-'0';
    if(c == '+') return 62;
    if(c == '/') return 63;
    assert(false);
    return 0;
}

int main() {
    while(true) {
        int W, H, P;
        cin >> W >> H >> P;
        if(!W && !H && !P) break;

        vector<vector<unsigned> > img(H, vector<unsigned>((W+31)/32));
        for(
