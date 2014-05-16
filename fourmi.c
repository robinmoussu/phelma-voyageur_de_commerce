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
    f->tabu[0] = (Ville*) point_depart;
    f->L = 0;
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

        if (deja_visite((Ville*) voisin_courant->arrivee, (Ville**) f->tabu, f->nb_villes_deja_visite)) {
            proba_ville[i] = 0;
        } else {
            // TODO verrifier la formule
            proba_ville[i] = pow(1/voisin_courant->d,alpha) / pow(voisin_courant->d,beta);
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

/** Valide le parcourt d'une fourmi
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi *f, Ville *list_villes, int nb_villes)
{
    bool retour = true;

    // on s'assure que la fourmi à visite toutes les villes
    if (f->nb_villes_deja_visite != nb_villes) {
        retour = false;
    } else {

        // On s'assure que toutes ces villes sont bien uniques
        bool *ville_visitees = malloc(nb_villes * sizeof(*ville_visitees));
        Ville *ville_courante = f->tabu[0];
        int i, j;


        // On refait le parcourt de la fourmi
        for (ville_courante = f->tabu[i = 0]; i < nb_villes; ville_courante = f->tabu[i++]) {
            // On s'assure que la fourmi n'était pas déjà passé par cette ville
            for (j = 0; j < nb_villes; j++) {
                if (ville_courante == &list_villes[i]) { // nb : comparaison par adresse
                    if (ville_visitees[j] ) { // si la ville était déjà visitée
                        retour = false;
                        goto fin_parcourt; // inutile de continuer plus loin le parcourt. Vu qu'il y a deux boucles imbriquées, un break ne suffit pas. L'utilisation du goto est donc justifié pour des raisons de performances. NB : si on commente cette ligne, l'agorithme reste fonctionnel, mais sera inutilement plus long.
                    } else {
                        ville_visitees[j] = true;
                    }
                }
            }
        }
fin_parcourt:
        free(ville_visitees);

    }

    return retour;
}

/** Met à jour le meilleur parcourt si celui de la fourmi est meilleur
 */
void meilleur_parcourt(Fourmi f, Graph *meilleur_parcourt[], int distance_meilleur_parcourt, int nb_villes)
{
    int i;

    for (i = 0; i < nb_villes; i++) {

    }
}

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
*/
void graph_update(Fourmi f, Graph *g)
{}

