source: main.o definition.o
	g++ -o source main.o definition.o

main.o: main.cpp
	g++ -c main.cpp -o main.o
	
definition.o: header_definitions.cpp header.h
	g++ -c header_definitions.cpp -o definition.o

clean:
	rm source *.o