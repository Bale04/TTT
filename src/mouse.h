/*
 ============================================================================
 Name        : mouse.h
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Description : Libreria condivisa per la gestione del mouse e del cursore del terminale.
 ============================================================================
 */

#ifndef mouse_H
#define mouse_H

#include "strutture.h"


#ifdef _WIN32
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <stdio.h>
#endif


// posizione base del cursore nel terminale (dopo ogni input)
#define CURSORE_BASE ((Cursore){1, 25})

// gestisce lo spostamento del cursore al click
static inline void goTo(int x, int y) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
    SetConsoleCursorPosition(h, pos);
#else
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

// blocca finché non riceve un click sinistro del mouse. Restituisce 1 se il click è valido, 0 in caso di errore.
#ifdef _WIN32
static inline int leggiClick(int *riga, int *colonna) {
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ev;
    DWORD cnt;
    while (1) {
        ReadConsoleInput(h, &ev, 1, &cnt);
        if (ev.EventType == MOUSE_EVENT &&
            ev.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            *colonna = ev.Event.MouseEvent.dwMousePosition.X + 1;
            *riga    = ev.Event.MouseEvent.dwMousePosition.Y + 1;
            goTo(*colonna, *riga);
            return 1;
        }
    }
}
#else
static inline int leggiClick(int *riga, int *colonna) {
    char sequenza[32];
    int indice;
    while (1) {
        if (read(STDIN_FILENO, sequenza, 1) != 1) return 0;
        if (sequenza[0] != '\033') continue;
        if (read(STDIN_FILENO, sequenza, 1) != 1 || sequenza[0] != '[') continue;
        if (read(STDIN_FILENO, sequenza, 1) != 1 || sequenza[0] != '<') continue;
        indice = 0;
        while (indice < 30) {
            if (read(STDIN_FILENO, &sequenza[indice], 1) != 1) break;
            if (sequenza[indice] == 'M' || sequenza[indice] == 'm') {
                sequenza[indice + 1] = '\0';
                break;
            }
            indice= indice +1;
        }
        if (sequenza[indice] == 'M') {
            int bottone, col, rig;
            if (sscanf(sequenza, "%d;%d;%d", &bottone, &col, &rig) == 3 &&
                bottone == 0) {
                *colonna = col;
                *riga    = rig;
                goTo(*colonna, *riga);
                return 1;
            }
        }
    }
}
#endif

// funzione di abilitazione del mouse
static inline void abilitaMouse(void) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
#else
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    printf("\033[?1000h\033[?1006h");
    fflush(stdout);
#endif
}

// abilita l'input da tastiera
static inline void abilitaTastiera(void) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT |
                      ENABLE_PROCESSED_INPUT);
#else
    printf("\033[?1000l\033[?1006l");
    fflush(stdout);
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

// controlla se il click corrisponde all'area cliccabile
static inline int areaCliccata(AreaCliccabile area, int riga, int colonna) {
    return (riga == area.r && colonna >= area.c1 && colonna <= area.c2);
}

#endif 
