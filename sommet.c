#include "sommet.h"
#include <stdio.h>

//Dans ce fichier on créer un graph en lisant des texts GRAPHE donnés et ajouté des données dans le tableau alloué
GRAPH *creation_graph (char *data_graph, int *nb_villes)
{
    int nbarc,c,noeud1,noeud2;//nbarc est le nombre d'arrete a lire,noeud1 et noeud2 les deux ville d'une arrete
    int i;//i parcours le fichier
    char mot[256],nom_sommet[256];//mot[256] est la variable pour lire les lignes inutiles
    double d,e,distance;
    FILE *fp=fopen(data_graph,"r");
    if(!fp)//verifie si on peut ouvrir ce fichier
    {
        printf("can't open file\n");
        return -1;
    }

    fscanf(fp,"%d %d",nb_villes,&nbarc);//lire le nombre du sommet et le nombre de l'arc
    fgets(mot,256,fp);//lire les mots"sommets du graphe"
    GRAPH som=calloc(nb_villes,sizeof(*som));//alloue le tableau de ville

    for (i=0, i<nb_villes, i++)//lire tous les info dans "sommets du graphe"
    {   fscanf(fp,"%d %lf %lf %s",&c,&d,&e,&nom_sommet);
        som[i].numero=c;
        som[i].x=d;
        som[i].y=e;
        som[i].nom=nom_sommet;
    }

    fgets(mot,256,fp);//lire les mots"Arètes du graphe : noeud1 noeud2 valeur"

    for (i=0, i<nbarc, i++)//lire tous les info dans "Arètes du graphe"
    {   fscanf(fp,"%d %d %lf",&noeud1,&noeud2,&distance);
        som[i].voisin=arrete(noeud1, noeud2, Distance, som[i].voisin);
    }
    return som;
}
