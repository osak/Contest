main(i,j,k) {
    char**p=&j+30;
    printf("%p %p\n", k, p);
    puts(p[0]);
    puts(((char**)k)[0]);
}
