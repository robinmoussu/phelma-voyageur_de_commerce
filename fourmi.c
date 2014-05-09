#include <stdlib.h>     /* srand, rand */
#include <mah.h>
# include "main.h"

//// #include <time.h>       /* time */
//// TO DO: srand(time(NULL)); // dans le main

Fourmi init_fourmi(Parametres *param)
{
    Fourmi f;

    f.tabu = NULL;
    f.L = 0;
    return f;
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
 * \param p Les paramètres de la simulation
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi f, Parametres *p)
{
    float tirage;
    float proba_ville;  /// < la probabilité de chaque ville d'être tirée.
    float cumul_proba;  /// < valeur permettant la normalisation des probabilités
    float fx;           /// < valeur courante de la fonction de répartition
    Ville *ville_courante;
    int i;

    ville_courante = f->tabu[f-nb_villes_deja_visite];

    // On calule la probabilité de tirer chacune des ville à visiter
    proba_ville = malloc(ville_courante->nb_voisins)*sizeof(proba_ville));
    cumul_proba = 0;
    for (i = 0; i < p->nb_ville; i++) {
        Arc *voisin_courant = ville_courante->voisins[i];

        if (deja_visite(voisin_courant->arrivee, f->tabu, f->nb_villes_deja_visite) {
            proba_ville[i] = 0;
        } else {
            proba_ville[i] = pow(voisin_courant->visibilite,p->alpha) / pow(voisin_courant->d,p->beta);
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
            f->tabu[f->nb_villes_deja_visite++] = ville_courante->voisins[i];
            break;
        }
    }

}

/** Valide le parcourt d'une fourmi
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi f, Graph list_villes, int nb_villes)
{
    bool retour = true;

    // on s'assure que la fourmi à visite toutes les villes
    if (f->nb_villes_deja_visite != nb_villes) {
        retour = false;
    } else {

        // On s'assure que toutes ces villes sont bien uniques
        bool ville_visitees[] = malloc(nb_villes * sizeof(ville_visitees));
        Ville *ville_courante = f->tabu[0];
        int j;


        // On refait le parcourt de la fourmi
        for (ville_courante = f->tabu[i = 0]; i < nb_villes; ville_courante = f->tabu[i++]) {
            // On s'assure que la fourmi n'était pas déjà passé par cette ville
            for (j = 0; j < nb_villes; j++) {
                if (ville_courante == list_villes[i]) { // comparaison par adresse
                    if (ville_visitees[j]) { // comparaison par adresse
                        retour = false;
                        goto fin_parcourt; // inutile de continuer plus loin le parcourt. Vu qu'il y a deux boucles imbriquées, un break ne suffit pas. L'utilisation du goto est donc justifié pour des raisons de performances
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
void (Fourmi f, Graph meilleur_parcourt);

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
*/
void graph_update(Fourmi f, Graph g);

