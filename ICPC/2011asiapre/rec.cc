int rec(int a) {
    rec(a+1);
}

int main() {
    rec(0);
}
