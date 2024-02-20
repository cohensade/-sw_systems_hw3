all: StrList

StrList: main.o lib.a
	gcc -Wall -g main.o lib.a -o StrList

main.o: main.c StrList.h
	gcc -Wall -g -c main.c

StrList.o: StrList.c StrList.h
	gcc -Wall -g -c StrList.c

lib.a: StrList.o
	ar -rcs lib.a StrList.o

clean:
	rm -f *.o *.a StrList 

.PHONY: all clean