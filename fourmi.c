#include <stdlib.h>     /* srand, rand */
#include <math.h>
#include <string.h>

# include "fourmi.h"

//// #include <time.h>       /* time */
//// TO DO: srand(time(NULL)); // dans le main

/** Initialise la structure fourmi
 *  \param point_depart la ville de depart pour la fourmi
 */
void init_fourmi(Fourmi *f, Ville *point_depart)
{
    f->L = 0;
    f->nb_villes_deja_visite = 1;
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
   \param proba_ville : tableau aloué, non initialisé servant à calculer la la probabilité de chaque ville d'être tirée.
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi *f, int nb_villes, int alpha, int beta, float proba_ville[], bool deja_visite[])
{
    float tirage;
    float cumul_proba;  /// < valeur permettant la normalisation des probabilités
    float fx;           /// < valeur courante de la fonction de répartition
    Ville *ville_courante;
    int i;

    ville_courante = f->tabu[f->nb_villes_deja_visite - 1];

    // On calule la probabilité de tirer chacune des ville à visiter
    cumul_proba = 0;
    for (i = 0; i < ville_courante->nb_voisins; i++) {
        Arc   *arc_courant  = ville_courante->voisins[i];

        if (deja_visite[get_arrivee(ville_courante, arc_courant)->id_ville]) {
            proba_ville[i] = 0;
        } else {
            proba_ville[i] = pow(arc_courant->pheromones,alpha) / pow(arc_courant->distance,beta);
        }

        cumul_proba += proba_ville[i];
    }

    if (cumul_proba == 0) {
        fprintf(stderr,"All cities were already visited, no path found");
        return;
    }

    // On selectionne aléatoirement une ville parmi la liste de ville (en la normalisant)
    tirage = rand() * cumul_proba / (float) RAND_MAX;
    fx = 0;
    for (i = 0; i < ville_courante->nb_voisins; i++) {
        fx += proba_ville[i];
        if ((tirage < fx) && (proba_ville[i] != 0)) {
            Ville *a0;
            Ville *a1;
            Ville *a2;
            Ville *a3;
            Ville *a4;
            Ville *a5;
            // C'est cette ville qui a été selectionnée
            Ville *ville_arrivee = get_arrivee(ville_courante, ville_courante->voisins[i]);

            f->tabu[f->nb_villes_deja_visite++] = ville_arrivee;
            f->L += get_arc(ville_courante, ville_arrivee)->distance; // On actualise la distance parcouru
            deja_visite[ville_arrivee->id_ville] = true;

            a0 = (Ville*) f->tabu[0];
            a1 = (Ville*) f->tabu[1];
            a2 = (Ville*) f->tabu[2];
            a3 = (Ville*) f->tabu[3];
            a4 = (Ville*) f->tabu[4];
            a5 = (Ville*) f->tabu[5];
            ON_DEBUG(printf("City chosen : %s\n", ville_arrivee->nom);)
            break;
        }
    }

}


void parcourt(Fourmi *fourmi_actuelle, Fourmi *meilleure_fourmi, Ville villes[], int nb_villes, bool ville_visitees[], int alpha, int beta, float proba_ville[])
{
    int i;
    init_fourmi(fourmi_actuelle, &villes[0]);

    // seule la premiere ville est visitee
    ville_visitees[0] = true;
    memset(ville_visitees + 1, false, nb_villes*sizeof(bool));

    // On commence à 1, vu que la ville de départ est déjà compté
    for (i = 1; i < nb_villes; i++) {
        ville_suivante(fourmi_actuelle, nb_villes, alpha, beta, proba_ville, ville_visitees);
    }
}

/** Valide le parcourt d'une fourmi
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi *f, Ville villes[], int nb_villes, bool ville_visitees[])
{
    int i, j;
    double distance = 0;

    // on s'assure que la fourmi semble avoir visiter toutes les villes
    if (f->nb_villes_deja_visite != nb_villes) {
        fprintf(stderr, "Error : All cities are not visited (%d cities visited instead of %d)\n",f->nb_villes_deja_visite, nb_villes);
        return false;
    }

    // On initialise la liste des villes visitées
    ville_visitees[0] = true;
    memset(ville_visitees + 1, false, nb_villes*sizeof(bool));

    // On refait le parcourt de la fourmi (de la ville 0 à l'avant-dernière ville vu qu'on calcule la distance entre la ville n et n+1)
    for (i = 0; i < (nb_villes - 1); i++) {
        Ville *ville_courante = f->tabu[i];
        Ville *ville_suivante = f->tabu[i + 1];

        // On s'assure que la fourmi n'était pas déjà passé par cette ville

        if (ville_visitees[ville_suivante->id_ville]) {
            fprintf(stderr, "Error : City visited twice (%s)", ville_suivante->nom);
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

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
*/
void graph_update(Fourmi **fourmi_actuelle, Fourmi **meilleure_fourmi, Ville villes[], int nb_villes, bool ville_visitees[])
{
    Ville *depart, *arrivee;
    int i;

    // on s'assure que le parcourt de la fourmi est valide
    if (!parcourt_valide(*fourmi_actuelle, villes, nb_villes, ville_visitees)) {
        fprintf(stderr, "Error : Invalid path.\n");
        return;
    }

    depart  = (*fourmi_actuelle)->tabu[0];
    for(i = 1; i < nb_villes; i++) { // nb : on commence avec la ville numéro 1 (soit l'arc de la ville 0 vers la ville 1)
        arrivee = (*fourmi_actuelle)->tabu[i];

        // on met à jour les phéromones sur les arcs
        get_arc(depart, arrivee)->pheromones += PARCOURT_PHEROMONES;

        // on actualise la ville de départ
        depart = arrivee;
    }

    // On regarde si la nouvelle fourmi a un trajet plus performant que l'ancienne (et que l'ancien était initialisé)
    // Si c'est le cas, (plutot que de copier toutes les données de la fourmi actuelle dans la meilleure fourmi,
    // ce qui est long), on les swap.
    if ((*fourmi_actuelle)->L < (*meilleure_fourmi)->L) {
        swap(fourmi_actuelle,meilleure_fourmi);
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

    printf("\nThat ant have made a travel of %lf km throught :\n", f->L);
    for(i = 0; i < nb_villes; i++) {
        printf("\t%s\n", f->tabu[i]->nom);
    }
    printf("\n");
}