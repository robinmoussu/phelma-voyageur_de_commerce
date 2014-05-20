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
make install
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
 * Ainsi que trois graphs incomplets :
 * - graphe_11_incomplet.txt
 * - graphe_12_incomplet.txt
 * - graphe_13_incomplet.txt
 * 
 * Un graph incomplet est un graph dans lequel certaines villes ne sont pas reliées entre elles. Le graphe graphe_11_incomplet.txt
 * est particulièrement incomplet, et ne donne pas toujours de solutions valides.
 *
 * \subsection subsec_time Temps d'exécution
 * 
 * La vitesse d'exécution de cet algorithme été particulièrement travaillé. Pour le tester vous pouvez la commande suivante :

\verbatim
make clean && make install && time ./voyageur nom_du_graph_contenant_les_donnees.txt
\endverbatim

 * \section test_section test
 *
 * Les tests de validité de l'algorithme sont effectués directement dans le programme si les options de compilation ont été choisit correctement.
 * \see ON_DEBUG
 * \see ON_VERBOSE
 * \note Toutes les erreurs sont écritent dans la sortie d'erreur standard (stderr).
 *
 * Vous pouvez spécifier toutes les options de débug en modifiant les paramètre dans main.h, ou plus simplement toutes les activer à la compilation
 * avec la commande suivante (attention, le programme devient alors très bavard !) :

\verbatim
make debug
./voyageur nom_du_graph_contenant_les_donnees.txt
\endverbatim

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


 *
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
    Fourmi  *(*fourmis[NB_FOURMIS]);
    Fourmi  *meilleure_fourmi;
    bool    *ville_visitees;
    double   *proba_ville;
    int     nb_villes;
    int     nb_arcs;

    if (argc != 2) {
        fprintf(stderr, "Syntax error. You have to specifie the filename of the file that contains the data.\n");
        return EXIT_FAILURE;
    }

    // Initiale le générateur pseudo-aléatoire
    srand(time(NULL));

    // Initialise les données du graphe, et alloue la mémoire
    memory_pool = creation_graph(argv[1], &villes, &arcs, (Fourmi***) &fourmis, &meilleure_fourmi, &ville_visitees, &proba_ville, &nb_villes, &nb_arcs, NB_FOURMIS);
    if (!memory_pool) {
        return EXIT_FAILURE;
    }

    // On explore le graph
    explore_graph(villes, arcs, fourmis
        , meilleure_fourmi, ville_visitees, proba_ville
        , nb_villes, NB_FOURMIS
        , MAX_C, ALPHA, BETA, EVAPORATION, DEPOT_PHEROMONES);


    // On libère toute la mémoire du programme
    free(memory_pool);
    return EXIT_SUCCESS;
}
