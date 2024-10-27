# FO4 Makefile

fo4: main.c fo4.c util.c
	gcc -o fo4 main.c fo4.c util.c

