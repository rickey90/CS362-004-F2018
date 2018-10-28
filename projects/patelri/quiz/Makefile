CFLAGS= -Wall -fpic -coverage -lm 

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	./testme

all: testme

clean:
	rm -f testme testme.gcov testme.gcda testme.gcno