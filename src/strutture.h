#ifndef strutture_H
#define strutture_H

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

// struttura delle zone cliccabili dello schermo
typedef struct {
  int r;  // riga del pulsante
  int c1; // colonna di inizio
  int c2; // colonna di fine
} AreaCliccabile;

typedef struct {
  Stringa nomeAvversario; // nome dell'avversario affrontato
  int numeroVittorie;     // numero di vittorie di un giocatore
  int numeroSconfitte;    // numero di sconfitte di un giocatore
  int numeroPareggi;      // numero di pareggi di un giocatore
} Statistiche;

// struttura della partita
typedef struct {
  char griglia[3][3]; // griglia di gioco
  int turno;          // turno del giocatore che deve muovere (1 o 2)
  int round;          // round corrente
  Statistiche statisticheG1;
  Statistiche statisticheG2;
} Partita;

#endif