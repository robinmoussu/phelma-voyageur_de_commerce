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
 
#include <stdlib.h>     /* srand, rand */
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "fourmi.h"
#include "memory.h"


void init_fourmi(Fourmi *f, Ville villes[], int nb_villes, bool deja_visite[])
{
    int ville_depart = rand()%nb_villes;
    f->L = 0;
    f->nb_villes_deja_visite = 1;
    f->parcourt_valide = true;
    f->tabu[0] = get_in_villes(villes, ville_depart, nb_villes);
    deja_visite[ville_depart] = true;
}

bool deja_visite(Ville *a_visiter, Ville *deja_visite[], int nb_villes_deja_visite)
{
    int i;

    for (i = 0; i< nb_villes_deja_visite; i++){
        if (a_visiter == deja_visite[i]) { // On compare les adresses des villes
            return true;
        }
    }

    return false;
}

void ville_suivante(Fourmi *f, int alpha, int beta, float proba_ville[], bool deja_visite[])
{
    float tirage;
    float cumul_proba;  /// < valeur permettant la normalisation des probabilités
    float fx;           /// < valeur courante de la fonction de répartition
    Ville *ville_courante;
    int i;

    ville_courante = f->tabu[f->nb_villes_deja_visite - 1];

    // On calule la probabilitée de tirer chacune des ville à visiter
    cumul_proba = 0;
    for (i = 0; i < ville_courante->nb_voisins; i++) {
        Arc   *arc_courant  = ville_courante->voisins[i];

        if (deja_visite[get_arrivee(ville_courante, arc_courant)->id_ville]) {
            proba_ville[i] = 0;
        } else {
            proba_ville[i] = pow(*get_pheromones(ville_courante,arc_courant),alpha) / pow(arc_courant->distance,beta);

        }

        cumul_proba += proba_ville[i];
    }

    if (cumul_proba == 0) {
        fprintf(stderr,"error: All cities were already visited, no path found\n");
        f->parcourt_valide = false;
        return;
    }

    // On selectionne aléatoirement une ville parmi la liste de ville (en la normalisant)
    tirage = rand() * cumul_proba / (float) RAND_MAX;
    fx = 0;
    for (i = 0; i < ville_courante->nb_voisins; i++) {
        fx += proba_ville[i];
        if ((tirage < fx) && (proba_ville[i] != 0)) {
            // C'est cette ville qui a été selectionnée
            Ville *ville_arrivee = get_arrivee(ville_courante, ville_courante->voisins[i]);

            f->tabu[f->nb_villes_deja_visite++] = ville_arrivee;
            f->L += get_arc(ville_courante, ville_arrivee)->distance; // On actualise la distance parcouru
            deja_visite[ville_arrivee->id_ville] = true;
            ON_DEBUG(printf("City chosen : %s\n", ville_arrivee->nom);)
            break;
        }
    }

}


void parcourt(Fourmi *fourmi_actuelle, Ville villes[], int nb_villes, bool ville_visitees[], int alpha, int beta, float proba_ville[])
{
    int i;

    // On réinitialise le tableau des villes visitées avant toutes choses
    memset(ville_visitees, false, nb_villes*sizeof(bool));

    // On fabrique une nouvelle fourmi
    init_fourmi(fourmi_actuelle, villes, nb_villes, ville_visitees);

    while (fourmi_actuelle->parcourt_valide && (fourmi_actuelle->nb_villes_deja_visite < nb_villes)) {
        ville_suivante(fourmi_actuelle, alpha, beta, proba_ville, ville_visitees);
    }
}

bool parcourt_valide(Fourmi *f, int nb_villes, bool ville_visitees[])
{
    int i;
    double distance = 0;

    // on s'assure que la fourmi semble avoir visiter toutes les villes
    if (f->nb_villes_deja_visite != nb_villes) {
        fprintf(stderr, "Error : All cities are not visited (%d cities visited instead of %d)\n",f->nb_villes_deja_visite, nb_villes);
        return false;
    }

    // On initialise la liste des villes visitées
    memset(ville_visitees, false, nb_villes*sizeof(bool));

    // On refait le parcourt de la fourmi (de la ville 0 à l'avant-dernière ville vu qu'on calcule la distance entre la ville n et n+1)
    ville_visitees[f->tabu[0]->id_ville] = true;
    for (i = 0; i < (nb_villes - 1); i++) {
        Ville *ville_courante = f->tabu[i];
        Ville *ville_suivante = f->tabu[i + 1];

        // On s'assure que la fourmi n'était pas déjà passé par cette ville

        if (ville_visitees[ville_suivante->id_ville]) {
            fprintf(stderr, "Error : City visited twice (%s)\n", ville_suivante->nom);
            return false;
        } else {
            ville_visitees[ville_suivante->id_ville] = true;
        }

        // on calcule la distance jusqu'à la prochaine ville
        distance += get_arc(ville_courante, ville_suivante)->distance;
    }

    // on vérifie que la distance était correctement calculée
    // vu que ce sont des flotants, on ne peut pas faire (distance == f->L)
    if ((distance - f->L) > 0.00001) {
        fprintf(stderr, "error : Distance invalid\n");
        return false;
    }

    return true;
}

void parcourt_update(Fourmi **fourmi_actuelle, Fourmi **meilleure_fourmi, int nb_villes, bool ville_visitees[], float evaporation, float depot_pheromones)
{
    Ville *depart, *arrivee;
    int i;

    // on s'assure que le parcourt de la fourmi est valide
    ON_DEBUG(
        if (!parcourt_valide(*fourmi_actuelle, nb_villes, ville_visitees)) {
            fprintf(stderr, "Error : Invalid path.\n");
            return;
        }
    )

    depart  = (*fourmi_actuelle)->tabu[0];
    for(i = 1; i < nb_villes; i++) { // nb : on commence avec la ville numéro 1 (soit l'arc de la ville 0 vers la ville 1)
        Arc *arc_courant;
        arrivee = (*fourmi_actuelle)->tabu[i];
        arc_courant= get_arc(depart, arrivee);

        // on met à jour les phéromones sur les arcs
        *get_pheromones(depart,arc_courant) = evaporation*(arc_courant->pheromonesAB) + depot_pheromones/((*fourmi_actuelle)->L);

        // on actualise la ville de départ
        depart = arrivee;
    }

    // On regarde si la nouvelle fourmi a un trajet plus performant que l'ancienne (et que l'ancien était initialisé)
    // Si c'est le cas, (plutot que de copier toutes les données de la fourmi actuelle dans la meilleure fourmi,
    // ce qui est long), on les swap.
    if ((*fourmi_actuelle)->L < (*meilleure_fourmi)->L) {
        swap((void*) fourmi_actuelle, (void*) meilleure_fourmi);
    }
}

void affiche_parcourt(Fourmi *f, int nb_villes, bool ville_visitees[])
{
    int i;

    // on s'assure que le parcourt de la fourmi est valide
    if (!parcourt_valide(f, nb_villes, ville_visitees)) {
        fprintf(stderr, "Error : Invalid path.\n");
        return;
    }

    for(i = 0; i < nb_villes; i++) {
        printf("\t%s\n", f->tabu[i]->nom);
    }
    printf("\n");
}