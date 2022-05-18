main:
	echo "Main target"
compile: main.cpp
	g++ -c TSP.cpp
	g++ TSP.o -o result
clean:
	rm *.o
workresult:
	./result
