//Name: The Number of Area
//Level: 1
//Category: 数論, やるだけ
//Note:

/*
 * 有名な問題。
 * (n-1)本の直線で平面が分割されているところにn本目を引くと、
 * 最大で(n-1)本の直線と交わる→n個の平面を分割する。
 */
#include <iostream>

using namespace std;

int main() {
    for(int n; cin >> n; ) cout << 2 + (2+n)*(n-1)/2 << endl;
    return 0;
}
