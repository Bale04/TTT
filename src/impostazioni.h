#ifndef impostazioni_H
#define impostazioni_H

#include "areeCliccabili.h"

// Definizione della stringa di caratteri
typedef struct {
  char data[20];
} Stringa;

// struttura delle impostazioni della partita
typedef struct {
  Stringa nomeGiocatore1;    // nome del giocatore 1
  Stringa nomeGiocatore2;    // nome del giocatore 2
  int modoPartita;           // 1 - CPU,   0 - Giocatore
  Stringa partitaPrecedente; // nome della partita da riprendere
  char simboloGiocatore1;    // simbolo giocatore 1
  char simboloGiocatore2;    // simbolo del giocatore 2
  int annullaImpostazioni;   // 1 - Default,  0 - Modificate
  int numeroRound;           // numero dei round
  Stringa nomePartita;       // nome della partita da giocare
} Impostazioni;

// bottoni per ogni schermata
AreaCliccabile bMenu[] = {{9, 26, 51},  {11, 27, 49}, {13, 30, 45},
                          {15, 28, 47}, {17, 26, 49}, {19, 26, 50},
                          {20, 65, 70}};
AreaCliccabile bNomi[] = {{12, 31, 44}, {16, 31, 44}, {18, 38, 44}};
AreaCliccabile bModo[] = {{13, 19, 27}, {13, 49, 53}, {16, 38, 44}};
AreaCliccabile bCarica[] = {{12, 40, 42}, {14, 38, 44}};
AreaCliccabile bSimb[] = {{12, 39, 42}, {16, 39, 42}, {18, 38, 44}};
AreaCliccabile bAnnulla[] = {{13, 29, 33}, {13, 49, 52}};
AreaCliccabile bRound[] = {{12, 37, 46}, {16, 40, 43}, {18, 38, 44}};

// costante per il percorso delle interfacce delle impostazioni
const char PERCORSO_FILE[50] =
    "D:\\GitHub\\TTT\\Interfacce\\Impostazioni\\%s.txt";

#endif