main.o: main.cc tbuf.h
	g++ -O2 -Wall -o $@ -c $<

tbuf.o: tbuf.cc tbuf.h
	g++ -O2 -Wall -o $@ -c $<

main: tbuf.o main.o
	g++ -o $@ $^

clean:
	rm *.o

fmt: *.cc *.h
	clang-format -i $^

all: fmt main
