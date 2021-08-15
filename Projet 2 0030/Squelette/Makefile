###
## Makefile
## INFO0030: Projet 2
## Ouro-Gomma Marzouk s204743
###

#---------------
# Variables
#---------------

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
DOXYGEN=doxygen
OBJ_PNM=main-pnm.o pnm.o
OBJ_BASIC_CIPHER=main-basic_cipher.o basic_cipher.o pnm.o lfsr.o
OBJ_ADVCD_CIPHER=main-advanced_cipher.c advanced_cipher.c basic_cipher.o pnm.o lfsr.o 
OBJ_PNM_TESTS=pnm-test.o pnm.o seatest.o
OBJ_LFSR_TESTS=lfsr-test.o lfsr.o seatest.o
GDBFLAGS = -g

# Files
EXEC1=pnm
EXEC2=basic_cipher
EXEC3=advanced_cipher
EXEC4=pnm_tests
EXEC5=lfsr_tests

#---------------
# Rules
#---------------

all: pnm basic_cipher advanced_cipher lfsr_tests pnm_tests doc

pnm: $(OBJ_PNM)
	$(LD) -o $(EXEC1) $(OBJ_PNM) $(LDFLAGS)

basic_cipher: $(OBJ_BASIC_CIPHER)
	$(LD) -o $(EXEC2) $(OBJ_BASIC_CIPHER) $(LDFLAGS)

advanced_cipher: $(OBJ_ADVCD_CIPHER)
	$(LD) -o $(EXEC3) $(OBJ_ADVCD_CIPHER) $(LDFLAGS) $(GDBFLAGS)

pnm_tests: $(OBJ_PNM_TESTS)
	$(LD) -o $(EXEC4) $(OBJ_PNM_TESTS) $(LDFLAGS)

lfsr_tests: $(OBJ_LFSR_TESTS)
	$(LD) -o $(EXEC5) $(OBJ_LFSR_TESTS) $(LDFLAGS)

main-pnm.o: main-pnm.c
	$(CC) -c main-pnm.c -o main-pnm.o $(CFLAGS)

lfsr.o: lfsr.c
	$(CC) -c lfsr.c -o lfsr.o $(CFLAGS)

lfsr-test.o: lfsr-test.c
	$(CC) -c lfsr-test.c -o lfsr-test.o $(CFLAGS)

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

pnm-test.o: pnm-test.c
	$(CC) -c pnm-test.c -o pnm-test.o $(CFLAGS)

main-basic_cipher.o: main-basic_cipher.c
	$(CC) -c main-basic_cipher.c -o main-basic_cipher.o $(CFLAGS)

basic_cipher.o: basic_cipher.c
	$(CC) -c basic_cipher.c -o basic_cipher.o $(CFLAGS)

#---------------
# Documentation
#---------------

doc:
	$(DOXYGEN) Doxyfile

#---------------
# Utilitaires
#---------------

clean:
	rm -f *.o $(EXEC1) *~ $(EXEC2) *~ $(EXEC3) *~ $(EXEC4) *~ $(EXEC5) *~
