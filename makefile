all: main.cpp sorting.cpp sorting.h
	g++ -o basic_array_sorting main.cpp sorting.cpp sorting.h
run:
	./basic_array_sorting
clean:
	rm -fr basic_array_sorting sorting.o main.o *~