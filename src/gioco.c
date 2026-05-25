/*
 ============================================================================
 Name        : gioco.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 0.2
 Copyright   : Your copyright notice
 Description : file di gestione del gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gestione delle strutture per il gioco (include anche mouse.h e impostazioni.h)
#include "gioco.h"


// ----------------- DICHIARAZIONI ---------------------
#pragma region dichiarazioni funzioni di accesso

// funzioni di gioco
void stampaSchermataGioco(Stringa s);
void stampaGioco(Partita partita, Impostazioni impostazioni);
void navigaPartita(Partita *partita, Impostazioni impostazioni);

#pragma endregion

// ----------------- MAIN ---------------------------
#pragma region main

int main() {
    // 1. Raccolta delle impostazioni tramite la schermata di impostazioni
    Impostazioni impostazioni;
    resetImpostazioni(&impostazioni);

    Stringa schermate[3] = {{"Gioco"}, {"SalvaPartita"}, {"Supporto"}};
    navigaImpostazioni(&impostazioni, schermate);

    // 2. Inizializzazione della partita con le impostazioni raccolte
    Partita partita;
    // griglia vuota
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            partita.griglia[r][c] = ' ';
    partita.turno = 1;
    partita.round = 1;

    // 3. Avvio schermata di gioco
    navigaPartita(&partita, impostazioni);

    return EXIT_SUCCESS;
}

#pragma endregion


// ----------------- STAMPA SCHERMATA ------------------
#pragma region stampa

// stampa il file .txt della schermata di gioco
void stampaSchermataGioco(Stringa s) {
    FILE *fp;
    int c;
    char nomeCompleto[256];

    sprintf(nomeCompleto, PERCORSO_GIOCO, s.data);
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


// sovrascrive i dati dinamici sulla schermata: nome partita, round, turno, griglia
void stampaGioco(Partita partita, Impostazioni impostazioni) {
    int turno = partita.turno;
    int round = partita.round;

    // stampa il nome della partita centrato nella barra del titolo (riga 6)
    goTo(GIOCO_TITOLO_COL, GIOCO_TITOLO_RIG);
    printf("%-5s", Get_nomePartita(impostazioni).data);

    // stampa il numero del round (riga 8, dopo "ROUND: ")
    goTo(GIOCO_ROUND_COL, GIOCO_ROUND_RIG);
    printf("%d", round);

    // stampa il turno (numero del giocatore) (riga 8, dopo "TURNO: ")
    goTo(GIOCO_TURNO_COL, GIOCO_TURNO_RIG);
    printf("%d", turno);

    fflush(stdout);

    // stampa i simboli al centro di ogni cella della griglia
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            char simbolo = partita.griglia[r][c];
            goTo(GRIGLIA_CENTRO_COL[c], GRIGLIA_CENTRO_RIG[r]);
            printf("%c", (simbolo == ' ' || simbolo == '\0') ? ' ' : simbolo);
        }
    }
    fflush(stdout);
}

#pragma endregion


// --------------------- NAVIGAZIONE PARTITA -----------------------------
#pragma region navigazione

void navigaPartita(Partita *partita, Impostazioni impostazioni) {
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

        // stampa la schermata base del gioco
        Stringa schermataGioco = {"Gioco"};
        stampaSchermataGioco(schermataGioco);

        // sovrascrive i dati dinamici (round, turno, griglia)
        stampaGioco(*partita, impostazioni);

        // legge il click del giocatore
        int riga, colonna;
        if (!leggiClick(&riga, &colonna))
            continue;

        // --- rilevamento cella cliccata ---
        // usa le costanti definite in gioco.h (GRIGLIA_COL_INI/FIN, GRIGLIA_RIG_INI/FIN)
        int cellaR = -1, cellaC = -1;
        for (int r = 0; r < 3; r++) {
            if (riga >= GRIGLIA_RIG_INI[r] && riga <= GRIGLIA_RIG_FIN[r]) {
                cellaR = r;
                break;
            }
        }
        for (int c = 0; c < 3; c++) {
            if (colonna >= GRIGLIA_COL_INI[c] && colonna <= GRIGLIA_COL_FIN[c]) {
                cellaC = c;
                break;
            }
        }

        // se è stata cliccata una cella valida e ancora libera
        if (cellaR != -1 && cellaC != -1) {
            // simbolo del giocatore corrente letto dalle impostazioni
            char simboloCorrente = (partita->turno == 1)
                ? impostazioni.simboloGiocatore1
                : impostazioni.simboloGiocatore2;

            if (partita->griglia[cellaR][cellaC] == ' ' ||
                partita->griglia[cellaR][cellaC] == '\0') {
                // piazza il simbolo nella cella
                partita->griglia[cellaR][cellaC] = simboloCorrente;

                // alterna il turno
                partita->turno = (partita->turno == 1) ? 2 : 1;
            }
        }

        // TODO: aggiungere controllo vittoria/pareggio e avanzamento round
    }

    // ripristina terminale
    abilitaTastiera();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("Partita terminata.\n");
}

#pragma endregion