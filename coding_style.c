/*
 * Un lien vers un coding style très cohérent.
 * http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html
 *
 * Voici un exemple de code pour résumer ce document
 */


/* Résumé :
 * nom de constantes : en majuscules
 * type : première lettre en majuscule
 * variables globales : préfixé par « g_ » et à utilisé le moins possible
 * si plusieurs mots dans un identifiant : séparation par des underscore (_)
 * des nom explicites
 *
 * pas d'espace avant les nom de fonctions
 * un espace avant les mots clés
 *
 * Tout les programmes doivent compiler sans warning. Si un warning est justifié,
 * il doit être expliqué au niveau de la ligne causant problème.
 * 
 * 80 colonnes max
 * 1 écran de haut max par fonction
 * 
 * accolades : ouvrante sur la même ligne (sauf pour les fonctions, fermantes sur la ligne suivante
 * identation : 4 espaces après chaque accolades
 */
 
/* ********** */


/* define
 * vu que les compilateur pour l'embarqué ne sont pas très optimisé, on utilise des defines pour les constantes
 * tout en majuscule avec des «_» pour les séparations
 * À mettre après les includes, mais en début de fichier, dans les headers (les fichiers .h)
 * le nom doit être explicite (on ne doit pas avoir besoin de commentaire pour les comprendre)
 */
#define CONSTANTE 10        /* c'est un mauvais nom */
#define TEMPS_MAX 100
#define BOUTON_ENFONCE 0
#define BOUTON_RELACHE 1


/* variable globales
 * à utiliser **le moins possible**
 * préfixé par « g_»
 */
int g_compteur;
int g_variable_globale;


/* nom des stucture, unions et enum
 * premiere lettre en majuscule
 * si plusieurs mots, séparation par des underscores
 *
 * nom des elements d'une structure ou d'une union : voir variable
 * nom des elements d'une enum : comme les constantes
 */
typedef struct {
    float x;
    float y;
    const char *chaine_de_caracteres;
} Ma_stucture, *Adresse_structure;
union {
    int_32 entier;
    char octet[4];
};
enum Etat_des_pins {
    PIN_OFF,
    PIN_ON
};


/* nom de fonction
 * Tout en minuscule
 * utiliser des « _ » comme séparateurs
 * rendre l'action explicite
 * jamais d'espace avant les parentèses
 */
int max();
void ecrire_dans_fichier(FILE *fichier, char *chaine);
void faire_quelquechose();
void faire_quelquechose_d_autre();
void affiche_erreur(const char *message);


/* les accolades
 * pour les fonction, on revient à la ligne
 * pour les mots clé, voir plus bas
 */
int main (void)
{
    /* nom des variable
     * tout en minuscule
     * utiliser des « _ » comme séparateurs
     * unités du système international postfixé
     * une déclaration par ligne (pour la doc)
     */
    int i;                              /* variable de boucle */
    int variable_avec_plusieur_mot;     /* nom explicite */
    int timer_ms;                       /* avec unités */

    /* pointers
     * on place l'étoile à coté du nom de la variable
     */
    char *adresse;
    char *chaine_de_caracteres;

    /* les tests
     * on évite l'utilisation de «constante magique», et on préfere des defines
     *
     * les accolades
     * sur la même ligne que le mot clé
     */
    if (i == BOUTON_ENFONCE) {
        faire_quelquechose();
    } else if (i == BOUTON_RELACHE) {
        faire_quelquechose_d_autre();
    } else {
        affiche_erreur("valeure impossible");
    }

    /* les accolades (exemple 2) */
    while (timer_ms < TEMPS_MAX) {
        faire_quelquechose();
    }

    return 0;
}


/* considérations générales
 * quatre espaces pour l'alignement
 * on n'oublie pas de mettre des lignes vides en fin de fichier
 * une fonction doit être courte (max un écran de haut) (pour faciliter la lecture)
 * il ne doit pas y avoir plus de 80 caractères par ligne (pour faciliter la lecture)
 * une action par ligne (soit un point virgule)
 * on teste le retour des fonctions (ex: calloc() )
 *
 * un espace après un mot clé «if» «while» «for» «int», etc
 * pas d'espace après une fonction (lors de l'utilisation)
 * ex : ma_fonction(param1, param2);
 *
 * pour la doc, on utilisera Doxygen, main je détaillerai ça plus tard
 */


