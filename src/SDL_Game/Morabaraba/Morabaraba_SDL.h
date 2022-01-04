#ifndef MORABARABA_SDL_H
#define MORABARABA_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef char* dynamicString;

typedef struct SDL_Mouse SDL_Mouse;
struct SDL_Mouse{
    int x, y;
    unsigned clickBuffer;
    unsigned click;
};

typedef struct SDL_Text SDL_Text;
struct SDL_Text{
    dynamicString text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
};

typedef struct SDL_Button SDL_Button;
struct SDL_Button{
    SDL_Rect rect;
    SDL_Color normal;
    SDL_Color clicked;
    SDL_Color hovered;
    bool state;
};

//SDL_mouse
void SDL_UpdateMouse(SDL_Mouse* mouse);
void SDL_UpdateMouseBuffer(SDL_Mouse* mouse);

/**
 * @brief Création d'une structure text avec tous les structures de la SDL
 * 
 * @param renderer structure SDL_Renderer
 * @param x position x du text
 * @param y position y du text
 * @param font police d'écriture
 * @param text chaine de caractère dynamic
 * @param color structure SDL_Color
 * @return Adresse de la strucure créer
 */
SDL_Text* SDL_CreateText(SDL_Renderer *renderer, int x, int y, TTF_Font *font, dynamicString text, SDL_Color color);
void SDL_UpdateText(SDL_Renderer *renderer, SDL_Text* text, int x, int y);

/**
 * @brief libère la mémoire occupé par SDL_Text
 * 
 * @param Text Adresse de la structure SDL_Text à désalouer
 */
void SDL_FreeText(SDL_Text* Text);

//SDL_Button
SDL_Button* SDL_CreateButton(int x, int y, int w, int h, SDL_Color normal, SDL_Color clicked, SDL_Color hovered);
void SDL_UpdateButton(SDL_Renderer* renderer, SDL_Button* button, SDL_Mouse* mouse);
void SDL_FreeButton(SDL_Button* button);

//SDL_Circle
void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);

//SDL_Rect
void SDL_SetRect(SDL_Rect* rect, int x, int y, int w, int h);

#endif