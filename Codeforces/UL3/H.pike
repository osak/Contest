string get(array(array(string)) field, int row, int col) {
    if(row < 0 || 10 <= row) return "0";
    if(col < 0 || 10 <= col) return "0";
    return field[row][col];
}

int check(array(array(string)) field, int row, int col) {
    return get(field, row+1, col+1) == "0" &&
           get(field, row+1, col-1) == "0" &&
           get(field, row-1, col+1) == "0" &&
           get(field, row-1, col-1) == "0";
}

int main() {
    int N = (int)Stdio.stdin->gets();
    while(N--) {
        array(array(string)) field = allocate(10);
        for(int i = 0; i < 10; ++i) {
            field[i] = Stdio.stdin->gets() / "";
        }

        array(int) count = allocate(5);
        int ok = 1;
        for(int row = 0; row < 10; ++row) {
            for(int col = 0; col < 10; ++col) {
                if(get(field, row, col) == "*") {
                    int width = 1;
                    int height = 1;
                    ok &= check(field, row, col);
                    field[row][col] = "+";

                    //Horizontal
                    while(get(field, row, col+width) == "*") {
                        ok &= check(field, row, col+width);
                        field[row][col+width] = "+";
                        width++;
                    }
                    if(width == 1) {
                        //Vertical
                        while(get(field, row+height, col) == "*") {
                            ok &= check(field, row+height, col);
                            field[row+height][col] = "+";
                            height++;
                        }
                    }
                    int size = max(width, height);
                    if(size <= 4) count[size]++;
                    else ok = 0;
                }
            }
        }
        if(ok && count[1] == 4 && count[2] == 3 && count[3] == 2 && count[4] == 1) write("YES\n");
        else write("NO\n");

        if(N) Stdio.stdin->gets();
    }
    return 0;
}
