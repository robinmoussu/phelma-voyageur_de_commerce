#ifndef MAIN_H
#define MAIN_H

// chose one of the folowing statement
#define ON_DEBUG(instruction) 
//#define ON_DEBUG(instruction) instruction

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

#define ALPHA   1
#define BETA    2

#endif /* MAIN_H */
