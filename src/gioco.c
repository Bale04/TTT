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
#include "gioco.h"
#include "supporto.h"

// funzioni esterne da impostazioni.c
extern Stringa Get_nomePartita(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
extern int    Get_numeroRound(Impostazioni impostazioni);
extern char   Get_simboloGiocatore1(Impostazioni impostazioni);
extern char   Get_simboloGiocatore2(Impostazioni impostazioni);

#pragma region dichiarazioni funzioni
void stampaSchermataGioco(Stringa s);
void stampaGioco(Partita partita, Impostazioni impostazioni);

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
    int turno = Get_turno(partita);
    int round = Get_round(partita);

    // stampa il nome della partita centrato nella barra del titolo (riga 6)
    goTo(GIOCO_TITOLO_COL, GIOCO_TITOLO_RIG);
    printf("%-5s", Get_nomePartita(impostazioni).data);

    // stampa il numero del round (riga 8, dopo "ROUND: ")
    goTo(GIOCO_ROUND_COL, GIOCO_ROUND_RIG);
    printf("%d", round);

    // stampa il turno (numero del giocatore: 1 o 2) (riga 8, dopo "TURNO: ")
    goTo(GIOCO_TURNO_COL, GIOCO_TURNO_RIG);
    printf("%d", turno);

    fflush(stdout);

    // stampa i simboli al centro di ogni cella della griglia
    int r = 0;
    while (r < 3) {
        int c = 0;
        while (c < 3) {
            char simbolo = Get_griglia(partita, r, c);
            goTo(GRIGLIA_CENTRO_COL[c], GRIGLIA_CENTRO_RIG[r]);
            printf("%c", (simbolo == ' ' || simbolo == '\0') ? ' ' : simbolo);
            c = c + 1;
        }
        r = r + 1;
    }
    fflush(stdout);
}

#pragma endregion


// --------------------- NAVIGAZIONE PARTITA -----------------------------
#pragma region navigazione

void navigaPartita(Partita *partita, Impostazioni impostazioni) {
    int esci = 0;

    // inizializza la partita
    Set_turno(partita, 1);
    Set_round(partita, 1);
    // inizializza la griglia vuota
    int ri = 0;
    while (ri < 3) {
        int ci = 0;
        while (ci < 3) {
            Set_griglia(partita, ri, ci, ' ');
            ci = ci + 1;
        }
        ri = ri + 1;
    }

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
        stampaSchermataGioco(schermatePartita[0]);

        // sovrascrive i dati dinamici (nome partita, round, turno, griglia)
        stampaGioco(*partita, impostazioni);

        // legge il click del giocatore
        int riga, colonna;
        if (!leggiClick(&riga, &colonna))
            continue;

        // --- rilevamento cella cliccata tramite la funzione di gioco.h ---
        int cella = cellaCliccata(riga, colonna);

        if (cella != -1) {
            int cellaR = cella / 3;
            int cellaC = cella % 3;

            // se la cella è ancora libera
            if (Get_griglia(*partita, cellaR, cellaC) == ' ' ||
                Get_griglia(*partita, cellaR, cellaC) == '\0') {
                // simbolo del giocatore corrente letto dalle impostazioni
                char simboloCorrente = (Get_turno(*partita) == 1)
                    ? Get_simboloGiocatore1(impostazioni)
                    : Get_simboloGiocatore2(impostazioni);

                // piazza il simbolo nella cella
                Set_griglia(partita, cellaR, cellaC, simboloCorrente);

                // alterna il turno
                Set_turno(partita, (Get_turno(*partita) == 1) ? 2 : 1);
            }
        } else if (areaCliccata(bGiocoMenu[1], riga, colonna)) {
            // [SUPPORTO] - apre il supporto dal gioco
            abilitaTastiera();
            navigaSupporto();
            abilitaMouse();
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