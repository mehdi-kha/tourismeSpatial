CC = gcc 

all: test_modele

modele.o: modele.h
TEST.o: modele.h

clean:
	rm *.o

test_modele: TEST.o modele.o
	$(CC) $^ -o $@
