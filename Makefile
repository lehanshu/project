project: main.c supermarket.c
	cc -c main.c -lncurses
	cc -c supermarket.c -lncurses
	
	cc main.o supermarket.o -o project -lncurses
