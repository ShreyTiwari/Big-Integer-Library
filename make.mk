a.out: impl.o client.o
	gcc -Wall -Werror -g impl.o client.o

impl.o: impl.c intal.h
	gcc -c impl.c

client.o: client.c intal.h
	gcc -c client.c
