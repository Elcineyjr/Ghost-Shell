all: 
	gcc utils/*.c *.c -o ghostShell -g -Wall

clean: 
	rm -f ghostShell