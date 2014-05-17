#ifndef MAIN_H
#define MAIN_H

// C/C++ File
// AUTHOR:   robin_arch
// FILE:     main.h
// ROLE:     TODO (some explanation)
// CREATED:  2014-04-04 08:04:06
// MODIFIED: 2014-04-04 08:04:06

typedef enum {false,true} bool;

// paramètres de la simulation
typedef struct {
    int nb_fourmi;  /// < nombre total de fourmis de l'algorithme
    int nb_villes;  /// < nombre de villes dans le graphe
    float alpha;    /// < Coefficient régulant l'importance des phéromones pour le choix d'une ville
    float beta;     /// < Coefficient régulant l'importance de la visibilité pour le choix d'une ville
    float epsilon;  /// < Valeur initiale non nulle de phéromones sur les arcs
    float rho;      /// < Coefficient d'évaporation des phéromones
    float Q;        /// < Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi
} Parametres;

/// Constante, nombre maximum de cycles autorisés.
#define MAX_C   200
#define ALPHA   100
#define BETA    100

#endif /* MAIN_H */
