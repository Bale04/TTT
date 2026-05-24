#ifndef salvataggio_H
#define salvataggio_H
#include "impostazioni.h"
#include "areeCliccabili.h"

// --------------- PERCORSO INTERFACCIA GIOCO ---------------
const char PERCORSO_GIOCO[70] ="/home/Bale/GitHub/TTT/Interfacce/Gioco/%s.txt";

typedef struct{
    char griglia[3][3]; // griglia di gioco
    Impostazioni impostazioni; // impostazioni da passare
    int turno; // turno del giocatore che deve muovere
    int round; // round corrente
} Partita;


// AREA DI GIOCO



// funzioni esterne definite in impostazioni.c
extern void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]);
extern void resetImpostazioni(Impostazioni *impostazioni);
extern int  leggiClick(int *riga, int *colonna);
extern void goTo(int x, int y);
extern char Get_simboloGiocatore1(Impostazioni impostazioni);
extern char Get_simboloGiocatore2(Impostazioni impostazioni);

#endif