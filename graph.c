
#include <stdlib.h>
#include <float.h>

#include "graph.h"

/// passe à la ligne suivante
void flush_line(FILE *fp)
{
    while (fgetc(fp) != '\n') {;} // le \n de la ligne courante
    while (fgetc(fp) != '\n') {;} // la ligne suivante
}

// Les différentes stuctures utilisées dans ce programmes utilisent des tableaux
// de taille flexible (aray[]), cette fonction s'occupe de l'alocation de la
// mémoire du programme. Il faut donc connaitre la taille réele occupée en
// mémoire par chaque élément.

// taille mémoire rééle d'une Ville =
//      sizeof(Ville) + 
//      (nombre de villes dans le graphe - 1 au maximum) * sizeof(*Arc)
// NB : si le graph n'est pas complet on pourrait économiser de la mémoire
// car il peut y avoir moins de nombre de villes dans le graphe - 1 villes
// relié à chaque sommet.
// Comme ce n'est pas le cas ici, cela n'a pas été implémenté pour des raisons
// de facilitéessize_t sizeof_villes(int nb_ville)
size_t sizeof_one_ville(int nb_ville)
{

    return sizeof(Ville) + sizeof(Arc*)*(nb_ville - 1);
}


// taille mémoire rééle d'un arc =
//      sizeof(Arc)
size_t sizeof_one_arc(int nb_arc)
{
    return sizeof(Arc);
}
// taille mémoire rééle d'une fourmi =
//      sizeof(Fourmi)
//      + (nombre de villes dans le graphe) * sizeof(*Ville)
// nb : on a besoin d'en avoir deux en mémoire : la fourmi qui parcourt
// actuellement le graph et la meilleur fourmi
size_t sizeof_fourmi(int nb_ville)
{
    return sizeof(Fourmi) + nb_ville*sizeof(Ville*);
}

size_t sizeof_villes_visitee(int nb_ville)
{
    return nb_ville * sizeof(bool);
}

size_t sizeof_proba_ville(int nb_voisins_max)
{
    return nb_voisins_max*sizeof(float);
}

void* memory_allocator(Ville *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle,
    bool *(ville_visitees[]), float *(proba_ville[]), int nb_ville, int nb_arc)
{
    void *memory_pool;

    memory_pool = malloc (
          nb_ville*sizeof_one_ville(nb_ville)
        + nb_arc*sizeof_one_arc(nb_arc)
        + 2*sizeof_fourmi(nb_ville)
        + sizeof_villes_visitee(nb_ville)
        + sizeof_proba_ville(nb_arc)
            );
    // Sous linux c'est inutile vu que malloc renvoie toujours un pointeur
    if (memory_pool==NULL) {
        fprintf(stderr, "allocation error\n");
        return 0; 
    }

    // On fait correspondre chaque pointeur à son espace mémoire
    *villes           = (Ville*)                                memory_pool;
    *arcs             = (Arc*)    ( (void*)*villes             + nb_ville*sizeof_one_ville(nb_ville));
    *fourmi_actuelle  = (Fourmi*) ( (void*)*arcs               + nb_arc*sizeof_one_arc(nb_arc));
    *meilleure_fourmi = (Fourmi*) ( (void*)*fourmi_actuelle   + sizeof_fourmi(nb_ville));
    *ville_visitees   = (bool*)   ( (void*)*meilleure_fourmi    + sizeof_fourmi(nb_ville));
    *proba_ville      = (float*)  ( (void*)*ville_visitees   + sizeof_villes_visitee(nb_ville));

    return memory_pool;
}

