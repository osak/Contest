#define B(x) x; printf("B(" #x ")");
#define A(x) printf("A(" #x ")"); x;
main(){B(printf("#define B(x) x; printf(\"  B(\" #x \")\");\n#define A(x) printf(\"  A(\" #x \")\\n\"); x;\nmain(){"))A(printf("}"))}