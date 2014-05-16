#DIRSDL=/users/prog1a/C/librairie/2011
#DIRSDL=/home/robin_arch/cour/1ere_annee_phelma/info/sdl_phelma/

CFLAGS=-g -c -O2 -Wall -Wextra
LDFLAGS= 
CIBLE=voyageur_de_commerce

run : ${CIBLE}
	./${CIBLE}

all : voyageur_de_commerce

voyageur_de_commerce: fourmi.c graph.c main.c
	gcc -o $@  $^  $(LDFLAGS)

%.o:%.c
	gcc $(CFLAGS) $< -o $@

clean:
	rm *.o voyageur_de_commerce


