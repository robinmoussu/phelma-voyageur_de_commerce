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

/** \mainpage Documentation du projet Voyageur de commerce
 *
 * \section intro_sec Introduction
 *
 * Ce projet à pour but de résoudre le problème du voyageur de commerce à l'aide de l'utilisation de fourmis
 *
 * \section install_sec Installation
 *
 * \subsection install_subsc Téléchargement des sources
 *
 * Outils necessaires :
 * - git
 *
 * Éxécutez la commande suivante :

\verbatim
git clone http://github.com/robinmoussu/voyageur_de_commerce
\endverbatim

 *
 * \subsection running Éxécuter le programme
 *
 * Outils necessaires :
 * - gcc
 *
 * Éxécutez les commandes suivantes :

\verbatim
cd voyageur_de_commerce
make
./voyageur nom_du_graph_contenant_les_donnees.txt
\endverbatim

 *
 * Les graphs suivants sont fournis :
 * - berlin52.txt
 * - djibouti38.txt
 * - graphe11.txt
 * - graphe12.txt
 * - graphe13.txt
 * - graphe14.txt
 * - kroA100.txt
 * - Quatar194.txt
 *
 * \section copyright Copyright and License
 *
 * Ce logiciel est distribué sous la licence GNU GPL v3.

\verbatim

    Voyageur de commerce
    Copyright (C) 2014 Robin Moussu - Jingbo Su

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\endverbatim
 */


/** \file main.c
 * \brief fonction main du programme
 */

 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "data.h"
#include "fourmi.h"
#include "graph.h"

/**
 * \param argc nombre de graph passé en entrée. Doit être égal à 1.
 * \param argv nom du graph passé en entrée
 * \return 0 si le program s'est bien passé.
 */
int main (int argc, const char *argv[])
{
    void    *memory_pool;
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
        fprintf(stderr, "Syntax error. You have to specifie the filename of the file that contains the data.\n");
        return EXIT_FAILURE;
    }

    // Initiale le générateur pseudo-aléatoir
    srand(time(NULL));

    // Initialise les données du graphe, et alloue la mémoire
    memory_pool = creation_graph(argv[1], &villes, &arcs, &meilleure_fourmi, &fourmi_actuelle, &ville_visitees, &proba_ville, &nb_villes, &nb_voisins);
    if (!memory_pool) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < MAX_C; i++) {
        parcourt(fourmi_actuelle, villes, nb_villes, ville_visitees, ALPHA, BETA, proba_ville);
        ON_DEBUG(printf("\nThat ant have made a travel of %lf km throught :\n", meilleure_fourmi->L));
        ON_DEBUG(affiche_parcourt(fourmi_actuelle, nb_villes, ville_visitees));
        parcourt_update(&fourmi_actuelle, &meilleure_fourmi, nb_villes, ville_visitees);
    }

    // affichage du meilleur parcourt
    printf("\nThe best ant have made a travel throught :\n");
    affiche_parcourt(meilleure_fourmi, nb_villes, ville_visitees);
    printf("That was a trip of  %lf km.\n", meilleure_fourmi->L);

    // On libère toute la mémoire du programme
    free(memory_pool);
    return EXIT_SUCCESS;
}