void swap(void **p1, void **p2)
{
    void *tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


void read_villes(FILE *fp, Ville villes[], int nb_ville)
{
    int   i;

    flush_line(fp); // lire les mots "sommets du graphe"
    for (i = 0; i < nb_ville; i++) { // lire tous les info dans "sommets du graphe"  
        Ville *p_ville = get_in_villes(villes, i, nb_ville);

        fscanf(fp,"%d %lf %lf %s",&(p_ville->id_ville), &(p_ville->x), &(p_ville->y), p_ville->nom);
        p_ville->nb_voisins = 0;    // Pour l'instant, on ne connait pas les arcs voisins
    }
}


void read_arcs(FILE *fp, Arc arcs[], Ville villes[], int nb_ville, int nb_arc)
{
    int   noeud1, noeud2;    // noeud1 et noeud2 les deux ville d'une arrete
    int   i;

    // lecture des Arcs
    flush_line(fp); // lire les mots"Arêtes du graphe : noeud1 noeud2 valeur"
    for (i = 0; i < nb_arc; i++) { // lire toutes les info dans "sommets du graphe"  
        Arc   *p_arc = get_in_arcs(arcs, i);
        Ville *p_ville;

        fscanf(fp,"%d %d %lf", &noeud1, &noeud2, &(p_arc->distance));
        p_arc->pheromones = EPSILON_PHEROMONES;

        // on cherche la ville de départ et d'arrivée à partir de leurs identifiants
        // et on ajoute l'arc courant dans la liste des voisins
        // NB : les arcs sont supposé bi-directionnels
        p_ville = get_in_villes(villes,noeud1,nb_ville); // ville de départ
        p_ville->voisins[(p_ville->nb_voisins)++] = p_arc;
        p_arc->depart = (struct Ville*) p_ville;
        p_ville = get_in_villes(villes,noeud2,nb_ville); // ville d'arrivée
        p_ville->voisins[(p_ville->nb_voisins)++] = p_arc;
        p_arc->arrivee = (struct Ville*) p_ville;
    }
}

//Dans ce fichier on crÃ©e une graphe en lisant des texts GRAPHE donnÃ©s et ajouter des donner dans le tableau allouÃ©
void* creation_graph(const char *data_graph, Sommet *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle, bool *(ville_visitees[]), float *(proba_ville[]), int *nb_villes, int *nb_arc)
{
    void  *memory_pool;   /// pointeur sur la zone qui va contenir l'intégralité de la mémoire necessaire pour la simulation
    FILE  *fp;              /// fichier contenant les informations sur le graph

    fp = fopen(data_graph,"r");
    if(!fp) { // verifie si on peut ouvrir ce fichier
        fprintf(stderr, "can't open file\n");
        return 0;
    }

    fscanf(fp,"%d %d", nb_villes, nb_arc); // lire le nombre du sommet et le nombre d'arc

    // Désormais, on connait l'espace mémoire total à allouer
    // Du coup, on peut allouer toutes les données de manière contigues
    memory_pool = memory_allocator(villes, arcs, meilleure_fourmi, fourmi_actuelle, ville_visitees, proba_ville, *nb_villes, *nb_arc);
    if (memory_pool==NULL) { return 0; }

    read_villes(fp, *villes, *nb_villes);
    read_arcs(fp, *arcs, *villes, *nb_villes, *nb_arc);

    init_fourmi(*fourmi_actuelle , &((*villes)[0]));
    init_fourmi(*meilleure_fourmi, &((*villes)[0]));
    (*meilleure_fourmi)->L = FLT_MAX; // distance infinie

    print_graph(*villes, *arcs, *nb_villes, *nb_arc);

    fclose(fp);
    return memory_pool;
}

void print_arc(Arc *p_arc)
{
            Ville *p_depart = (Ville*) p_arc->depart;
            const char *nom_depart = p_depart->nom;
            Ville *p_arrivee = (Ville*) p_arc->arrivee;
            const char *nom_arrivee = p_arrivee->nom;
            printf("\t %lf %lf %s %s\n", p_arc->distance, p_arc->pheromones, nom_depart, nom_arrivee);
}

void print_graph(Sommet villes[], Arc arcs[], int nb_villes, int nb_voisins)
{
    int i,j;

    printf("Liste des Villes\n");
    for (i = 0; i < nb_villes; i++) {
        Ville *p_ville = get_in_villes(villes, i, nb_villes);
        printf("%d %lf %lf %s %d\n",p_ville->id_ville, p_ville->x, p_ville->y, p_ville->nom, p_ville->nb_voisins);
        for (j = 0; j < p_ville->nb_voisins; j++) {
            print_arc(p_ville->voisins[j]);
        }
        printf("\n");
    }


    printf("\n");

    printf("Liste des Arcs\n");
    for (i = 0; i < nb_voisins; i++) {
            print_arc(get_in_arcs(arcs, i));
    }
}