all:sum-nbo

sum-nbo:main.cpp
	g++ -g -o sum-nbo main.cpp

clean:
	rm -f sum-nbo
	rm -f *.o
