// Elapsed date from 1/1/0
// Runs in O(1)
int cal(int y, int m, int d) {
    static const int DAYS[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ans = 0;
    ans += (y-1) * 365 + (y-1)/4 - (y-1)/100 + (y-1)/400;
    for(int i = 1; i < m; ++i) ans += DAYS[i];
    if(m > 2 && (y%4 == 0 && (y%100 != 0 || y%400 == 0))) ++ans;
    ans += d;
    return ans;
}

// Used in:
// AOJ0125
