all:
	gcc -g -Wall -Wextra -pedantic -o target.exe *.c -I. -lpthread
clean:
	rm -f target.exe
