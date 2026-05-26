/*
 ============================================================================
 Name        : impostazioni.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 1.1 Copyright   : Your copyright notice
 Description : file di gestione delle impostazioni di gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "impostazioni.h"
#include "strutture.h"
// libreria condivisa per mouse e cursore
#include "mouse.h"
#include "menu.h"

void stampaSchermata(Stringa s);


#pragma region main

int main() {
  // appena si avvia il codice si impostano le impostazioni di default.

  // vettore che carica i nomi delle schermate da visualizzare alla selezione
  Stringa schermate[1] = {{"MenuPrincipale"}};
  stampaSchermata(schermate[0]);
  // avvia la navigazione con il mouse nelle schermate impostazioni

  return EXIT_SUCCESS;
}
// #endif
#pragma endregion

void stampaSchermata(Stringa s) {
    FILE *fp;
    int c;
    char nomeCompleto[256];

    sprintf(nomeCompleto, PERCORSO_MENU, s.data);
    printf("%s", nomeCompleto);
    fp = fopen(nomeCompleto, "r");
    if (fp == NULL) {
        printf("Errore caricamento schermata gioco: %s\n", nomeCompleto);
    } else {
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);
        }
        fclose(fp);
    }
}