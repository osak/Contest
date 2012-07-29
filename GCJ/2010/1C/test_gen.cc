#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    printf("1\n");
    printf("512 512\n");
    for(int i = 0; i < 512; ++i) {
        for(int j = 0; j < 512/4; ++j) {
            printf("A");
        }
        printf("\n");
    }
    return 0;
}
