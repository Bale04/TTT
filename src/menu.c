/*
 ============================================================================
 Name        : menu.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 0.1 
 Copyright   : Your copyright notice
 Description : file di gestione del menu principale
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "strutture.h"
// libreria condivisa per mouse e cursore
#include "mouse.h"
#include "menu.h"
#include "supporto.h"

// funzioni esterne da impostazioni.c
extern void navigaImpostazioni(Impostazioni *impostazioni);
extern void resetImpostazioni(Impostazioni *impostazioni);
extern Stringa Get_nomePartita(Impostazioni impostazioni);

// funzioni esterne da gioco.c
extern void navigaPartita(Partita *partita, Impostazioni impostazioni);

// funzioni locali
void stampaSchermataMenu(Stringa s);
void navigaMenu(Impostazioni *impostazioni);


#pragma region main

int main() {
    // le impostazioni vengono create una sola volta e persistono per tutto il programma
    Impostazioni impostazioni;
    resetImpostazioni(&impostazioni);


    // avvia la navigazione del menu principale
    navigaMenu(&impostazioni);

    return EXIT_SUCCESS;
}

#pragma endregion


// ----------------- STAMPA SCHERMATA MENU ------------------
#pragma region stampa

void stampaSchermataMenu(Stringa s) {
    FILE *fp;
    int c;
    char nomeCompleto[256];

    sprintf(nomeCompleto, PERCORSO_MENU, s.data);
    fp = fopen(nomeCompleto, "r");
    if (fp == NULL) {
        printf("Errore caricamento schermata menu: %s\n", nomeCompleto);
    } else {
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);
        }
        fclose(fp);
    }
}

#pragma endregion


// --------------------- NAVIGAZIONE MENU PRINCIPALE -----------------------------
#pragma region navigazione

void navigaMenu(Impostazioni *impostazioni) {
    int esci = 0;

    // abilita il mouse tramite la libreria mouse.h
    abilitaMouse();

    while (!esci) {
        // pulisce il terminale
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // stampa la schermata del menu principale
        stampaSchermataMenu(schermateMenu[0]);

        // legge il click dell'utente
        int riga, colonna;
        if (!leggiClick(&riga, &colonna))
            continue;

        // gestione click sui bottoni del menu
        if (areaCliccata(bMainMenu[0], riga, colonna)) {
            // [GIOCA]
            abilitaTastiera();
            Partita partita;
            navigaPartita(&partita, *impostazioni);
            // quando il gioco termina si torna al menu
            abilitaMouse();
        } else if (areaCliccata(bMainMenu[1], riga, colonna)) {
            // [IMPOSTAZIONI] - apre le impostazioni
            abilitaTastiera();
            navigaImpostazioni(impostazioni);
            // quando si preme ESCI dalla schermata 0 delle impostazioni si torna qui
            abilitaMouse();
        } else if (areaCliccata(bMainMenu[2], riga, colonna)) {
            // [SUPPORTO] - apre il supporto
            abilitaTastiera();
            navigaSupporto();
            abilitaMouse();
        } else if (areaCliccata(bMainMenu[3], riga, colonna)) {
            // [STATISTICHE] - TODO
        } else if (areaCliccata(bMainMenu[4], riga, colonna)) {
            // [ESCI] - esce dal programma
            esci = 1;
        }
    }

    // ripristina il terminale
    abilitaTastiera();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("Arrivederci!\n");
}

#pragma endregion