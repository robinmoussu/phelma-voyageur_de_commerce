#ifndef MAIN_H
#define MAIN_H

// C/C++ File
// AUTHOR:   robin_arch
// FILE:     main.h
// ROLE:     TODO (some explanation)
// CREATED:  2014-04-04 08:04:06
// MODIFIED: 2014-04-04 08:04:06

typedef int graph[];

int m;          /// < nombre total de fourmis de l'algorithme
int n;          /// < nombre de villes dans le graphe G
graph tabu;     /// < Liste des villes déjà parcourues par la fourmi k
float alpha;    /// < Coefficient régulant l'importance des phéromones pour le choix d'une ville
float beta;     /// < Coefficient régulant l'importance de la visibilité pour le choix d'une ville
float epsilon;  /// < Valeur initiale non nulle de phéromones sur les arcs
float Q;        /// < Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi

/// < Constante, nombre maximum de cycles autorisés.
#define MAX_C

int L;          /// < Longueur d'un chemin, somme des longueurs de chaque arc constituant le ch



typedef struct {
    int d[];            /// < Distance entre les villes i et j
    int visibilite[];   /// < Quantité de phéromones sur l'arc a
} Ville;

ρ \in [0,1]                         /// < Coefficient d'évaporation des phéromones
L_k = Σ_aij \in solution_k_dij      /// < Longueur d'un chemin, somme des longueurs de chaque arc constituant le ch

η_ij = 1/d_ij                       /// < Visibilité de la ville j quand une fourmi se trouve dans la ville i
#endif /* MAIN_H */
