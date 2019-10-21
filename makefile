all: 
	gcc utils/*.c main.c -o ghostShell -g -Wall

clean: 
	rm -f ghostShell
