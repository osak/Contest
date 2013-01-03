#/bin/sh

while true; do
	wget -O - 'http://ipsc.ksp.sk/contests/ipsc2011/real/M/?TIS=91173949657717871140' > prob_m_tmp
	diff prob_m_tmp prob_m > /dev/null
	if [ 0 -ne $? ]; then
		echo "modified!"
		aplay ./mikuxtu.wav
		cp prob_m_tmp prob_m
	fi
	sleep 60
done
