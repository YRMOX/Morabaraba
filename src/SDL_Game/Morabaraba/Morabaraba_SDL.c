#include "Morabaraba_SDL.h"
#include <stdio.h>
#include <math.h>

void SDL_UpdateMouse(SDL_Mouse* mouse){
        mouse->click = SDL_GetMouseState(&mouse->x, &mouse->y);
}

SDL_Text* SDL_CreateText(SDL_Renderer *renderer, int x, int y, TTF_Font *font, char* text, SDL_Color color){
    SDL_Text* temp_text = malloc(sizeof(SDL_Text));
    temp_text->surface = TTF_RenderText_Solid(font, text, color);
    temp_text->texture = SDL_CreateTextureFromSurface(renderer, temp_text->surface);
    int x2, y2;
    SDL_QueryTexture(temp_text->texture, NULL, NULL, &x2, &y2);
    temp_text->rect.x = x;
    temp_text->rect.y = y;
    temp_text->rect.w = x2/20;
    temp_text->rect.h = y2/20;
    return temp_text;
}

void SDL_FreeText(SDL_Text* Text){
    SDL_FreeSurface(Text->surface);
    SDL_DestroyTexture(Text->texture);
}

SDL_Button* SDL_CreateButton(int x, int y, int w, int h, SDL_Color normal, SDL_Color clicked, SDL_Color hovered){
    SDL_Button* temp_button = malloc(sizeof(SDL_Button));
    temp_button->rect.x = x;
    temp_button->rect.y = y;
    temp_button->rect.w = w;
    temp_button->rect.h = h;
    temp_button->normal = normal;
    temp_button->clicked = clicked;
    temp_button->hovered = hovered;
    return temp_button;
}

void SDL_UpdateButton(SDL_Renderer* renderer, SDL_Button* button, SDL_Mouse* mouse){
    if((mouse->x >= button->rect.x) && (mouse->x <= button->rect.x+button->rect.w) && (mouse->y >= button->rect.y) && (mouse->y <= button->rect.y+button->rect.h)){
            button->state = false;
            SDL_SetRenderDrawColor(renderer, button->hovered.r, button->hovered.g, button->hovered.b, button->hovered.a);
            if(mouse->click == SDL_BUTTON_LMASK) {
                button->state = true;
                SDL_SetRenderDrawColor(renderer, button->clicked.r, button->clicked.g, button->clicked.b, button->clicked.a);
            }
    }else{
        button->state = false;
        SDL_SetRenderDrawColor(renderer, button->normal.r, button->normal.g, button->normal.b, button->normal.a);
    }
    SDL_RenderFillRect(renderer, &button->rect);
}

void SDL_FreeButton(SDL_Button* button){
    free(button);
}

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, float radius){
    int renderW, renderH;
    SDL_GetRendererOutputSize(renderer, &renderW, &renderH);
    radius = (int)(renderW/7*radius);
    int offsetX, offsetY, d;
    offsetX = 0;
    offsetY = radius;
    d = radius-1;
    while (offsetY >= offsetX){
        SDL_RenderDrawLine(renderer, x-offsetY, y+offsetX, x+offsetY, y+offsetX);
        SDL_RenderDrawLine(renderer, x-offsetX, y+offsetY, x+offsetX, y+offsetY);
        SDL_RenderDrawLine(renderer, x-offsetX, y-offsetY, x+offsetX, y-offsetY);
        SDL_RenderDrawLine(renderer, x-offsetY, y-offsetX, x+offsetY, y-offsetX);
        if (d >= 2*offsetX) {
            d -= 2*offsetX + 1;
            offsetX +=1;
        }
        else if (d < 2 * (radius - offsetY)) {
            d += 2 * offsetY - 1;
            offsetY -= 1;
        }
        else {
            d += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
    }
}