/*
 ============================================================================
 Name        : mouse.h
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Description : Libreria condivisa per la gestione del mouse e del cursore del terminale.
 ============================================================================
 */

#ifndef MOUSE_H
#define MOUSE_H

#include "costanti.h"
#include "strutture.h"

#ifdef _WIN32
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <stdio.h>
#endif

// posizione base del cursore nel terminale (dopo ogni input)
#define CURSOR_BASE ((Cursor){1, 25})

// gestisce lo spostamento del cursore al click
static inline void goto_xy(int x, int y)
{
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
    SetConsoleCursorPosition(h, pos);
#else
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

// funzione di abilitazione del mouse
static inline void enable_mouse(void)
{
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    if (GetConsoleMode(h, &mode)) {
        mode = (mode | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;
        SetConsoleMode(h, mode);
    }
#else
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    printf("\033[?1000h\033[?1006h");
    fflush(stdout);
#endif
}

// blocca finche' non riceve un click sinistro del mouse. Restituisce 1 se il click e' valido, 0 in caso di errore.
#ifdef _WIN32
static inline int read_click(int *row, int *col)
{
    enable_mouse();
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ev;
    DWORD cnt;
    while (1) {
        ReadConsoleInput(h, &ev, 1, &cnt);
        if (ev.EventType == MOUSE_EVENT &&
            ev.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            *col = ev.Event.MouseEvent.dwMousePosition.X + 1;
            *row = ev.Event.MouseEvent.dwMousePosition.Y + 1;
            goto_xy(*col, *row);
            return 1;
        }
    }
}
#else
static inline int read_click(int *row, int *col)
{
    char sequence[32];
    int index;
    while (1) {
        if (read(STDIN_FILENO, sequence, 1) != 1) return 0;
        if (sequence[0] != '\033') continue;
        if (read(STDIN_FILENO, sequence, 1) != 1 || sequence[0] != '[') continue;
        if (read(STDIN_FILENO, sequence, 1) != 1 || sequence[0] != '<') continue;
        index = 0;
        while (index < 30) {
            if (read(STDIN_FILENO, &sequence[index], 1) != 1) break;
            if (sequence[index] == 'M' || sequence[index] == 'm') {
                sequence[index + 1] = '\0';
                break;
            }
            index = index + 1;
        }
        if (sequence[index] == 'M') {
            int button, c, r;
            if (sscanf(sequence, "%d;%d;%d", &button, &c, &r) == 3 &&
                button == 0) {
                *col = c;
                *row = r;
                goto_xy(*col, *row);
                return 1;
            }
        }
    }
}
#endif

// abilita l'input da tastiera
static inline void enable_keyboard(void)
{
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    if (GetConsoleMode(h, &mode)) {
        mode &= ~ENABLE_MOUSE_INPUT;
        mode |= ENABLE_QUICK_EDIT_MODE;
        SetConsoleMode(h, mode);
    }
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
static inline int is_area_clicked(ClickableArea area, int row, int col)
{
    return (row == area.row && col >= area.col1 && col <= area.col2);
}

#endif
