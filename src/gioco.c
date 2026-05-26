/*
 ============================================================================
 Name        : gioco.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 0.3
 Copyright   : Your copyright notice
 Description : file di gestione del gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gestione delle strutture per il gioco (include anche mouse.h e areeCliccabili.h)
#include "gioco.h"
#include "impostazioni.h"


// ----------------- DICHIARAZIONI ---------------------
#pragma region dichiarazioni funzioni

// funzioni di stampa
void stampaSchermata(Stringa s);
// void stampaGioco(Partita partita, Impostazioni impostazioni);

// funzione di navigazione
void navigaPartita(Partita *partita, Impostazioni impostazioni);

// funzioni di accesso Partita
void Set_griglia(Partita *partita, int riga, int colonna, char simbolo);
char Get_griglia(Partita partita, int riga, int colonna);
void Set_turno(Partita *partita, int turno);
int  Get_turno(Partita partita);
void Set_round(Partita *partita, int round);
int  Get_round(Partita partita);

#pragma endregion

// ----------------- MAIN ---------------------------
#pragma region main

int main() {
    // 1. Raccolta delle impostazioni tramite la schermata di impostazioni
    //    Le impostazioni NON vengono resettate qui: il reset avviene
    //    internamente in navigaImpostazioni tramite impostazioni.c
    Impostazioni impostazioni;
    // resetImpostazioni(&impostazioni);

    // le 7 schermate delle impostazioni (definite come in impostazioni.c)
    Stringa schermatePartita[3] = {{"Gioco"}, {"SalvaPartita"}, {"Supporto"}};
    stampaSchermata(schermatePartita[0]);

    // 2. Inizializzazione della partita con le impostazioni raccolte
    Partita partita;
    // griglia vuota
    // for (int r = 0; r < 3; r++)
    //     for (int c = 0; c < 3; c++)
    //         Set_griglia(&partita, r, c, ' ');
    // Set_turno(&partita, 1);
    // Set_round(&partita, 1);

    // 3. Avvio schermata di gioco
    navigaPartita(&partita, impostazioni);

    return EXIT_SUCCESS;
}

#pragma endregion


// ------------------------------ FUNZIONI DI ACCESSO PARTITA ------------------------------------
#pragma region funzioni di accesso

// ---------------------GRIGLIA---------------------------
void Set_griglia(Partita *partita, int riga, int colonna, char simbolo) {
    partita->griglia[riga][colonna] = simbolo;
}
char Get_griglia(Partita partita, int riga, int colonna) {
    return partita.griglia[riga][colonna];
}
// ---------------------TURNO---------------------------
void Set_turno(Partita *partita, int turno) {
    partita->turno = turno;
}
int Get_turno(Partita partita) {
    return partita.turno;
}
// ---------------------ROUND---------------------------
void Set_round(Partita *partita, int round) {
    partita->round = round;
}
int Get_round(Partita partita) {
    return partita.round;
}

#pragma endregion


// ----------------- STAMPA SCHERMATA ------------------
#pragma region stampa

// stampa il file .txt della schermata di gioco
void stampaSchermata(Stringa s) {
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
// void stampaGioco(Partita partita, Impostazioni impostazioni) {
//     int turno = Get_turno(partita);
//     int round = Get_round(partita);

//     // stampa il nome della partita centrato nella barra del titolo (riga 6)
//     goTo(GIOCO_TITOLO_COL, GIOCO_TITOLO_RIG);
//     printf("%-5s", Get_nomePartita(impostazioni).data);

//     // stampa il numero del round (riga 8, dopo "ROUND: ")
//     goTo(GIOCO_ROUND_COL, GIOCO_ROUND_RIG);
//     printf("%d", round);

//     // stampa il turno (numero del giocatore: 1 o 2) (riga 8, dopo "TURNO: ")
//     goTo(GIOCO_TURNO_COL, GIOCO_TURNO_RIG);
//     printf("%d", turno);

//     fflush(stdout);

//     // stampa i simboli al centro di ogni cella della griglia
//     for (int r = 0; r < 3; r++) {
//         for (int c = 0; c < 3; c++) {
//             char simbolo = Get_griglia(partita, r, c);
//             goTo(GRIGLIA_CENTRO_COL[c], GRIGLIA_CENTRO_RIG[r]);
//             printf("%c", (simbolo == ' ' || simbolo == '\0') ? ' ' : simbolo);
//         }
//     }
//     fflush(stdout);
// }

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
        stampaSchermata(schermataGioco);

        // sovrascrive i dati dinamici (round, turno, griglia)
        // stampaGioco(*partita, impostazioni);

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
            // char simboloCorrente = (Get_turno(*partita) == 1)
            //     ? Get_simboloGiocatore1(impostazioni)
            //     : Get_simboloGiocatore2(impostazioni);

            if (Get_griglia(*partita, cellaR, cellaC) == ' ' ||
                Get_griglia(*partita, cellaR, cellaC) == '\0') {
                // piazza il simbolo nella cella
                // Set_griglia(partita, cellaR, cellaC, simboloCorrente);

                // alterna il turno
                Set_turno(partita, (Get_turno(*partita) == 1) ? 2 : 1);
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