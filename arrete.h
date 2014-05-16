#ifndef arrete_H
#define arrete_H

/* on définit l'arc comme uns liste*/
typedef struct ARRETE 
{
    int *depart; //ville de depart
    int arrive; //ville d'arrivee
    double distance;
    double pheromone;
    struct ARRETE* suiv;
} Arc;


/* on définit la structure file chaines pour enregistrer des arrêtes trouvés, la nouvelle solution entrée est sauvé dans la queue de la file*/
typedef struct FILEARC{
    Arc* arc;            
    struct FILEARC *suiv;     
} FileArc;


/*on ajoute l'arrête sur la tete de la liste qui est contenu dans les sommets*/
Arc* arrete(int depart,int arrive, double distance, Arc* Listearrete);


#endif
