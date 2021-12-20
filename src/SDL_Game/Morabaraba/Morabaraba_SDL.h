#ifndef MORABARABA_SDL_H
#define MORABARABA_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct SDL_Mouse SDL_Mouse;
struct SDL_Mouse{
    int x, y;
    unsigned click;
};

typedef struct SDL_Text SDL_Text;
struct SDL_Text{
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

//SDL_Text
SDL_Text* SDL_CreateText(SDL_Renderer *renderer, int x, int y, TTF_Font *font, char* text, SDL_Color color);
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