#ifndef MAIN_H
#define MAIN_H

// C/C++ File
// AUTHOR:   robin_arch
// FILE:     main.h
// ROLE:     TODO (some explanation)
// CREATED:  2014-04-04 08:04:06
// MODIFIED: 2014-04-04 08:04:06

typedef struct {
    float d;            /// < Distance entre les villes i et j
    float visibilite;   /// < Quantité de phéromones sur l'arc a
} Arc;

typedef struct {
    Arc *arc;           /// < Liste des ville que l'on peut atteindre depuis la ville
    const char nom[64]; /// < Nom de la ville
} Ville;

typedef Ville *Graph;

// paramètres de la simutation
typedef struct {
    int m;          /// < nombre total de fourmis de l'algorithme
    int n;          /// < nombre de villes dans le graphe G
    float alpha;    /// < Coefficient régulant l'importance des phéromones pour le choix d'une ville
    float beta;     /// < Coefficient régulant l'importance de la visibilité pour le choix d'une ville
    float epsilon;  /// < Valeur initiale non nulle de phéromones sur les arcs
    float rho;      /// < Coefficient d'évaporation des phéromones
    float Q;        /// < Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi
} Parametres;

Graph meilleur_parcourt;

/// < Constante, nombre maximum de cycles autorisés.
#define MAX_C   200

typedef struct {
    Graph tabu;        /// < Liste des villes déjà parcourues par la fourmi k
    float L;           /// < Longueur d'un chemin, somme des longueurs de chaque arc constituant le cheminemin
} Fourmi;

///////////
// graph //
///////////

/** Initialise le graph à partir des données contenu dans le fichier data_graph.
 * \param n out : Nombre de ville contenu dans le graph (indiqué dans le fichier data_graph)
 */
Graph creation_graph(FILE data_graph, int *n);

/** Initialise les paramètres de la simutation
 */
Parametres init_param(int m, float alpha, float beta, float epsilon, float rho, float Q);

/** Lance la simulation
 */
void run_simu(Parametres *p, Graph g);

/////////////
// fourmis //
/////////////

/** Fabrique une nouvelle fourmis
 */
Fourmi init_fourmi();

/** Déplace la fourmi dans la nouvelle ville, en fonction de sa visibilité et des phéromones sur l'arc
 * \param f La fourmi en train d'effectuer son voyage
 * \param p Les parametres de la simulation
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi f, Parametres *p);

/** Valide le parcourt d'une fourmi
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi f, Parametres p);

/** Met à jour le meilleur parcourt si celui de la fourmi est meilleur
 */
void (Fourmi f, Graph meilleur_parcourt);

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
 */
void graph_update(Fourmi f, Graph g);


#endif /* MAIN_H */
