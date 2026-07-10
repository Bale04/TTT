#ifndef COSTANTI_H
#define COSTANTI_H

// costanti di dimensione necessarie a tempo di compilazione per definire array statici e strutture

#define GRID_SIZE 3
#define NUM_CELLS 9
#define STRING_LENGTH 20
#define PATH_LENGTH 256
#define HINT_NAME_LENGTH 30


// turni dei giocatori
static const int PLAYER1_TURN = 1;
static const int PLAYER2_TURN = 2;

// risultati finali della partita
static const int RESULT_DRAW = 0;
static const int RESULT_PLAYER1_WIN = 1;
static const int RESULT_PLAYER2_WIN = 2;

// cella non valida / mossa non trovata
static const int INVALID_CELL = -1;

// punteggi dell'algoritmo calcolaPunteggio (bot)
static const int SCORE_WIN = 10;
static const int SCORE_LOSS = -10;
static const int MIN_SCORE = -100;
static const int MAX_SCORE = 100;

// modalita' di gioco
static const int MODE_PLAYER = 0;
static const int MODE_CPU = 1;

// impostazioni default/modificate
static const int SETTINGS_DEFAULT = 1;
static const int SETTINGS_MODIFIED = 0;

// pagine del menu impostazioni
static const int SETTINGS_PAGE_MAIN = 0;
static const int SETTINGS_PAGE_NAMES = 1;
static const int SETTINGS_PAGE_MODE = 2;
static const int SETTINGS_PAGE_LOAD = 3;
static const int SETTINGS_PAGE_SYMBOLS = 4;
static const int SETTINGS_PAGE_UNDO = 5;
static const int SETTINGS_PAGE_ROUND = 6;

// pagine del menu principale
static const int MAIN_MENU_INDEX = 0;

// schermate delle statistiche
static const int STATS_SCREEN_MENU = 0;
static const int STATS_SCREEN_LIST = 1;

// coordinate di stampa statistiche
static const int SCREEN_CENTER_COL = 41;
static const int SEARCHED_NAME_ROW = 9;
static const int TABLE_COL_START = 7;
static const int TABLE_ROW_START = 12;

// esiti delle funzioni (successo / errore)
static const int STATUS_SUCCESS = 1;
static const int STATUS_ERROR = 0;

// pagine del supporto
static const int HELP_PAGE_MAIN = 0;
static const int HELP_PAGE_RULES = 1;
static const int HELP_PAGE_MANUAL = 2;
static const int HELP_PAGE_TIPS = 3;

// range di pagine dei suggerimenti
static const int TIP_PAGE_FIRST = 1;
static const int TIP_PAGE_LAST = 5;

#endif
