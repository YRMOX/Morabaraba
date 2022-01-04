#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char currentPath[20];
    strcpy(currentPath, argv[0]);
    int i=0;
    while(currentPath[i]!='M') i++;
    currentPath[i] = '\0';

    char command[40] = "start ";
    char command2[40];
    char temp[20] = "SDL_Game.exe";
    char temp2[20] = " lastsave";
    strcat(command, currentPath);
    strcat(command, temp);
    strcpy(command2, command);
    strcat(command2, temp2);
    printf("Choisissez un Mode d'execution:\n\t1) SDL_Game\n\t2) SDL_Game + lastSave\n>>> ");
    int response = 0;
    scanf("%i", &response);
    switch (response)
    {
    case 1:
        system(command);
        break;
    
    case 2:
        system(command2);
        break;

    default:
        system(command);
        break;
    }
    return 0;
}