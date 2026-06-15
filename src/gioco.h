#ifndef gioco_H
#define gioco_H

#include "strutture.h"

#include "mouse.h"


// i centri delle celle per posizionare i simboli
int GRIGLIA_CENTRO_COL[3] = {32, 40, 48};
int GRIGLIA_CENTRO_RIG[3] = {11, 15, 19};

// Posizioni dell'intefaccia su cui scrivere le informazioni
#define GIOCO_TITOLO_COL   38   // colonna del nome partita (riga 6)
#define GIOCO_TITOLO_RIG    6
#define GIOCO_ROUND_COL    13   // colonna del numero round  (riga 8)
#define GIOCO_ROUND_RIG     8
#define GIOCO_TURNO_COL    75   // colonna del turno/nome giocatore (riga 8)
#define GIOCO_TURNO_RIG     8
#define VITTORIA_G1_RIG    12
#define VITTORIA_G2_RIG    13
#define VITTORIA_COL       11   // colonna del numero di vittorie del giocatore
#define NOME_VINCITORE_COL 41
#define NOME_VINCITORE_RIG 14

// le celle sono defined a partire da sinistra a destra partendo dall'alto
/*  1-2-3
    4-5-6
    7-8-9
*/
AreaCliccabile cella1[] = {{10, 29, 36}, {11, 29, 36}, {12, 29, 36}};
AreaCliccabile cella2[] = {{10, 37, 44}, {11, 37, 44}, {12, 37, 44}};
AreaCliccabile cella3[] = {{10, 45, 52}, {11, 45, 52}, {12, 45, 52}};
AreaCliccabile cella4[] = {{14, 29, 36}, {15, 29, 36}, {16, 29, 36}};
AreaCliccabile cella6[] = {{14, 45, 52}, {15, 45, 52}, {16, 45, 52}};
AreaCliccabile cella5[] = {{14, 37, 44}, {15, 37, 44}, {16, 37, 44}};
AreaCliccabile cella7[] = {{18, 29, 36}, {19, 29, 36}, {20, 29, 36}};
AreaCliccabile cella8[] = {{18, 37, 44}, {19, 37, 44}, {20, 37, 44}};
AreaCliccabile cella9[] = {{18, 45, 52}, {19, 45, 52}, {20, 45, 52}};


// ESCI - SALVA - SUPPORTO
AreaCliccabile bGiocoMenu[] = { {22, 5, 10}, {22, 33, 47}, {22, 66, 75}};

// SI - NO - ESCI per la conferma salvataggio
AreaCliccabile bSalvaConferma[] = {{13, 29, 33}, {13, 49, 53}, {16, 38, 43}};

// TORNA AL MENU
AreaCliccabile bVittoria[] = {{20, 33, 47}};

// Puntatori alle celle per gestione click iterativa
AreaCliccabile *tutteLeCelle[9] = {
    cella1, cella2, cella3,
    cella4, cella5, cella6,
    cella7, cella8, cella9
};

// Controlla se un click (riga, colonna) cade in una delle 9 celle.
// Restituisce l'indice della cella (0-8) oppure -1 se nessuna cella è stata cliccata.
static inline int cellaCliccata(int riga, int colonna) {
    int i = 0;
    while (i < 9) {
        int j = 0;
        while (j < 3) {
            if (areaCliccata(tutteLeCelle[i][j], riga, colonna)) {
                return i;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    return -1;
}

// vettore delle schermate della partita
Stringa schermatePartita[4] = {{"Gioco"}, {"SalvaPartita"}, {"Supporto"}, {"Vittoria"}};
const char PERCORSO_GIOCO[70] = "/home/Bale/GitHub/TTT/Interfacce/Gioco/%s.txt";

#endif /* gioco_H */