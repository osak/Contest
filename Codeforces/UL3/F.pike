array(int) mul(array(int) a, int b) {
	int len = sizeof(a);
	array(int) ans = a + ({});
	for(int i = len-1; i > 0; --i) ans[i] = ans[i-1];
	ans[0] = 0;
	for(int i = 0; i < len; ++i) ans[i] += a[i]*b;
	return ans;
}

int main() {
	int N = (int)Stdio.stdin->gets();
	array(int) list = ({});
	for(int i = 0; i < N+1; ++i) list = Array.push(list, (int)0);

	list[0] = 1;
	for(int i = 0; i < N; ++i) {
		int b = (int)Stdio.stdin->gets();
		list = mul(list, b);
	}

	int first = 1;
	for(int i = N; i >= 0; --i) {
		if(list[i] != 0) {
			if(list[i] < 0) write("-");
			else if(!first) write("+");
		}
		if(i == 0) {
			if(list[i] != 0) write(abs(list[i]) + "");
		}
		else if(list[i] != 0) {
			if(abs(list[i]) != 1) write(abs(list[i]) + "*");
			write("X");
			if(i > 1) write("^" + i);
		}
		first = 0;
	}
	write("\n");

	return 0;
}
