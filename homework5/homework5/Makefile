source: main.o header_definitions.o
	g++ -o source main.o header_definitions.o

main.o: main.cpp
	g++ -c main.cpp
	
header_definitions.o: header_definitions.cpp header.h
	g++ -c header_definitions.cpp

clean:
	rm source *.o