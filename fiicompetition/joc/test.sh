for NUM in $(seq 1 200);
do
	echo $NUM
	echo Gentest
	g++ gentest.cpp
	./a.out
	echo main
	g++ main.cpp -w
	./a.out
	echo brute
	g++ joc_brute.cpp
	./a.out
done
