#!/bin/bash
if [ "$1" == "par" ]
then
	> parallel_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> parallel_vals.txt
		./main_parallel.app $i >> parallel_vals.txt
	done
	python grapher.py par
elif [ "$1" == "seq" ]
then
	> main_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> main_vals.txt
		./main.app $i >> main_vals.txt
	done
	python grapher.py seq
elif [ $1 == "both" ]
then
	> parallel_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> parallel_vals.txt
		./main_parallel.app $i >> parallel_vals.txt
	done

	> main_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> main_vals.txt
		./main.app $i >> main_vals.txt
	done
	python grapher.py both
else
	echo "Usage: ./autogen.sh [seq|par]"
fi
