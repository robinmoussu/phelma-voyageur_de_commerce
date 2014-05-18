#DIRSDL=/users/prog1a/C/librairie/2011
#DIRSDL=/home/robin_arch/cour/1ere_annee_phelma/info/sdl_phelma/

CFLAGS= -c -Wall -fdiagnostics-color=auto -ggdb
CFLAGS_NO_DEBUG= -c -Wall -fdiagnostics-color=auto -O2 
LDFLAGS= -fdiagnostics-color=auto -lm -ggdb
CIBLE=voyageur
OPTION=graphe11.txt 

cible : $(CIBLE)

run : ${CIBLE}
	./${CIBLE} $(OPTION)

all : voyageur

voyageur: fourmi.c sommet.c graph.c main.c
	gcc -o $@  $^  $(LDFLAGS)

%.o:%.c
	gcc $(CFLAGS) $< -o $@

clean:
	rm voyageur


