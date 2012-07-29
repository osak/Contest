int main() {
	int K = (int)Stdio.stdin->gets();
	array(int) list = (array(int))(Stdio.stdin->gets() / " ");

	float sine = sin(K*Math.pi/180);
	float cosine = cos(K*Math.pi/180);

	float x = list[0]*cosine - list[1]*sine;
	float y = list[0]*sine + list[1]*cosine;
	write(x + " " + y + "\n");
	return 0;
}

