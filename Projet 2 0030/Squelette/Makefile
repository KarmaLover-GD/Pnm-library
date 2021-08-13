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
EXEC=lsfr
MODULES=main.c lsfr.c
OBJECTS=main.o lsfr.o

## Rules

all: $(EXEC)

lsfr: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS) $(GDBFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS) $(GDBFLAGS)

lsfr.o: lsfr.c
	$(CC) -c lsfr.c -o lsfr.o $(CFLAGS) $(GDBFLAGS)

clean:
	rm -f *.o $(EXEC) *~

