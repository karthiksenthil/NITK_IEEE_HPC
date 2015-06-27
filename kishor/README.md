Ray Tracer
==========

## Dependencies

* OpenGL environment
* g++
* [matplotlib](http://matplotlib.org/faq/installing_faq.html#install-from-git)

## Building

### Sequential

`$ g++ main.cpp ray.cpp shading.cpp sphere.cpp vectors.cpp -o main.app -lglut -lGL -lGLU -lm`

### Parallel

`$ g++ main_parallel.cpp ray.cpp shading.cpp sphere.cpp vectors.cpp -o main_parallel.app -lglut -lGL -lGLU -lm -fopenmp`

## Running

`$ ./main.app [viewframe_size]`
`$ ./main_parallel.app [viewframe_size]`


## Graph Generation

`$ ./autogen.sh [seq|par]`
