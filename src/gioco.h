#ifndef gioco_H
#define gioco_H

#include "strutture.h"

#include "mouse.h"
#include "impostazioni.h"

// --------------- PERCORSO INTERFACCIA GIOCO ---------------
const char PERCORSO_GIOCO[70] = "/home/Bale/GitHub/TTT/Interfacce/Gioco/%s.txt";



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
// AREE CLICCABILI DEI BOTTONI DELLA SCHERMATA DI GIOCO
// [SALVA PARTITA]  riga 22, colonne 5-19
// [SUPPORTO]       riga 22, colonne 66-75
// ----------------------------------------------------------------
AreaCliccabile bGiocoMenu[] = {
    {22, 5, 19},   // [SALVA PARTITA]
    {22, 66, 75}   // [SUPPORTO]
};

// ----------------------------------------------------------------
// Funzioni esterne definite in impostazioni.c
// (le funzioni goTo, leggiClick, abilitaMouse, abilitaTastiera,
//  areaCliccata sono ora fornite da mouse.h)
// ----------------------------------------------------------------
// extern void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]);
// extern void resetImpostazioni(Impostazioni *impostazioni);
// extern Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
// extern Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
// extern Stringa Get_nomePartita(Impostazioni impostazioni);
// extern int    Get_numeroRound(Impostazioni impostazioni);
// extern char   Get_simboloGiocatore1(Impostazioni impostazioni);
// extern char   Get_simboloGiocatore2(Impostazioni impostazioni);

#endif /* gioco_H */