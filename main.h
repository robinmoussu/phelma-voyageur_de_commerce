#ifndef MAIN_H
#define MAIN_H

// C/C++ File
// AUTHOR:   robin_arch
// FILE:     main.h
// ROLE:     TODO (some explanation)
// CREATED:  2014-04-04 08:04:06
// MODIFIED: 2014-04-04 08:04:06

typedef struct {
    int d;              /// < Distance entre les villes i et j
    int visibilite;     /// < Quantité de phéromones sur l'arc a
} Arc;

typedef struct {
    Arc *arc;           /// < Liste des ville que l'on peut atteindre depuis la ville
} Ville;

typedef Ville *graph;

// paramètres de la simutation
int m;          /// < nombre total de fourmis de l'algorithme
int n;          /// < nombre de villes dans le graphe G
graph tabu;     /// < Liste des villes déjà parcourues par la fourmi k
float alpha;    /// < Coefficient régulant l'importance des phéromones pour le choix d'une ville
float beta;     /// < Coefficient régulant l'importance de la visibilité pour le choix d'une ville
float epsilon;  /// < Valeur initiale non nulle de phéromones sur les arcs
float rho;      /// < Coefficient d'évaporation des phéromones
float Q;        /// < Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi

/// < Constante, nombre maximum de cycles autorisés.
#define MAX_C   200

int L;          /// < Longueur d'un chemin, somme des longueurs de chaque arc constituant le chemin



#endif /* MAIN_H */
