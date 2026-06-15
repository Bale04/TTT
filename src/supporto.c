/*
 ============================================================================
 Name        : supporto.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Description : Gestione delle schermate di supporto (regolamento, manuale, suggerimenti)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supporto.h"
#include "mouse.h"

// Funzione interna per stampare un file di interfaccia (.txt)
void stampaSchermataSupporto(const char *nomeSchermata) {
    FILE *fp;
    int c;
    char nomeCompleto[256];

    sprintf(nomeCompleto, PERCORSO_SUPPORTO, nomeSchermata);
    fp = fopen(nomeCompleto, "r");
    if (fp == NULL) {
        printf("Errore caricamento schermata supporto: %s\n", nomeCompleto);
    } else {
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);
        }
        fclose(fp);
        printf("\n");
    }
}

// Funzione principale di navigazione del supporto
void navigaSupporto(void) {
    int riga, colonna;
    int esciSupporto = 0;
    // schermata: 0 = Supporto principale, 1 = Regolamento, 2 = Manuale, 3 = Suggerimenti
    int schermata = 0;
    int pagSuggerimento = 1;

    // abilita il mouse per la navigazione interattiva
    abilitaMouse();

    while (!esciSupporto) {
        // pulisce il terminale
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // stampa la schermata corretta
        if (schermata == 0) {
            stampaSchermataSupporto("Supporto");
        } else if (schermata == 1) {
            stampaSchermataSupporto("Regolamento");
        } else if (schermata == 2) {
            stampaSchermataSupporto("Manuale");
        } else if (schermata == 3) {
            char nomeSuggerimento[30];
            sprintf(nomeSuggerimento, "Suggerimenti%d", pagSuggerimento);
            stampaSchermataSupporto(nomeSuggerimento);
        }

        goTo(1, 25);
        fflush(stdout);

        // attende ed acquisisce il click del mouse
        if (!leggiClick(&riga, &colonna))
            continue;

        // gestione della navigazione in base alla schermata corrente
        if (schermata == 0) {
            // Menu Principale del Supporto
            if (areaCliccata(bSupRegole, riga, colonna)) {
                schermata = 1;
            } else if (areaCliccata(bSupManuale, riga, colonna)) {
                schermata = 2;
            } else if (areaCliccata(bSupSuggerimenti, riga, colonna)) {
                schermata = 3;
                pagSuggerimento = 1;
            } else if (areaCliccata(bSupEsci, riga, colonna)) {
                esciSupporto = 1;
            }
        } else if (schermata == 1) {
            // Regolamento
            if (areaCliccata(bSubEsci, riga, colonna)) {
                schermata = 0;
            }
        } else if (schermata == 2) {
            // Manuale
            if (areaCliccata(bSubEsci, riga, colonna)) {
                schermata = 0;
            }
        } else if (schermata == 3) {
            // Suggerimenti (pagine 1 a 5)
            if (areaCliccata(bSuggEsci, riga, colonna)) {
                schermata = 0;
            } else if (pagSuggerimento > 1 && areaCliccata(bSuggIndietro, riga, colonna)) {
                pagSuggerimento = pagSuggerimento - 1;
            } else if (pagSuggerimento == 1 && areaCliccata(bSuggAvantiP1, riga, colonna)) {
                pagSuggerimento = pagSuggerimento + 1;
            } else if (pagSuggerimento > 1 && pagSuggerimento < 5 && areaCliccata(bSuggAvanti, riga, colonna)) {
                pagSuggerimento = pagSuggerimento + 1;
            }
        }
    }

    // ripristina la modalità terminale
    abilitaTastiera();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
