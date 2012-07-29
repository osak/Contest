int main() {
	int N = (int)Stdio.stdin->gets();
	string s1 = Stdio.stdin->gets();
	string s2 = Stdio.stdin->gets();
	
	int l1 = sizeof(s1);
	int l2 = sizeof(s2);
	
	int i;
	for(i = 0; i < l1 && i < l2; ++i) {
		if(s1[i] != s2[i]) break;
	}

	int turn = 0;
	turn += l1 - i;
	turn += l2 - i;

	write((turn <= N ? "Yes" : "No") + "\n");
	return 0;
}
