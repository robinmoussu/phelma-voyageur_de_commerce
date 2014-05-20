/*
 *    Voyageur de commerce
 *    Copyright (C) 2014 Robin Moussu - Jingbo Su
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef MAIN_H
#define MAIN_H

/** \file main.h
 * \brief Contient les paramètres de la simulation, ainsi que les options de tests.
 * \note Doit etre inclu dans tout les fichirs du projet.
 */

/** \def ON_DEBUG
 *  \brief Ligne de code exécutée uniquement si le débug est actif
 *  \param instuction Instruction à exécuter
 *
 *  La constante DEBUG permet d'activer toutes les options de débug si elle est définie à une valeur autre que 0.
 */

/** \def ON_VERBOSE
 *  \brief Ligne de code exécutée uniquement si le le programme est bavard
 *  \param instuction Instruction à exécuter
 *
 *  La constante VERBOSE permet de rendre le programme bavard si elle est définie à une valeur autre que 0.
 *  \note DEBUG active également cette macro.
 */

// Les lignes suivantes permettent d'activer le débug.
// Pour cela, on peut utiliser la commande "make debug" ou définir DEBUG à une valeur non nulle
// En mode debug, le programme est également bavard !
#if (DEBUG == 0)
#define ON_DEBUG(instruction)
#else
#define ON_DEBUG(instruction) instruction
#define VERBOSE 1
#endif // DEBUG

#if (VERBOSE == 0)
#define ON_VERBOSE(instruction)
#else
#define ON_VERBOSE(instruction) instruction
#endif // VERBOSE

// Pour l'utilisation en c89
#ifndef bool
typedef enum {false,true} bool;
#endif


#define NB_FOURMIS          300         ///< Nombre de fourmis parcourant le graph en meme temps
#define MAX_C               100         ///< Nombre maximum de cycles autorisés

#define ALPHA               1           ///< Coefficient régulant l'importance des phéromones pour le choix d'une ville
#define BETA                10          ///< Coefficient régulant l'importance de la visibilité pour le choix d'une ville

#define EPSILON_PHEROMONES  0.00001     ///< Valeur initiale non nulle de phéromones sur les arc (epsilon dans le sujet)
#define DEPOT_PHEROMONES    10          ///< Quantitée de phéromones ajoutés à chaque passage (Q dans le sujet)
#define EVAPORATION         0.4         ///< Coeficiant d'évaporation (rho dans le sujet)

#endif /* MAIN_H */
