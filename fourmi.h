#ifndef FOURMI_H
#define FOURMI_H

#include "main.h"

typedef struct {
    int nb_villes_deja_visite;
    float L;           /// < Longueur d'un chemin, somme des longueurs de chaque arc constituant le chemin
    Ville *tabu[];      /// < Liste des villes déjà parcourues par la fourmi k. La plus plus récente est enregistré dans tabu[nb_villes_deja_visite - 1]; La taille de ce tableau est constante et est égale au nombre de villes dans la simulation;
} Fourmi;

/** Initialise la structure fourmi
 *  \param point_depart la ville de depart pour la fourmi
 */
void init_fourmi(Fourmi *f, Ville *point_depart);

/** Indique si la ville a déjà été visité par la fourmi
 */
bool deja_visite(Ville *a_visiter, Ville *deja_visite[], int nb_villes_deja_visite);

/** Déplace la fourmi dans la nouvelle ville, en fonction de sa visibilité et des phéromones sur l'arc
 * \param f La fourmi en train d'effectuer son voyage
 * \param p const Les paramètres de la simulation
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi *f, int nb_villes, int alpha, int beta);

/** Valide le parcourt d'une fourmi
 * \param p const Les paramètres de la simulation
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi *f, Ville *list_villes, int nb_villes);

/** Met à jour le meilleur parcourt si celui de la fourmi est meilleur
 */
void meilleur_parcourt(Fourmi f, Graph *meilleur_parcourt[], int distance_meilleur_parcourt, int nb_villes);

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
 */
void graph_update(Fourmi f, Graph *g);


#endif // FOURMI_H
