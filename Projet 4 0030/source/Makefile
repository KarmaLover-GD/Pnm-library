CC=gcc
LD=gcc
CFLAGS= --std=c99 --pedantic -Wall -W -Wmissing-prototypes
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`

all: five

five: main.o controleur_five.o vue_five.o modele_five.o 
	$(LD) -o five main.o vue_five.o controleur_five.o modele_five.o  $(LDFLAGS) $(GTKFLAGS)

main.o: main.c vue_five.h controleur_five.h modele_five.h
	$(CC) -c main.c -o main.o $(CFLAGS) $(GTKFLAGS)

controleur_five.o: controleur_five.h controleur_five.c vue_five.h modele_five.h
	$(CC) -c controleur_five.c -o controleur_five.o $(CFLAGS) $(GTKFLAGS)	

vue_five.o: vue_five.h vue_five.c controleur_five.h modele_five.h
	$(CC) -c vue_five.c -o vue_five.o $(CFLAGS) $(GTKFLAGS)

modele_five.o: modele_five.h modele_five.c
	$(CC) -c modele_five.c -o modele_five.o $(CFLAGS) $(GTKFLAGS)
	
doc:
	doxygen Doxyfile

.PHONY: doc

clean:
	rm -f *.o
	rm -f oxo
	clear