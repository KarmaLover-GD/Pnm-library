### 
## Makefile skeleton
## INFO0030: Projet 1
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
GDBFLAGS= -g

# Files
EXEC1=lsfr
EXEC2=basic_cipher
MODULES=main.c lsfr.c
OBJECTS_PNM=main.o lsfr.o
OBJECTS_BASIC_CIPHER=main_basique.o basique.o pnm.o lsfr.o
## Rules

all: $(EXEC1) (EXEC2)
 
lsfr: $(OBJECTS_PNM)
	$(LD) -o $(EXEC1) $(OBJECTS_PNM) $(LDFLAGS) $(GDBFLAGS)

basic_cipher:$(OBJECTS_BASIC_CIPHER)
	$(LD) -o $(EXEC2) $(OBJECTS_BASIC_CIPHER) $(LDFLAGS) $(GDBFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS) $(GDBFLAGS)

lsfr.o: lsfr.c
	$(CC) -c lsfr.c -o lsfr.o $(CFLAGS) $(GDBFLAGS)
basique.o: basique.c
	$(CC) -c basique.c -o basique.o $(CFLAGS) $(GDBFLAGS)

main_basique.o:
	$(CC) -c main_basique.c -o main_basique.o $(CFLAGS) $(GDBFLAGS)



clean:
	rm -f *.o $(EXEC1) *~ $(EXEC2) *~ 

