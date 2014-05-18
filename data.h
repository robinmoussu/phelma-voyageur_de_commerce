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
 
#ifndef GRAPH
#define GRAPH

/** \file data.h
 * \brief Contient les fonctions relative à la lectures des données du graph et à son affichage
 */


#include <stdio.h>

#include "main.h"
#include "fourmi.h"
#include "graph.h"
#include "memory.h"

/** Passe à la ligne suivante
 *  \note Permet de passer les lignes de commentaires
 */
void flush_line(FILE *fp);

/** Lit la liste des villes dans le fichier fp, et l'ajoute à la liste des villes
 *  \param fp fichier contenant les données
 *  \param villes espace mémoire dans lequel les villes doivent etre enregistrées
 *  \param nb_villes nombre de villes contenues dans le graph
 */
void read_villes(FILE *fp, Ville villes[], int nb_ville);

/** Lit la liste des arcs dans le fichier fp, et l'ajoute à la liste des arcs
 *  \note Ajoute pour chacunes des villes du graph la liste des arcs qui les relient
 *  \note Comme les arcs sont bi-directionnel, la ville de départ et d'arrivée d'un graph est arbitraire
 *  \param fp fichier contenant les données
 *  \param arcs espace mémoire dans lequel les arcs doivent etre enregistrés
 *  \param villes espace mémoire dans lequel les villes sont enregistrées
 *  \param nb_villes nombre de villes contenues dans le graph
 *  \param nb_arc nombre d'arc dans le graph
 */
void read_arcs(FILE *fp, Arc arcs[], Ville villes[], int nb_ville, int nb_arc);

/** Initialise le graph à partir des données contenu dans le fichier data_graph (et alloue la mémoire necessaire)
 *  \param data_graph nom du fichier contenant les données
 *  \see memory.h pour la liste des zones mémoires à allouer (les autres paramètres)
 *
 *  Les données doivent etre formatées de la manière suivante : 
 *      Une première ligne contenant le nombre de ville et le nombre d'arc
 *      Une ligne de commentaires
 *      La liste de toutes les données relatives aux villes (une par ligne) avec les données suivantes :
 *          numéro de la ville (identifiant unique, de 0 à nombre de ville - 1)
 *          coordonée x de la ville
 *          coordonée y de la ville
 *          nom de la ville (max 64 caractères)
 *      Une ligne de commentaires
 *      La liste de toutes les données relatives aux arcs (un par ligne) avec les données suivantes :
 *          identifiant de la ville de départ
 *          identifiant de la ville d'arrivée
 *          distance séparant les deux villes
 * 
 * \note Comme les arcs sont bi-directionnel, la ville de départ et d'arrivée d'un graph est arbitraire         
 */
void* creation_graph(const char *data_graph, Sommet *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle, bool *(ville_visitees[]), float *(proba_ville[]), int *nb_villes, int *nb_arc);

/** Affiche les données d'un arc
 */
void print_arc(Arc *p_arc);

/** Affiche les données du graph
 */
void print_graph(Sommet villes[], Arc arcs[], int nb_villes, int nb_voisins);

#endif // GRAPH