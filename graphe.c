#include "main.h"
#include <stdio.h>
//Dans ce fichier on crÃ©e une graphe en lisant des texts GRAPHE donnÃ©s et ajouter des donner dans le tableau allouÃ©
Graph *creation_graph (FILE *data_graph, int n, Sommet *som, Arc *arc)
{
    int nbsommet,nbarc,c,noeud1,noeud2;//nbarc est le nombre d'arret a lire,noeud1 et noeud2 les deux ville d'une arrete
    int i;//i parcours le fichier
    char mot[256],nom_sommet;//mot[256] est la variable pour lire les lignes inutiles
    double d,e,valeur;
    FILE *fp=fopen("data_graph","r");
    if(!fp) { //verifie si on peut ouvrir ce fichier
        printf("can't open file\n");
        return 0;
    }

    fscanf(fp,"%d %d",&nbsommet,&nbarc);//lire le nombre du sommet et le nombre de l'arc
    fgets(mot,256,fp);//lire les mots"sommets du graphe"

    for (i=0, i<nbsommet, i++) { //lire tous les info dans "sommets du graphe"   
        fscanf(fp,"%d %lf %lf %s",&c,&d,&e,&nom_sommet);
        som=calloc(nbsommet,sizeof(*som));
        if (som==NULL){return 0;}
        som[i]->numero=c;
        som[i]->x=d;
        som[i]->y=e;
        som[i]->nom=nom_sommet;
    }

    fgets(mot,256,fp);//lire les mots"Arêtes du graphe : noeud1 noeud2 valeur"

    for (i=0, i<nbarc, i++) { //lire tous les info dans "Arêtes du graphe"
        fpscanf(fp,"%d %d %lf",&noeud1,&noeud2,&valeur);
        arc=calloc(nbarc,sizeof(*arc));
        if (arc==NULL){return 0;}
        arc[i]->depart=noeud1;
        arc[i]->arrivee=noeud2;
        arc[i]->d=valeur;
    }
}
