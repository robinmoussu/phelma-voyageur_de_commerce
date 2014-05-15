#include "main.h"
#include <stdio.h>
Graph *creation_graph (FILE *data_graph, int n)
{
    int nbsommet,nbarc,c,noeud1,noeud2;
    int i;
    char mot[256],nom_sommet;
    double d,e,valeur;
    Sommet *som=NULL;
    Arc *arc=NULL;
    FILE *fp=fopen("data_graph","r");
    if(!fp)//verifie si on peut ouvrir ce fichier
    {
        printf("can't open file\n");
        return -1;
    }

    fscanf(fp,"%d %d",&nbsommet,&nbarc);//lire le nombre du sommet et le nombre de l'arc
    fgets(mot,256,fp);//lire les mots"sommets du graphe"

    for (i=0, i<nbsommet, i++)//lire tous les info dans "sommets du graphe"
    {   fscanf(fp,"%d %lf %lf %s",&c,&d,&e,&nom_sommet);
        som=calloc(nbsommet,sizeof(*som));
        if (som==NULL){return 0;}
        som[i]->numero=c;
        som[i].x=d;
        som[i].y=e;
        som[i].nom=nom_sommet;
    }

    fgets(mot,256,fp);//lire les mots"Arêtes du graphe : noeud1 noeud2 valeur"

    for (i=0, i<nbarc, i++)//lire tous les info dans "Arêtes du graphe"
    {   fscanf(fp,"%d %d %lf",&noeud1,&noeud2,&valeur);
        arc=calloc(nbarc,sizeof(*arc));
        if (arc==NULL){return 0;}
        arc[i].depart=noeud1;
        arc[i].arrivee=noeud2;
        arc[i].d=valeur;
    }
}

Parametres init_param(int m, float alpha, float beta, float epsilon, float rho, float Q)
{



}


void run_simu(Parametres *p, Graph g)
{




}
