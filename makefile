all: 
	gcc utils/*.c main.c -o ghostShell -g -Wall

teste:
	gcc utils/*.c teste.c -o test -g -Wall

clean: 
	rm -f ghostShell
