//Name: BMI
//Level: 1
//Category: やるだけ
//Note:

#include <cstdio>

using namespace std;

int main() {
    int ID;
    double W, H;
    while(scanf("%d,%lf,%lf", &ID, &W, &H) != EOF) {
        if(W/H/H >= 25) printf("%d\n", ID);
    }
    return 0;
}
