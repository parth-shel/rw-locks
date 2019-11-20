all:
	gcc -g -Wall -Wextra -pedantic -o target.out *.c -I. -lpthread
clean:
	rm -f target.out
