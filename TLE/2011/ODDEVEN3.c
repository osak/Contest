#define B(x)x"B("#x")"
#define A(x)"A("#x")";x
B(char*s="#define B(x)x\"B(\"#x\")\"\n#define A(x)\"A(\"#x\")\";x\n")A(main(i){while(~scanf("%d",&i))for(i&=1;i<184;i+=2)putchar(s[i]);})