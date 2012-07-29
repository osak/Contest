int main() {
	string s = Stdio.stdin->gets();
	array(int) list = (array(int))(s / " ");

	int wc = list[0] / list[2] + (list[0]%list[2] > 0 ? 1 : 0);

	if(wc*wc <= list[1]) write("YES\n");
	else write("NO\n");

	return 0;
}
