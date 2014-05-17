#include <stdlib.h>     /* srand, rand */
#include <math.h>

# include "fourmi.h"

//// #include <time.h>       /* time */
//// TO DO: srand(time(NULL)); // dans le main

/** Initialise la structure fourmi
 *  \param point_depart la ville de depart pour la fourmi
 */
void init_fourmi(Fourmi *f, Ville *point_depart)
{
    f->L = 0;
    f->nb_villes_deja_visite = 0;
    f->tabu[0] = (Ville*) point_depart;
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

/** Déplace la fourmi dans la nouvelle ville, en fonction de sa visibilité et des phéromones sur l'arc
 * \param f La fourmi en train d'effectuer son voyage
 * \param nb_villes nombre de villes dans la simulation
 * \param alpha Coefficient régulant l'importance des phéromones pour le choix d'une ville
   \param beta :Coefficient régulant l'importance de la visibilité pour le choix d'une ville
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi *f, int nb_villes, int alpha, int beta)
{
    float tirage;
    float *proba_ville; /// < la probabilité de chaque ville d'être tirée.
    float cumul_proba;  /// < valeur permettant la normalisation des probabilités
    float fx;           /// < valeur courante de la fonction de répartition
    Ville *ville_courante;
    int i;

    ville_courante = f->tabu[f->nb_villes_deja_visite];

    // On calule la probabilité de tirer chacune des ville à visiter
    proba_ville = malloc((ville_courante->nb_voisins)*sizeof(proba_ville));
    cumul_proba = 0;
    for (i = 0; i < nb_villes; i++) {
        Arc *voisin_courant = ville_courante->voisins[i];

        if (deja_visite((Ville*) voisin_courant->arrivee, f->tabu, f->nb_villes_deja_visite)) {
            proba_ville[i] = 0;
        } else {
            // TODO verrifier la formule
            proba_ville[i] = pow(1/voisin_courant->distance,alpha) / pow(voisin_courant->distance,beta);
        }

        cumul_proba += proba_ville[i];
    }

    // On selectionne aléatoirement une ville parmi la liste de ville
    tirage = rand() / cumul_proba;
    fx = 0;
    for (i = 0; i < ville_courante->nb_voisins; i++) {
        fx += proba_ville[i];
        if (tirage < fx) {
            // C'est cette ville qui a été selectionnée
            f->tabu[f->nb_villes_deja_visite++] = (Ville*) ville_courante->voisins[i]->arrivee;
            break;
        }
    }

}


void parcourt(Fourmi *fourmi_actuelle, Fourmi *meilleure_fourmi, Ville villes[], int nb_villes, bool ville_visitees[], int alpha, int beta)
{
    int i;

    for (i = 0; i < nb_villes; i++) {
        ville_suivante(fourmi_actuelle, nb_villes, alpha, beta);
        fourmi_actuelle = graph_update(fourmi_actuelle, meilleure_fourmi, villes, nb_villes, ville_visitees);
    }
}

/** Valide le parcourt d'une fourmi
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi *f, Ville villes[], int nb_villes, bool ville_visitees[])
{
    Ville *ville_courante;
    int i, j;
    double distance = 0;

    // on s'assure que la fourmi semble avoir visiter toutes les villes
    if (f->nb_villes_deja_visite != nb_villes) {
        fprintf(stderr, "Error : All cities are not visited (%d cities visited instead of %d)\n",f->nb_villes_deja_visite, nb_villes);
        return false;
    }

    // On s'assure que toutes ces villes sont bien uniques
    for (i = 0; i < nb_villes; ++i) {
        ville_visitees = false;
    }

    // On refait le parcourt de la fourmi
    for (i = 0; i < nb_villes; i++) {
        ville_courante = f->tabu[i];

        // On s'assure que la fourmi n'était pas déjà passé par cette ville
        for (j = 0; j < nb_villes; j++) {
            if (ville_courante == get_in_villes(villes, i, nb_villes)) { // nb : comparaison par adresse
                if (ville_visitees[j] ) { // si la ville était déjà visitée
                    fprintf(stderr, "Error : City visited twice (%s)\ville_courante", ville_courante->nom);
                    return false;
                } else {
                    ville_visitees[j] = true;
                }
            }
        }

        // on calcule la distance jusqu'à la prochaine ville
        distance += get_arc(ville_courante, get_in_villes(villes, i + 1, nb_villes))->distance;
    }

    // on vérifie que la distance était correctement calculée
    if (distance != f->L) {
        return false;
    }

    return true;
}

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
*/
Fourmi* graph_update(Fourmi *fourmi_actuelle, Fourmi *meilleure_fourmi, Ville villes[], int nb_villes, bool ville_visitees[])
{
    Ville *depart, *arrivee;
    int i;

    // on s'assure que le parcourt de la fourmi est valide
    if (!parcourt_valide(fourmi_actuelle, villes, nb_villes, ville_visitees)) {
        fprintf(stderr, "Error : Invalid path.\n");
        return;
    }

    depart  = get_in_villes(villes, 0, nb_villes);
    for(i = 1; i < (nb_villes - 1); i++) { // nb : on commence avec la ville numéro 1 (arc de la ville 0 vers la ville 1)
        arrivee = get_in_villes(villes, i , nb_villes);

        // on met à jour les phéromones sur les arcs
        get_arc(depart, arrivee
            )->pheromones += PARCOURT_PHEROMONES;

        // on actualise la ville de départ
        depart = arrivee;
    }

    // On regarde si la nouvelle fourmi a un trajet plus performant que l'ancienne (et que l'ancien était initialisé)
    if ((fourmi_actuelle->L < meilleure_fourmi->L) || (meilleure_fourmi->L != 0)) {
        meilleure_fourmi = fourmi_actuelle;
        return meilleure_fourmi;
    } else {
        return fourmi_actuelle;
    }
}

void affiche_parcourt(Fourmi *f, Ville villes[], int nb_villes, bool ville_visitees[])
{
    Ville *ville_courante;
    int i;

    // on s'assure que le parcourt de la fourmi est valide
    if (!parcourt_valide(f, villes, nb_villes, ville_visitees)) {
        fprintf(stderr, "Error : Invalid path.\n");
        return;
    }

    printf("That ant have made a travel of %d km throught :\n", f->L);
    for(i = 1; i < (nb_villes - 1); i++) {
        ville_courante = get_in_villes(villes, i , nb_villes);

        printf("\t%s\n", ville_courante->nom);
    }
    printf("\n");
}