#ifndef MORABARABA_FRAME_H
#define MORABARABA_FRAME_H

/**
 * @brief structure de chaque case du Morabaraba
 */
typedef struct Frame Frame;
#include "Morabaraba.h"
#include "Morabaraba_SDL.h"
#include "stdbool.h"

#define MAX_NEIGHBOR 4

struct Frame{
    int x, y;
    int value;
    Frame** neighbor;
    bool isSelected;
    bool isMoving;
    bool isProtected;
    SDL_Rect rect;
    SDL_Renderer* renderer;
};

/**
 * @brief Crée une case et initialise les valeurs et la position de la case dans
 * la grille
 * 
 * @param morabaraba structure morabaraba pour l'affichage
 * @param x position x de la case dans la grille
 * @param y position y de la case dans la grille
 * @return Adresse de la case après allocation et initialisation
 */
Frame* CreateFrame(Morabaraba* morabaraba, int x, int y);

/**
 * @brief Recherche une Case dans un tableau de Case et renvoie sa position
 * 
 * @param frame Case à recherché
 * @param frames tableau de case dans lequel chercher
 * @return position de la case dans le tableau
 */
int IndexInFrames(Frame* frame, Frame** frames);

/**
 * @brief libère la mémoire occupé par une case
 * 
 * @param mill Case à désallouer
 */
void FreeFrame(Frame* frame);

/**
 * @brief Crée un tableau de structure Case
 * 
 * @param size taille du tableau
 * @return Adresse du tableau dynamique de Case
 */
Frame** CreateFrames(int size);

/**
 * @brief libère la mémoire occupé par un tableau dynamique de Case
 * 
 * @param mills tableau dynamique de Case
 * @param size taille du tableau
 */
void FreeFrames(Frame** frames, int size);

/**
 * @brief Crée un matrice de structure Case
 * 
 * @param morabaraba structure Morabaraba dans laquel est stocké le renderer
 * @param size taille de la matrice
 * @return Adresse de la matrice dynamique de Case
 */
Frame*** CreateFrameArray(int size);

/**
 * @brief libère la mémoire occupé par une matrice dynamique de Case
 * 
 * @param mills matrice dynamique de Case
 * @param size taille de la matrice
 */
void FreeFrameArray(Frame*** array, int size);

/**
 * @brief Affiche les coordonnés de tous les Voisin d'une case
 * 
 * @param frame case contenant les donnés des voisins
 */
void PrintNeighbor(Frame* frame);

/**
 * @brief Ajouté un voisin à la liste des voisins d'une case
 * 
 * @param frame case contenant la liste des voisins
 * @param frameToAppend case a ajouté à la liste des voisins
 */
void AppendNeighbor(Frame* frame, Frame* frameToAppend);

/**
 * @brief Vérifie si il y a bien une case  x, y voisin de la case donné
 * 
 * @param x position de la case a cherché en x
 * @param y position de la case a charché en y
 * @param frame case qui contient la liste des voisins dans laquel chercher
 * @return vrai si il y a au moins une case de coordonnée x, y dans les voisins
 * @return faux si il n'y a pas de case de coordonnée x, y dans les voisins
 */
bool IsInNeighbor(int x, int y, Frame* frame);

/**
 * @brief Mise à jour d'un case du point de vue donné et graphique
 * 
 * @param morabaraba Morabaraba qui contient les informations pour l'affichage
 * @param frame case à mettre à jour
 * @param mouse structure souris qui permet de savoir si la case est cliquer
 */
void SDL_UpdateFrame(Morabaraba* morabaraba, Frame *frame, SDL_Mouse* mouse);

/**
 * @brief Mise à jour de toutes les cases d'une matrice
 * 
 * @param morabaraba Morabaraba qui contient la matrice
 * @param mouse structure souris qui permet de savoir si la case est cliquer
 */
void SDL_UpdateAllFrame(Morabaraba* morabaraba, SDL_Mouse* mouse);

#endif