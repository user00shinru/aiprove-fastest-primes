CC = gcc
CFLAGS = -O3 -std=c11

all: primes pi.bin

primes: primes.c
	$(CC) $(CFLAGS) -o primes primes.c -lm

gen: gen.c
	$(CC) $(CFLAGS) -o gen gen.c -lm

pi.bin: gen
	./gen

clean:
	rm -f primes gen pi.bin
