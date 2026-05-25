#ifndef gioco_H
#define gioco_H

#include "mouse.h"

// Definizione delle strutture per evitare inclusioni multiple di variabili globali
// da impostazioni.h
typedef struct {
  char data[20];
} Stringa;

typedef struct {
  Stringa nomeGiocatore1;
  Stringa nomeGiocatore2;
  int modoPartita;
  Stringa partitaPrecedente;
  char simboloGiocatore1;
  char simboloGiocatore2;
  int annullaImpostazioni;
  int numeroRound;
  Stringa nomePartita;
} Impostazioni;

// --------------- PERCORSO INTERFACCIA GIOCO ---------------
const char PERCORSO_GIOCO[70] = "/home/Bale/GitHub/TTT/Interfacce/Gioco/%s.txt";

typedef struct {
    char griglia[3][3]; // griglia di gioco
    int turno;          // turno del giocatore che deve muovere (1 o 2)
    int round;          // round corrente
} Partita;

// ----------------------------------------------------------------
// AREE CLICCABILI DELLA GRIGLIA DI GIOCO
// Coordinate ricavate dall'interfaccia Gioco.txt:
//   - linee verticali alle colonne 36 e 44
//   - linee orizzontali alle righe 13 e 17
//
//   celle colonne:  [5-35]  [37-43]  [45-76]
//   celle righe:    [10-12] [14-16]  [18-20]
// ----------------------------------------------------------------

// Ogni cella è un'AreaCliccabile definita con riga, col_inizio, col_fine.
// Per copertura bidimensionale usiamo la convenzione:
//   bGriglia[riga][colonna] con r = riga centrale della cella.
//   La verifica della riga viene fatta separatamente con i vettori sotto.

// Limiti colonne delle celle (1-indexed)
static const int GRIGLIA_COL_INI[3] = {5,  37, 45};
static const int GRIGLIA_COL_FIN[3] = {35, 43, 76};

// Limiti righe delle celle (1-indexed)
static const int GRIGLIA_RIG_INI[3] = {10, 14, 18};
static const int GRIGLIA_RIG_FIN[3] = {12, 16, 20};

// Centri delle celle per la stampa dei simboli (col, riga)
static const int GRIGLIA_CENTRO_COL[3] = {20, 40, 60};
static const int GRIGLIA_CENTRO_RIG[3] = {11, 15, 19};

// Posizioni degli indicatori di stato nell'interfaccia
#define GIOCO_TITOLO_COL  38   // colonna del nome partita (riga 6)
#define GIOCO_TITOLO_RIG   6
#define GIOCO_ROUND_COL   13   // colonna del numero round  (riga 8)
#define GIOCO_ROUND_RIG    8
#define GIOCO_TURNO_COL   75   // colonna del turno/nome giocatore (riga 8)
#define GIOCO_TURNO_RIG    8

// ----------------------------------------------------------------
// Funzioni esterne definite in impostazioni.c
// (le funzioni goTo, leggiClick, abilitaMouse, abilitaTastiera,
//  areaCliccata sono ora fornite da mouse.h)
// ----------------------------------------------------------------
extern void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]);
extern void resetImpostazioni(Impostazioni *impostazioni);
extern Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
extern Stringa Get_nomePartita(Impostazioni impostazioni);
extern int    Get_numeroRound(Impostazioni impostazioni);

#endif /* gioco_H */