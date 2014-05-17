
#include <stdlib.h>

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
// de facilitées
size_t sizeof_ville(int nb_ville)
{
    return sizeof(Ville) + sizeof(Arc*)*(nb_ville - 1);
}



// taille mémoire rééle d'un arc =
//      sizeof(Arc)
size_t sizeof_arcs()
{
    return sizeof(Arc); // l'ensemble des arcs
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

size_t sizeof_ville_visitees(int nb_ville)
{
    return nb_ville * sizeof(bool);
}

void* memory_allocator(Sommet *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle, bool *(ville_visitees[]), int *nb_ville)
{
    void *global_memory;

    global_memory = malloc (
          sizeof_ville(*nb_ville)
        + sizeof_arcs()
        + sizeof_fourmi(*nb_ville)
        + sizeof_ville_visitees(*nb_ville)
            );
    // Sous linux c'est inutile vu que malloc renvoie toujours un pointeur
    if (global_memory==NULL) {
        fprintf(stderr, "allocation error\n");
        return 0; 
    }

    // On fait correspondre chaque pointeur à son espace mémoire
    *villes           = (Ville*)                                global_memory;
    *arcs             = (Arc*)    ( (void*)*villes             + sizeof_ville(*nb_ville));
    *fourmi_actuelle  = (Fourmi*) ( (void*)*arcs               + sizeof_arcs());
    *meilleure_fourmi = (Fourmi*) ( (void*)*fourmi_actuelle    + sizeof_fourmi(*nb_ville));
    *ville_visitees   = (bool*)   ( (void*)*meilleure_fourmi   + sizeof_fourmi(*nb_ville));

    return global_memory;
}


void read_villes(FILE *fp, Ville villes[], int nb_ville)
{
    int   i;

    flush_line(fp); // lire les mots "sommets du graphe"
    for (i = 0; i < nb_ville; i++) { // lire tous les info dans "sommets du graphe"  
        Ville *p_ville = get_in_villes(villes, i, nb_ville);

        fscanf(fp,"%d %lf %lf %s",&(p_ville->id_sommet), &(p_ville->x), &(p_ville->y), p_ville->nom);
        p_ville->nb_voisins = 0;    // Pour l'instant, on ne connait pas les arcs voisins
    }
}


void read_arcs(FILE *fp, Arc arcs[], Ville villes[], int nb_ville)
{
    int   noeud1, noeud2;    // noeud1 et noeud2 les deux ville d'une arrete
    int   i;

    // lecture des Arcs
    flush_line(fp); // lire les mots"Arêtes du graphe : noeud1 noeud2 valeur"
    for (i = 0; i < nb_ville; i++) { // lire toutes les info dans "sommets du graphe"  
        Arc   *p_arc = get_in_arcs(arcs, i);
        Ville *p_ville;

        fscanf(fp,"%d %d %lf", &noeud1, &noeud2, &(p_arc->distance));
        p_arc->pheromones = EPSILON_PHEROMONES;

        // on cherche la ville de départ et d'arrivée à partir de leurs identifiants
        // et on ajoute l'arc courant dans la liste des voisins
        // NB : les arcs sont supposé bi-directionnels
        p_ville = get_in_villes(villes,noeud1,nb_ville); // ville de départ
        p_ville->voisins[++(p_ville->nb_voisins)] = p_arc;
        p_ville = get_in_villes(villes,noeud2,nb_ville); // ville d'arrivée
        p_ville->voisins[++(p_ville->nb_voisins)] = p_arc;
    }
}

//Dans ce fichier on crÃ©e une graphe en lisant des texts GRAPHE donnÃ©s et ajouter des donner dans le tableau allouÃ©
void* creation_graph(const char *data_graph, Sommet *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle, bool *(ville_visitees[]), int *nb_villes)
{
    int   nb_arc;           /// nombre d'arc dans la simulation
    void  *global_memory;   /// pointeur sur la zone qui va contenir l'intégralité de la mémoire necessaire pour la simulation
    FILE  *fp;              /// fichier contenant les informations sur le graph

    fp = fopen(data_graph,"r");
    if(!fp) { // verifie si on peut ouvrir ce fichier
        fprintf(stderr, "can't open file\n");
        return 0;
    }

    fscanf(fp,"%d %d", nb_villes, &nb_arc); // lire le nombre du sommet et le nombre d'arc

    // Désormais, on connait l'espace mémoire total à allouer
    // Du coup, on peut allouer toutes les données de manière contigues
    global_memory = memory_allocator(villes, arcs, meilleure_fourmi, fourmi_actuelle,ville_visitees, nb_villes);
    if (global_memory==NULL) { return 0; }

    read_villes(fp, *villes, *nb_villes);
    read_arcs(fp, *arcs, *villes, *nb_villes);

    init_fourmi(*meilleure_fourmi, &((*villes)[0]));
    init_fourmi(*fourmi_actuelle , &((*villes)[0]));

    print_graph(*villes, *arcs, *nb_villes, nb_arc);

    fclose(fp);
    return global_memory;
}

void print_graph(Sommet villes[], Arc arcs[], int nb_villes, int nb_voisins)
{
    int i,j;

    printf("Liste des Villes\n");
    for (i = 0; i < nb_villes; i++) {
        Ville *p_ville = get_in_villes(villes, i, nb_villes);
        printf("%d %lf %lf %s %d",&(p_ville->id_sommet), &(p_ville->x), &(p_ville->y), p_ville->nom, p_ville->nb_voisins);
        for (j = 0; j < p_ville->nb_voisins; i++) {
            Arc *p_arc = &(p_ville->voisins[i]);
            Ville *p_depart = p_arc->depart;
            const char *nom = p_depart->nom;
            printf("\t%d %lf %lf %s %s\n", p_arc->distance, p_arc->pheromones, nom, ((Ville*) p_arc->arrivee)->nom);
        }
        printf("\n");
    }


    printf("\n");

    printf("Liste des Arcs\n");
    for (j = 0; j < nb_voisins; i++) {
        Arc *p_arc = get_in_arcs(arcs, i);
        const char *nom = ((Ville*) p_arc->depart)->nom;
        printf("\t%d %lf %lf %s %s\n", p_arc->distance, p_arc->pheromones, nom, ((Ville*) p_arc->arrivee)->nom);
    }
}