#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "costanti.h"

// Definizione della stringa di caratteri
typedef struct {
  char data[STRING_LENGTH];
} String;

// struttura delle impostazioni della partita
typedef struct {
  String player1_name;    // nome del giocatore 1
  String player2_name;    // nome del giocatore 2
  int game_mode;           // 1 - CPU,   0 - Giocatore
  String previous_game; // nome della partita da riprendere
  char p1_symbol;    // simbolo giocatore 1
  char p2_symbol;    // simbolo del giocatore 2
  int undo_settings;   // 1 - Default,  0 - Modificate
  int num_rounds;           // numero dei round
  String game_name;       // nome della partita da giocare
} Settings;

// struttura delle zone cliccabili dello schermo
typedef struct {
  int row;  // riga del pulsante
  int col1; // colonna di inizio
  int col2; // colonna di fine
} ClickableArea;

// struttura delle statistiche per giocatore
typedef struct {
  char opponent_name[STRING_LENGTH]; // nome dell'avversario affrontato
  int wins;     // numero di vittorie di un giocatore
  int losses;    // numero di sconfitte di un giocatore
  int draws;      // numero di pareggi di un giocatore
} Stats;

// struttura della partita
typedef struct {
  char grid[GRID_SIZE][GRID_SIZE]; // griglia di gioco
  int turn;          // turno del giocatore che deve muovere (1 o 2)
  int round;          // round corrente
  Stats p1_stats;
  Stats p2_stats;
} Game;

// struttura per la posizione del cursore nel terminale
typedef struct {
  int col; // colonna
  int row; // riga
} Cursor;

#endif
