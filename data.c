
/*
 *    Voyageur de commerce
 *    Copyright (C) 2014 Robin Moussu - Jingbo Su
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <stdlib.h>
#include <double.h>

#include "data.h"

/// passe à la ligne suivante
void flush_line(FILE *fp)
{
    while (fgetc(fp) != '\n') {;} // le \n de la ligne courante
    while (fgetc(fp) != '\n') {;} // la ligne suivante
}

void read_villes(FILE *fp, Ville villes[], int nb_villes)
{
    int   i;

    flush_line(fp); // lire les mots "sommets du graphe"
    for (i = 0; i < nb_villes; i++) { // lire tous les info dans "sommets du graphe"  
        Ville *p_ville = (Ville*) get_in_villes(villes, i, nb_villes);

        fscanf(fp,"%d %lf %lf %s",&(p_ville->id_ville), &(p_ville->x), &(p_ville->y), p_ville->nom);
        p_ville->nb_voisins = 0;    // Pour l'instant, on ne connait pas les arcs voisins
    }
}


void read_arcs(FILE *fp, Arc arcs[], Ville villes[], int nb_villes, int nb_arcs)
{
    int   noeud1, noeud2;    // noeud1 et noeud2 les deux ville d'une arrete
    int   i;

    // lecture des Arcs
    flush_line(fp); // lire les mots"Arêtes du graphe : noeud1 noeud2 valeur"
    for (i = 0; i < nb_arcs; i++) { // lire toutes les info dans "sommets du graphe"  
        Arc   *p_arc = get_in_arcs(arcs, i);
        Ville *p_ville;

        fscanf(fp,"%d %d %lf", &noeud1, &noeud2, &(p_arc->distance));
        p_arc->pheromonesAB = p_arc->pheromonesBA = EPSILON_PHEROMONES;

        // on cherche la ville de départ et d'arrivée à partir de leurs identifiants
        // et on ajoute l'arc courant dans la liste des voisins
        // NB : les arcs sont supposé bi-directionnels
        p_ville = get_in_villes(villes,noeud1,nb_villes); // ville de départ
        p_ville->voisins[(p_ville->nb_voisins)++] = p_arc;
        p_arc->ville_A = (struct Ville*) p_ville;
        p_ville = get_in_villes(villes,noeud2,nb_villes); // ville d'arrivée
        p_ville->voisins[(p_ville->nb_voisins)++] = p_arc;
        p_arc->ville_B = (struct Ville*) p_ville;
    }
}

//Dans ce fichier on crÃ©e une graphe en lisant des texts GRAPHE donnÃ©s et ajouter des donner dans le tableau allouÃ©
void* creation_graph(const char *data_graph, Sommet *(villes[]), Arc *(arcs[]), Fourmi *(*fourmis[]), Fourmi **meilleure_fourmi, bool *(ville_visitees[]), double *(proba_ville[]), int *nb_villes, int *nb_arcs, int nb_fourmis)
{
    void  *memory_pool;     /// pointeur sur la zone qui va contenir l'intégralité de la mémoire necessaire pour la simulation
    FILE  *fp;              /// fichier contenant les informations sur le graph

    fp = fopen(data_graph,"r");
    if(!fp) { // verifie si on peut ouvrir ce fichier
        fprintf(stderr, "error :Can't open file\n");
        return 0;
    }

    fscanf(fp,"%d %d", nb_villes, nb_arcs); // lire le nombre du sommet et le nombre d'arc

    // Désormais, on connait l'espace mémoire total à allouer
    // Du coup, on peut allouer toutes les données de manière contigues
    memory_pool = memory_allocator(villes, arcs, fourmis, meilleure_fourmi, ville_visitees, proba_ville, *nb_villes, *nb_arcs, nb_fourmis);
    if (memory_pool==NULL) { return 0; }

    read_villes(fp, *villes, *nb_villes);
    read_arcs(fp, *arcs, *villes, *nb_villes, *nb_arcs);

    // La distance parcouru par la meilleure fourmie doit etre initialisée
    (*meilleure_fourmi)->L = FLT_MAX; // distance infinie
    (*meilleure_fourmi)->parcourt_valide = false; // utilisé si à la fin de l'algorithme aucun chemin n'a été trouvé

    print_graph(*villes, *arcs, *nb_villes, *nb_arcs);

    fclose(fp);
    return memory_pool;
}

void print_arc(Arc *p_arc)
{
    Ville *p_depart = (Ville*) p_arc->ville_A;
    const char *nom_depart = p_depart->nom;
    Ville *p_arrivee = (Ville*) p_arc->ville_B;
    const char *nom_arrivee = p_arrivee->nom;
    printf("\t%lf\t%lf\t%s\t\t%s\n", p_arc->distance, p_arc->pheromonesAB, nom_depart, nom_arrivee);
}

void print_graph(Sommet villes[], Arc arcs[], int nb_villes, int nb_voisins)
{
    int i,j;

    printf("\n----------------------------------------\n");
    printf("\nList of cities in graph:\n\n");
    for (i = 0; i < nb_villes; i++) {
        Ville *p_ville = get_in_villes(villes, i, nb_villes);
        printf("\nid\tx\t\ty\t\tname\t\tnumber of arcs\n");
        printf("%d\t%lf\t%lf\t%s\t\t%d\n\n",p_ville->id_ville, p_ville->x, p_ville->y, p_ville->nom, p_ville->nb_voisins);
        printf("\tDISTANCE\tPHEROMONE\tCITY A\t\tCITY B\n");
        for (j = 0; j < p_ville->nb_voisins; j++) {
            print_arc(p_ville->voisins[j]);
        }
        printf("\n");
    }

    printf("\n----------------------------------------\n");

    printf("\nList of arcs in graph\n");
    printf("\tDISTANCE\tPHEROMONE\tCITY A\t\tCITY B\n");
    for (i = 0; i < nb_voisins; i++) {
        print_arc(get_in_arcs(arcs, i));
    }

    printf("\n----------------------------------------\n");
}