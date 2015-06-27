#!/bin/bash
if [ "$1" == "par" ]
then
	g++ main_parallel.cpp ray.cpp shading.cpp sphere.cpp vectors.cpp -o main_parallel.app -lglut -lGL -lGLU -lm -fopenmp
	> parallel_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> parallel_vals.txt
		./main_parallel.app $i skip >> parallel_vals.txt
	done
	python grapher.py par
elif [ "$1" == "seq" ]
then
	g++ main.cpp ray.cpp shading.cpp sphere.cpp vectors.cpp -o main.app -lglut -lGL -lGLU -lm
	> main_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> main_vals.txt
		./main.app $i skip >> main_vals.txt
	done
	python grapher.py seq
elif [ "$1" == "both" ]
then
	g++ main_parallel.cpp ray.cpp shading.cpp sphere.cpp vectors.cpp -o main_parallel.app -lglut -lGL -lGLU -lm -fopenmp
	> parallel_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> parallel_vals.txt
		./main_parallel.app $i skip >> parallel_vals.txt
	done

	g++ main.cpp ray.cpp shading.cpp sphere.cpp vectors.cpp -o main.app -lglut -lGL -lGLU -lm
	> main_vals.txt
	for i in 100 200 300 400 500
	do
		echo $(($i * 2)) >> main_vals.txt
		./main.app $i skip >> main_vals.txt
	done
	python grapher.py both
else
	echo "Usage: ./autogen.sh [seq|par|both]"
fi
