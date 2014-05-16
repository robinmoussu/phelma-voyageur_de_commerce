#include "arrete.h"
#include <stdio.h>
#include <stdlib.h>

#define cst_epsilon 0.00000001 /// < Valeur initiale non nulle de phéromones sur les arcs

Arc* arrete(int noeud1,int noeud2, double Dist, Arc* Listearrete)
{
	Arc* arrete = calloc(1, sizeof(arrete));

	arrete->depart = noeud1;
	arrete->arrive = noeud2;
	arrete->distance = Dist;
	arrete->pheromone = cst_epsilon;
	arrete->suiv = Listearrete;        //la nouvelle tete pointe vers la liste precedent

	return arrete;
}
