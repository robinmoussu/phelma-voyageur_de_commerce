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

/** Déplace la fourmi dans la nouvelle ville
 * \param f La fourmi en train d'effectuer son voyage
 * \param 
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi f, Parametres *p, Graph g);

- Initialisation (ville de départ + paramètres)
- Parcourt
    + Choix de la prochaine ville
        * importances de la visibilité
        * importances de la phéromones
    + Mise à jour des phéromones sur le graphe
        * nouveau phéromones
        * évaporation
    + meilleur parcourt



#endif /* MAIN_H */
