#ifndef ARRETE_H
#define ARRETE_H

struct Ville;

typedef struct {
    double d;            /// < Distance entre les villes i et j
    double pheromones;    /// La quantitée de phéromone actuelement sur l'arc
    struct Ville *depart;      /// < Sommet de départ (ville i)
    struct Ville *arrivee;  /// < Sommet d'arrivée (ville j)
} Arc;
/*on ajoute l'arrête sur la tete de la liste qui est contenu dans les sommets*/
Arc* arrete(int depart,int arrive, double distance, Arc* Listearrete);

#endif // ARRETE_H
