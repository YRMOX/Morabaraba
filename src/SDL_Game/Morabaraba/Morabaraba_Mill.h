#ifndef MORABARABA_MILL_H
#define MORABARABA_MILL_H

#define MILLSIZE 3

/**
 * @brief Structure qui stocke un groupe de case représentent un moulin
 * 
 */
typedef struct Mill Mill;
#include "Morabaraba_Frame.h"
#include <stdbool.h>

struct Mill{
    Frame** frames;
};

/**
 * @brief Crée une structure moulin et initialise ces valeurs
 * 
 * @return Adresse de la structure Moulin créer
 */
Mill* CreateMill();

/**
 * @brief vérifie si la case donné est bien le centre d'un moulin, si oui elle
 * crée un Moulin et le retourne
 * 
 * @param middle Case au centre du Moulin
 * 
 * @return Adresse de la structure Moulin créer
 */
Mill* SearchMill(Frame* middle);

/**
 * @brief vérifie si un Moulin crée est encore valide
 * 
 * @param mill Adresse de la structure Moulin à vérifié
 * 
 * @return vrai si le Moulin est toujours un Moulin
 * @return faux si le Moulin à été détruit
 */
bool CheckMill(Mill* mill);

/**
 * @brief copie une structure Moulin dans une autre
 * 
 * @param millA Moulin destinataire
 * @param millB Moulin source
 */
void CopyMill(Mill* millA, Mill* millB);

/**
 * @brief compare les Moulins
 * 
 * @param millA MoulinA
 * @param millB MoulinB
 * @return vrai si les moulins sont équaux
 * @return faux si les moulins sont différents
 */
bool CmpMill(Mill* millA, Mill* millB);

/**
 * @brief libère la mémoire occupé par un Moulin
 * 
 * @param mill Moulin à désallouer
 */
void FreeMill(Mill* mill);

/**
 * @brief Crée un tableau de structure Moulin
 * 
 * @param size taille du tableau
 * @return Adresse du tableau dynamique de Moulin
 */
Mill** CreateMills(int size);

/**
 * @brief Recherche un Moulin dans un tableau de Moulin et renvoie sa position
 * 
 * @param mill Moulin à recherché
 * @param mills tableau de Moulin dans lequel chercher
 * @return la position du Moulin dans le tableau
 */
int IndexInMills(Mill* mill, Mill** mills);

/**
 * @brief libère la mémoire occupé par un tableau dynamique de Moulin
 * 
 * @param mills tableau dynamique de Moulin
 * @param size taille du tableau
 */
void FreeMills(Mill** mills, int size);

#endif