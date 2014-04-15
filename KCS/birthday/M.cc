#include <cstdlib>

int main() {
    unsigned char *p = (unsigned char*)malloc(512*1024*1024);
    p[0] = 1;
    p[512*1024*1024-1] = 1;
    return 0;
}
