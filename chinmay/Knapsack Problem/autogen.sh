#!/bin/bash
if [ "$1" == "seq" ]
then
	g++ knapsack_seq.cpp -o Seq
	> seq_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> seq_vals.txt
		./Seq $i < input >> seq_vals.txt
	done
	python grapher.py seq


elif [ "$1" == "par" ]
then
	g++ knapsack_par.cpp -fopenmp -o Par
	> par4_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par4_vals.txt
		./Par $i 4 < input >> par4_vals.txt
	done

	> par8_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par8_vals.txt
		./Par $i 8 < input >> par8_vals.txt
	done

	> par12_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par12_vals.txt
		./Par $i 12 < input >> par12_vals.txt
	done

	> par16_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par16_vals.txt
		./Par $i 16 < input >> par16_vals.txt
	done

	python grapher.py par

elif [ "$1" == "both" ]
then
	g++ knapsack_seq.cpp -o Seq
	> seq_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> seq_vals.txt
		./Seq $i < input >> seq_vals.txt
	done

	g++ knapsack_par.cpp -fopenmp -o Par
	> par4_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par4_vals.txt
		./Par $i 4 < input >> par4_vals.txt
	done

	> par8_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par8_vals.txt
		./Par $i 8 < input >> par8_vals.txt
	done

	> par12_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par12_vals.txt
		./Par $i 12 < input >> par12_vals.txt
	done

	> par16_vals.txt
	for i in 7 13 17 20 24 26
	do
		echo $(($i)) >> par16_vals.txt
		./Par $i 16 < input >> par16_vals.txt
	done
	
	python grapher.py both

else
	echo "Usage: ./autogen.sh [seq|par]"
fi