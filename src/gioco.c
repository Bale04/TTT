/*
 ============================================================================
 Name        : gioco.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 0.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gestione delle strutture per il gioco 
#include "gioco.h"
// gestione del mouse e del terminale
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


// ----------------- DICHIARAZIONI ---------------------
#pragma region dichiarazioni funzioni di accesso

// funzioni di accesso alla Partita
void Set_griglia(Partita* partita, int r, int c, char simbolo);
char Get_griglia(Partita partita, int r, int c);
void Set_impostazioni(Partita* partita, Impostazioni impostazioni);
Impostazioni Get_impostazioni(Partita partita);
void Set_turno(Partita* partita, int turnoCorrente);
int Get_turno(Partita partita);
void Set_round(Partita* partita, int roundCorrente);
int Get_round(Partita partita);

// funzioni di gioco
void stampaSchermataGioco(Stringa s);
void stampaGioco(Partita partita);
void navigaPartita(Partita *partita, Impostazioni impostazioni);

#pragma endregion

// ----------------- MAIN ---------------------------
#pragma region main

int main() {
    // 1. Raccolta delle impostazioni tramite la schermata di impostazioni
    Impostazioni impostazioni;
    resetImpostazioni(&impostazioni);

    Stringa schermate[1] = {{"Gioco"}};
    navigaImpostazioni(&impostazioni, schermate);

    // 2. Inizializzazione della partita con le impostazioni raccolte
    Partita partita;
    // griglia vuota
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            partita.griglia[r][c] = ' ';
    partita.turno = 1;
    partita.round = 1;
    Set_impostazioni(&partita, impostazioni);

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


void stampaGioco(Partita partita) {
    Impostazioni imp = Get_impostazioni(partita);
    int turno  = Get_turno(partita);
    int round  = Get_round(partita);
    char *nomeCorrente = (turno == 1)
        ? imp.nomeGiocatore1.data
        : imp.nomeGiocatore2.data;

    goTo(13, 9);
    printf("%2d", round);
    goTo(28, 9);
    printf("%-18s", nomeCorrente);
    fflush(stdout);

    int righeGriglia[3] = {13, 17, 21};
    int colonneGriglia[3] = {20, 40, 60};

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            char simbolo = Get_griglia(partita, r, c);
            goTo(colonneGriglia[c], righeGriglia[r]);
            printf("%c", (simbolo == ' ' || simbolo == '\0') ? ' ' : simbolo);
        }
    }
    fflush(stdout);
}

#pragma endregion

// ===================== NAVIGAZIONE PARTITA =====================
#pragma region navigazione

void navigaPartita(Partita *partita, Impostazioni impostazioni) {
    int esci = 0;

    // abilita mouse
#ifdef _WIN32
    HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modalitaPrecedente;
    GetConsoleMode(handleInput, &modalitaPrecedente);
    SetConsoleMode(handleInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
#else
    struct termios originale, grezza;
    tcgetattr(STDIN_FILENO, &originale);
    grezza = originale;
    grezza.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &grezza);
    printf("\033[?1000h\033[?1006h");
    fflush(stdout);
#endif

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
        stampaGioco(*partita);

        // legge il click del giocatore
        int riga, colonna;
        if (!leggiClick(&riga, &colonna))
            continue;

        // --- rilevamento cella cliccata ---
        // limiti delle colonne nelle celle della griglia (approssimativi)
        // cella 0: col 11-29, cella 1: col 31-49, cella 2: col 51-69
        int colonnaInizio[3] = {11, 31, 51};
        int colonnaFine[3]   = {29, 49, 69};
        // limiti delle righe nelle celle della griglia
        // cella 0: riga 11-14, cella 1: riga 15-18, cella 2: riga 19-22
        int rigaInizio[3] = {11, 15, 19};
        int rigaFine[3]   = {14, 18, 22};

        int cellaR = -1, cellaC = -1;
        for (int r = 0; r < 3; r++) {
            if (riga >= rigaInizio[r] && riga <= rigaFine[r]) {
                cellaR = r;
                break;
            }
        }
        for (int c = 0; c < 3; c++) {
            if (colonna >= colonnaInizio[c] && colonna <= colonnaFine[c]) {
                cellaC = c;
                break;
            }
        }

        // se è stata cliccata una cella valida e ancora libera
        if (cellaR != -1 && cellaC != -1) {
            char simboloCorrente = (partita->turno == 1)
                ? Get_simboloGiocatore1(impostazioni)
                : Get_simboloGiocatore2(impostazioni);

            if (partita->griglia[cellaR][cellaC] == ' ' ||
                partita->griglia[cellaR][cellaC] == '\0') {
                Set_griglia(partita, cellaR, cellaC, simboloCorrente);

                // alterna il turno
                partita->turno = (partita->turno == 1) ? 2 : 1;
            }
        }

        // TODO: aggiungere controllo vittoria/pareggio e avanzamento round
    }

    // ripristina terminale
#ifdef _WIN32
    SetConsoleMode(handleInput, modalitaPrecedente);
    system("cls");
#else
    printf("\033[?1000l\033[?1006l");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &originale);
    system("clear");
#endif
    printf("Partita terminata.\n");
}

#pragma endregion