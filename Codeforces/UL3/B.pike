int main() {
	int N = (int)Stdio.stdin->gets();
	array(int) list = (array(int))(Stdio.stdin->gets() / ",");
	list = sort(map(list, abs));

	int ok = 1;
	if(list[0] == 0) {
		ok = 0;
	}
	else {
		for(int i = 0; i < N; ++i) {
			for(int j = i+1; j < N; ++j) {
				if(list[j] % list[i] != 0) {
					ok = 0;
				}
			}
		}
	}

	write((ok ? "" : "NOT ") + "FRIENDS\n");
	return 0;
}
