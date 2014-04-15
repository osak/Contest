#!/usr/bin/env ruby

TC_STR = <<TC_STR
1 	tourist 	3611
2 	Petr 	3602
2   rng_58 3468
3 	tomek 	3407
4 	Egor 	3350
5 	peter50216 	3301
6 	Burunduk1 	3210
7 	bmerry 	3202
8 	ACRush 	3186
9 	lyrically 	3177
9 	hos.lyric 	3177
10 	semiexp 	3167
11 	scott_wu 	3114
12 	[[iwi]] 	3100
13 	niyaznigmatul 	3099
14 	dzhulgakov 	3092
15 	sdya 	3079
16 	wata 	3075
17 	UdH-WiNGeR 	3065
18 	cgy4ever 	3023
19 	WJMZBMR 	3017
20 	marek.cygan 	3010
21 	Vasyl[alphacom] 	2985
22 	rejudge 	2979
23 	nika 	2973
24 	gawry 	2966
25 	mikhailOK 	2963
26 	kalinov 	2962
27 	kuniavski 	2936
28 	yeputons 	2928
29 	andrewzta 	2926
30 	RAVEman 	2906
TC_STR

CF_STR = <<CF_STR
1 	tourist 	90 	3186
2 	rng_58 	86 	2795
3 	yeputons 	69 	2773
4 	0O0o00OO0Oo0o0Oo 	44 	2718
5 	Petr 	67 	2717
6 	scott_wu 	40 	2710
7 	PavelKunyavskiy 	102 	2681
8 	meret 	17 	2655
9 	niyaznigmatul 	81 	2642
10 	vepifanov 	56 	2636
11 	ivan.metelsky 	19 	2623
12 	WJMZBMR 	52 	2617
13 	Egor 	123 	2614
14 	SergeyRogulenko 	38 	2601
15 	RAD 	51 	2590
16 	cerealguy 	36 	2587
17 	KADR 	113 	2564
18 	Dmitry_Egorov 	99 	2558
18 	ACMonster 	15 	2558
20 	dzhulgakov 	32 	2552
21 	OoO000oOOOoOooOo 	41 	2549
22 	sillycross 	17 	2540
23 	lyrically 	61 	2538
23 	hos.lyric 	61 	2538
24 	bmerry 	19 	2537
25 	TankEngineer 	27 	2529
26 	kelvin 	60 	2528
26 	louise 	11 	2528
28 	Endagorion 	62 	2523
29 	ainu7 	27 	2522
30 	glassices 	24 	2520 
CF_STR

tc = TC_STR.each_line.map(&:split).reduce({}){|acc,arr| acc[arr[1].downcase] = arr[2].to_i; acc}
cf = CF_STR.each_line.map(&:split).reduce({}){|acc,arr| acc[arr[1].downcase] = arr[-1].to_i; acc}

name = gets.chomp.downcase
puts (tc[name] || 0) + (cf[name] || 0)
