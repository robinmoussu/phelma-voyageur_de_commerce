#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "graph.h"
#include "fourmi.h"
#include "sommet.h"

/**
 * \param argc nombre de graph passé en entrée. Doit être égal à 1.
 * \param argv nom du graph passé en entrée
 * \return 0 si le program s'est bien passé.
 */
int main (int argc, const char *argv[])
{
    void    *memory_pool;
    char    *data_graph;
    Sommet  *villes;
    Arc     *arcs;
    Fourmi  *meilleure_fourmi;
    Fourmi  *fourmi_actuelle;
    bool    *ville_visitees;
    float   *proba_ville;
    int     nb_villes;
    int     nb_voisins;
    int i;

    if (argc != 2) {
        fprintf(stderr, "Syntax error. You have to specifie the filename of the file that contains the data");
        return EXIT_FAILURE;
    }

    // Initialise les données du graphe, et alloue la mémoire
    memory_pool = creation_graph(argv[1], &villes, &arcs, &meilleure_fourmi, &fourmi_actuelle, &ville_visitees, &proba_ville, &nb_villes, &nb_voisins);
    if (!memory_pool) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < MAX_C; i++) {
        parcourt(fourmi_actuelle, meilleure_fourmi, villes, nb_villes, ville_visitees, ALPHA, BETA, proba_ville);
        ON_DEBUG(affiche_parcourt(fourmi_actuelle, villes, nb_villes, ville_visitees));
        graph_update(&fourmi_actuelle, &meilleure_fourmi, villes, nb_villes, ville_visitees);
    }

    // affichage du meilleur parcourt
    affiche_parcourt(fourmi_actuelle, villes, nb_villes, ville_visitees);

    // On libère toute la mémoire du programme
    free(memory_pool);
    return EXIT_SUCCESS;
}
