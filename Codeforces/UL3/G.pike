int main() {
	int N = (int)Stdio.stdin->gets();
	mapping(string:int) dict = ([]);

	for(int i = 0; i < N; ++i) {
		array(string) list = Stdio.stdin->gets() / " ";
		int year = (int)list[1];
		dict += ([ list[0]:year ]);
	}

	int M = (int)Stdio.stdin->gets();
	int curyear = 10000;
	string curname = "";
	for(int i = 0; i < M; ++i) {
		string candidate = Stdio.stdin->gets();
		int year = dict[candidate];
		if(year < curyear) {
			curname = candidate;
			curyear = year;
		}
		else if(year == curyear && candidate > curname) {
			curname = candidate;
			curyear = year;
		}
	}

	write(curname + "\n");
	return 0;
}
