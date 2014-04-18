#ifndef MAIN_H
#define MAIN_H

// C/C++ File
// AUTHOR:   robin_arch
// FILE:     main.h
// ROLE:     TODO (some explanation)
// CREATED:  2014-04-04 08:04:06
// MODIFIED: 2014-04-04 08:04:06

struct Sommet;
typedef struct {
    float d;            /// < Distance entre les villes i et j
    float visibilite;   /// < Quantité de phéromones sur l'arc a
    struct Sommet *depart;      /// < Sommet de départ (ville i)
    struct Sommet *arrivee;  /// < Sommet d'arrivée (ville j)
} Arc;

typedef struct {
	int numero;			/// le numéro du sommet
	int nom;            /// le nom du sommet
	float x,y;          /// positions du sommet (pour la representation graphique du graphe).
	Arc *voisins[];		/// la liste d'adjacence, liste de pointeurs vers les arcs sortant de ce sommet
    const char nom[64]; /// < Nom de la ville
} Sommet;

typedef Ville Sommet;

typedef Ville Graph;  /// < Un graph est un tableau de ville

// paramètres de la simulation
typedef struct {
    int nb_fourmi;  /// < nombre total de fourmis de l'algorithme
    int nb_villes;  /// < nombre de villes dans le graphe
    Graph graph[];  /// < L'ensemble des villes
    float alpha;    /// < Coefficient régulant l'importance des phéromones pour le choix d'une ville
    float beta;     /// < Coefficient régulant l'importance de la visibilité pour le choix d'une ville
    float epsilon;  /// < Valeur initiale non nulle de phéromones sur les arcs
    float rho;      /// < Coefficient d'évaporation des phéromones
    float Q;        /// < Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi
} Parametres;

Graph meilleur_parcourt;

/// Constante, nombre maximum de cycles autorisés.
#define MAX_C   200

typedef struct {
    Graph tabu[];      /// < Liste des villes déjà parcourues par la fourmi k
    float L;           /// < Longueur d'un chemin, somme des longueurs de chaque arc constituant le chemin
	Parametres *param; /// < Pointeur sur les paramètres de la simulation
} Fourmi;

///////////
// graph //
///////////

/** Initialise le graph à partir des données contenu dans le fichier data_graph.
 * \param n out : Nombre de ville contenu dans le graph (indiqué dans le fichier data_graph)
 */
Graph *creation_graph(FILE *data_graph, Parametres parametres);

/** Initialise les paramètres de la simulation
 */
Parametres init_param(int m, float alpha, float beta, float epsilon, float rho, float Q);

/** Lance la simulation
 */
void run_simu(Parametres *p, Graph g);

/////////////
// fourmis //
/////////////

/** Fabrique une nouvelle fourmis
 * \param param const Les paramètres de la fonction
 */
Fourmi init_fourmi(Parametres *param);

/** Déplace la fourmi dans la nouvelle ville, en fonction de sa visibilité et des phéromones sur l'arc
 * \param f La fourmi en train d'effectuer son voyage
 * \param p const Les paramètres de la simulation
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi f, Parametres *p);

/** Valide le parcourt d'une fourmi
 * \param p const Les paramètres de la simulation
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi f, Parametres *p);

/** Met à jour le meilleur parcourt si celui de la fourmi est meilleur
 * \param p const Les paramètres de la simulation
 */
void (Fourmi f, Graph *meilleur_parcourt);

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
 */
void graph_update(Fourmi f, Graph *g);


#endif /* MAIN_H */
