/*
 ============================================================================
 Name        : mouse.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Description : Implementazione della gestione del mouse e del cursore del terminale.
 ============================================================================
 */

#include "mouse.h"

// gestisce lo spostamento del cursore al click
void goto_xy(int x, int y)
{
#ifdef _WIN32
    HANDLE h;
    COORD pos;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = (SHORT)(x - 1);
    pos.Y = (SHORT)(y - 1);
    SetConsoleCursorPosition(h, pos);
#else
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

// funzione di abilitazione del mouse
void enable_mouse(void)
{
#ifdef _WIN32
    HANDLE h;
    DWORD mode;

    h = GetStdHandle(STD_INPUT_HANDLE);
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
int read_click(int *row, int *col)
{
    HANDLE h;
    INPUT_RECORD ev;
    DWORD cnt;

    enable_mouse();
    h = GetStdHandle(STD_INPUT_HANDLE);
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
int read_click(int *row, int *col)
{
    char sequence[32];
    int index;
    int button;
    int c;
    int r;
    int sequenza_valida;
    int terminatore_trovato;

    while (1) {
        sequenza_valida = 0;
        if (read(STDIN_FILENO, sequence, 1) != 1) return 0;
        if (sequence[0] == '\033') {
            if (read(STDIN_FILENO, sequence, 1) == 1 && sequence[0] == '[') {
                if (read(STDIN_FILENO, sequence, 1) == 1 && sequence[0] == '<') {
                    sequenza_valida = 1;
                }
            }
        }

        if (sequenza_valida) {
            index = 0;
            terminatore_trovato = 0;
            while (index < 30 && !terminatore_trovato) {
                if (read(STDIN_FILENO, &sequence[index], 1) != 1) {
                    terminatore_trovato = 1;
                } else if (sequence[index] == 'M' || sequence[index] == 'm') {
                    sequence[index + 1] = '\0';
                    terminatore_trovato = 1;
                } else {
                    index = index + 1;
                }
            }

            if (sequence[index] == 'M') {
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
}
#endif

// abilita l'input da tastiera
void enable_keyboard(void)
{
#ifdef _WIN32
    HANDLE h;
    DWORD mode;

    h = GetStdHandle(STD_INPUT_HANDLE);
    if (GetConsoleMode(h, &mode)) {
        mode &= ~ENABLE_MOUSE_INPUT;
        mode |= ENABLE_QUICK_EDIT_MODE;
        SetConsoleMode(h, mode);
    }
#else
    struct termios t;

    printf("\033[?1000l\033[?1006l");
    fflush(stdout);
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

// controlla se il click corrisponde all'area cliccabile
int is_area_clicked(ClickableArea area, int row, int col)
{
    return (row == area.row && col >= area.col1 && col <= area.col2);
}
