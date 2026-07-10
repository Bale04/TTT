#ifndef GAME_H
#define GAME_H

#include "costanti.h"
#include "strutture.h"

// i centri delle celle per posizionare i simboli
int GRID_CENTER_COL[GRID_SIZE] = {32, 40, 48};
int GRID_CENTER_ROW[GRID_SIZE] = {11, 15, 19};

// Posizioni dell'intefaccia su cui scrivere le informazioni
const int GAME_TITLE_COL   = 38;   
const int GAME_TITLE_ROW    = 6;
const int GAME_ROUND_COL    = 13;   
const int GAME_ROUND_ROW     = 8;
const int GAME_TURN_COL    = 75;   
const int GAME_TURN_ROW     = 8;
const int P1_WIN_ROW    = 12;
const int P2_WIN_ROW    = 13;
const int WIN_COL       = 11;   
const int WINNER_NAME_COL = 41;
const int WINNER_NAME_ROW = 14;

// le celle sono definite a partire da sinistra a destra partendo dall'alto
/*  1-2-3
    4-5-6
    7-8-9
*/
ClickableArea cell1[] = {{10, 29, 36}, {11, 29, 36}, {12, 29, 36}};
ClickableArea cell2[] = {{10, 37, 44}, {11, 37, 44}, {12, 37, 44}};
ClickableArea cell3[] = {{10, 45, 52}, {11, 45, 52}, {12, 45, 52}};
ClickableArea cell4[] = {{14, 29, 36}, {15, 29, 36}, {16, 29, 36}};
ClickableArea cell6[] = {{14, 45, 52}, {15, 45, 52}, {16, 45, 52}};
ClickableArea cell5[] = {{14, 37, 44}, {15, 37, 44}, {16, 37, 44}};
ClickableArea cell7[] = {{18, 29, 36}, {19, 29, 36}, {20, 29, 36}};
ClickableArea cell8[] = {{18, 37, 44}, {19, 37, 44}, {20, 37, 44}};
ClickableArea cell9[] = {{18, 45, 52}, {19, 45, 52}, {20, 45, 52}};


// ESCI - SALVA - SUPPORTO
ClickableArea btn_game_menu[] = { {22, 5, 10}, {22, 33, 47}, {22, 66, 75}};

// SI - NO - ESCI per la conferma salvataggio
ClickableArea btn_save_confirm[] = {{13, 29, 33}, {13, 49, 53}, {16, 38, 43}};

// TORNA AL MENU
ClickableArea btn_victory[] = {{20, 33, 47}};

// Puntatori alle celle per gestione click iterativa
ClickableArea *all_cells[NUM_CELLS] = {
    cell1, cell2, cell3,
    cell4, cell5, cell6,
    cell7, cell8, cell9
};

// Controlla se un click (row, col) cade in una delle 9 celle.
// Restituisce l'indice della cella (0-8) oppure INVALID_CELL se nessuna cella e' stata cliccata.
static inline int get_clicked_cell(int row, int col)
{
    int i = 0;
    while (i < NUM_CELLS) {
        int j = 0;
        while (j < 3) {
            if (is_area_clicked(all_cells[i][j], row, col)) {
                return i;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    return INVALID_CELL;
}

// vettore delle schermate della partita
String game_screens[] = {{"Gioco"}, {"SalvaPartita"}, {"Supporto"}, {"Vittoria"}};
const char GAME_PATH[] = "C:/Users/utente/Desktop/TTT/Interfacce/Gioco";

#endif
