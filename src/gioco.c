/*
 ============================================================================
 Name        : gioco.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : file di gestione del gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gioco.h"

#pragma region funzioni esterne
// funzioni esterne da supporto.c
extern void navigaSupporto(void);

// funzioni esterne da salvataggio.c
extern int salvaPartita(const Impostazioni *impostazioni, const Partita *partita);
extern int caricaPartita(Impostazioni *impostazioni, Partita *partita);

// funzione esterna da statistiche.c
extern void salvaStatistichePartita(const char *nomeG1, const char *nomeG2, int risultato);

// funzioni esterne da impostazioni.c
extern Stringa Get_nomePartita(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
extern int Get_numeroRound(Impostazioni impostazioni);
extern char Get_simboloGiocatore1(Impostazioni impostazioni);
extern char Get_simboloGiocatore2(Impostazioni impostazioni);
extern int Get_modoPartita(Impostazioni impostazioni);
#pragma endregion

#pragma region dichiarazioni funzioni
// funzioni di accesso Partita
void Set_griglia(Partita *partita, int riga, int colonna, char simbolo);
char Get_griglia(Partita partita, int riga, int colonna);
void Set_turno(Partita *partita, int turno);
int Get_turno(Partita partita);
void Set_round(Partita *partita, int round);
int Get_round(Partita partita);
// funzioni di accesso Partita - statisticheG1
int Get_vittorieG1(Partita partita);
void Set_vittorieG1(Partita *partita, int v);
int Get_sconfitteG1(Partita partita);
void Set_sconfitteG1(Partita *partita, int v);
int Get_pareggiG1(Partita partita);
void Set_pareggiG1(Partita *partita, int v);
// funzioni di accesso Partita - statisticheG2
int Get_vittorieG2(Partita partita);
void Set_vittorieG2(Partita *partita, int v);
int Get_sconfitteG2(Partita partita);
void Set_sconfitteG2(Partita *partita, int v);
int Get_pareggiG2(Partita partita);
void Set_pareggiG2(Partita *partita, int v);

// funzioni di stampa
void stampaSchermataGioco(Stringa s);
void stampaGioco(Partita partita, Impostazioni impostazioni);

// funzione di navigazione
void navigaPartita(Partita *partita, Impostazioni *impostazioni);

// funzioni di verifica stato round
char controllaVincitoreRound(Partita partita);
int grigliaPiena(Partita partita);

// funzioni bot CPU
char controllaVincitoreGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]);
int controlloGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]);
int calcolaPunteggio(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA], char simboloBot, char simboloAvversario, int isMaximizing);
int mossaBot(Partita partita, char simboloBot, char simboloAvversario);

#pragma endregion

// ------------------------- FUNZIONI DI ACCESSO PARTITA -------------------------------
#pragma region funzioni di accesso

// ---------------------GRIGLIA---------------------------
void Set_griglia(Partita *partita, int riga, int colonna, char simbolo){
    partita->griglia[riga][colonna] = simbolo;
}
char Get_griglia(Partita partita, int riga, int colonna){
    return partita.griglia[riga][colonna];
}
// ---------------------TURNO---------------------------
void Set_turno(Partita *partita, int turno){
    partita->turno = turno;
}
int Get_turno(Partita partita){
    return partita.turno;
}
// ---------------------ROUND---------------------------
void Set_round(Partita *partita, int round){
    partita->round = round;
}
int Get_round(Partita partita){
    return partita.round;
}
// ---------------------STATISTICHE G1---------------------------
void Set_vittorieG1(Partita *partita, int v){
    partita->statisticheG1.numeroVittorie = v;
}
int Get_vittorieG1(Partita partita){
    return partita.statisticheG1.numeroVittorie;
}
void Set_sconfitteG1(Partita *partita, int v){
    partita->statisticheG1.numeroSconfitte = v;
}
int Get_sconfitteG1(Partita partita){
    return partita.statisticheG1.numeroSconfitte;
}
void Set_pareggiG1(Partita *partita, int v){
    partita->statisticheG1.numeroPareggi = v;
}
int Get_pareggiG1(Partita partita){
    return partita.statisticheG1.numeroPareggi;
}
// ---------------------STATISTICHE G2---------------------------
void Set_vittorieG2(Partita *partita, int v){
    partita->statisticheG2.numeroVittorie = v;
}
int Get_vittorieG2(Partita partita){
    return partita.statisticheG2.numeroVittorie;
}
void Set_sconfitteG2(Partita *partita, int v){
    partita->statisticheG2.numeroSconfitte = v;
}
int Get_sconfitteG2(Partita partita){
    return partita.statisticheG2.numeroSconfitte;
}
void Set_pareggiG2(Partita *partita, int v){
    partita->statisticheG2.numeroPareggi = v;
}
int Get_pareggiG2(Partita partita){
    return partita.statisticheG2.numeroPareggi;
}

#pragma endregion

// ----------------------------- BOT CPU --------------------------------
#pragma region bot

// controlla il vincitore sulla copia della griglia usata dal bot
char controllaVincitoreGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]){
    char vincitore = '\0';
    int r;
    int c;

    // Controlla righe
    r = 0;
    while (r < DIMENSIONE_GRIGLIA && vincitore == '\0'){
        if (g[r][0] != ' ' && g[r][0] != '\0' && g[r][0] == g[r][1] && g[r][1] == g[r][2]){
            vincitore = g[r][0];
        }
        r = r + 1;
    }

    // Controlla colonne
    c = 0;
    while (c < DIMENSIONE_GRIGLIA && vincitore == '\0'){
        if (g[0][c] != ' ' && g[0][c] != '\0' && g[0][c] == g[1][c] && g[1][c] == g[2][c]){
            vincitore = g[0][c];
        }
        c = c + 1;
    }

    // Controlla diagonale principale e secondaria
    if (vincitore == '\0'){
        if (g[0][0] != ' ' && g[0][0] != '\0' && g[0][0] == g[1][1] && g[1][1] == g[2][2]){
            vincitore = g[0][0];
        }else if (g[0][2] != ' ' && g[0][2] != '\0' && g[0][2] == g[1][1] && g[1][1] == g[2][0]){
            vincitore = g[0][2];
        }
    }

    return vincitore;
}

// controlla se la griglia è piena
int controlloGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]){
    int piena;
    int r;
    int c;

    piena = 1;
    r = 0;
    c = 0;

    // Scansiona le 9 celle
    while (r < DIMENSIONE_GRIGLIA && piena == 1){
        c = 0;
        while (c < DIMENSIONE_GRIGLIA && piena == 1){
            if (g[r][c] == ' ' || g[r][c] == '\0'){
                piena = 0;
            }
            c = c + 1;
        }
        r = r + 1;
    }

    return piena;
}

// algoritmo ricorsivo per il calcolo del punteggio della posizione
// isMaximizing == 1: turno del bot (massimizza)
// isMaximizing == 0: turno del giocatore (minimizza)
int calcolaPunteggio(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA], char simboloBot, char simboloAvversario, int isMaximizing){
    int punteggio;
    int r;
    int c;
    int p;
    int migliore;
    char vincitore;

    punteggio = 0;
    vincitore = controllaVincitoreGriglia(g);

    if (vincitore == simboloBot){
        punteggio = PUNTEGGIO_VITTORIA;
    }else if (vincitore == simboloAvversario){
        punteggio = PUNTEGGIO_SCONFITTA;
    }else if (controlloGriglia(g)){
        punteggio = RISULTATO_PAREGGIO;
    }else{
        if (isMaximizing){
            migliore = PUNTEGGIO_MINIMO;
            r = 0;
            c = 0;
            while (r < DIMENSIONE_GRIGLIA){
                c = 0;
                while (c < DIMENSIONE_GRIGLIA){
                    if (g[r][c] == ' ' || g[r][c] == '\0'){
                        g[r][c] = simboloBot;
                        p = calcolaPunteggio(g, simboloBot, simboloAvversario, 0);
                        g[r][c] = ' ';
                        if (p > migliore){
                            migliore = p;
                        }
                    }
                    c = c + 1;
                }
                r = r + 1;
            }
            punteggio = migliore;
        }else{
            migliore = PUNTEGGIO_MASSIMO;
            r = 0;
            c = 0;
            while (r < DIMENSIONE_GRIGLIA){
                c = 0;
                while (c < DIMENSIONE_GRIGLIA){
                    if (g[r][c] == ' ' || g[r][c] == '\0'){
                        g[r][c] = simboloAvversario;
                        p = calcolaPunteggio(g, simboloBot, simboloAvversario, 1);
                        g[r][c] = ' ';
                        if (p < migliore){
                            migliore = p;
                        }
                    }
                    c = c + 1;
                }
                r = r + 1;
            }
            punteggio = migliore;
        }
    }

    return punteggio;
}

// restituisce la cella migliore (0-8) per il bot, o -1 se nessuna mossa disponibile
int mossaBot(Partita partita, char simboloBot, char simboloAvversario){
    char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA];
    int migliore = PUNTEGGIO_MINIMO;
    int r;
    int c;
    int p;
    int cellaMossa = CELLA_NON_VALIDA;

    // Copia lo stato della griglia
    r = 0;
    while (r < DIMENSIONE_GRIGLIA){
        c = 0;
        while (c < DIMENSIONE_GRIGLIA){
            g[r][c] = Get_griglia(partita, r, c);
            c = c + 1;
        }
        r = r + 1;
    }

    // Ricerca la mossa migliore
    r = 0;
    while (r < DIMENSIONE_GRIGLIA){
        c = 0;
        while (c < DIMENSIONE_GRIGLIA){
            if (g[r][c] == ' ' || g[r][c] == '\0'){
                g[r][c] = simboloBot;
                p = calcolaPunteggio(g, simboloBot, simboloAvversario, 0);
                g[r][c] = ' ';
                if (p > migliore){
                    migliore = p;
                    cellaMossa = r * DIMENSIONE_GRIGLIA + c;
                }
            }
            c = c + 1;
        }
        r = r + 1;
    }

    return cellaMossa;
}

#pragma endregion

// ----------------- STAMPA SCHERMATA ------------------
#pragma region stampa

void stampaSchermataGioco(Stringa s){
    FILE *fp;
    int c;
    char nomeCompleto[256];

    sprintf(nomeCompleto, PERCORSO_GIOCO, s.data);
    fp = fopen(nomeCompleto, "r");
    if (fp == NULL){
        printf("Errore caricamento schermata gioco: %s\n", nomeCompleto);
    }else{
        while ((c = fgetc(fp)) != EOF){
            putchar(c);
        }
        fclose(fp);
    }
}

// mostra a schermo i dati della partita in corso
void stampaGioco(Partita partita, Impostazioni impostazioni){
    int turno;
    int round;
    int r;
    int c;
    char simbolo;

    turno = Get_turno(partita);
    round = Get_round(partita);

    // stampa il nome della partita
    goTo(GIOCO_TITOLO_COL, GIOCO_TITOLO_RIG);
    printf("%s", Get_nomePartita(impostazioni).data);

    // stampa il numero del round
    goTo(GIOCO_ROUND_COL, GIOCO_ROUND_RIG);
    printf("%d", round);

    // stampa il turno del giocatore
    goTo(GIOCO_TURNO_COL, GIOCO_TURNO_RIG);
    printf("%d", turno);

    // stampa il numero di vittorie correnti per giocatori in base ai round giocati
    goTo(VITTORIA_COL, VITTORIA_G1_RIG);
    printf("%d", Get_vittorieG1(partita));
    goTo(VITTORIA_COL, VITTORIA_G2_RIG);
    printf("%d", Get_vittorieG2(partita));

    fflush(stdout);

    // stampa i simboli al centro di ogni cella della griglia
    r = 0;
    while (r < 3){
        c = 0;
        while (c < 3){
            simbolo = Get_griglia(partita, r, c);
            goTo(GRIGLIA_CENTRO_COL[c], GRIGLIA_CENTRO_RIG[r]);
            if (simbolo == ' ' || simbolo == '\0'){
                printf(" ");
            }else{
                printf("%c", simbolo);
            }
            c = c + 1;
        }
        r = r + 1;
    }
    fflush(stdout);
}

#pragma endregion

// --------------------- NAVIGAZIONE PARTITA -----------------------------
#pragma region navigazione

void navigaPartita(Partita *partita, Impostazioni *impostazioni){
    int esci;
    int r;
    int c;
    int riga;
    int colonna;
    int cella;
    int risultato;
    int confermato;
    int piena;
    char vincitore;
    char simboloCorrente;
    Stringa nomeG;

    esci = 0;

    // Se c'è una partita precedente specificata la carica
    if (strlen(impostazioni->partitaPrecedente.data) > 0){
        if (caricaPartita(impostazioni, partita)){
            // dopo aver caricato la partita pulisce il campo partitaPrecedente in modo che non venga caricata di nuovo ad ogni ciclo di while
            impostazioni->partitaPrecedente.data[0] = '\0';
        }else{
            // Se fallisce il caricamento inizializza normalmente
            Set_turno(partita, 1);
            Set_round(partita, 1);
            Set_vittorieG1(partita, 0);
            Set_sconfitteG1(partita, 0);
            Set_pareggiG1(partita, 0);
            Set_vittorieG2(partita, 0);
            Set_sconfitteG2(partita, 0);
            Set_pareggiG2(partita, 0);
            r = 0;
            while (r < DIMENSIONE_GRIGLIA){
                c = 0;
                while (c < DIMENSIONE_GRIGLIA){
                    Set_griglia(partita, r, c, ' ');
                    c = c + 1;
                }
                r = r + 1;
            }
        }
    }else{
        // Inizializza una nuova partita
        Set_turno(partita, 1);
        Set_round(partita, 1);
        Set_vittorieG1(partita, 0);
        Set_sconfitteG1(partita, 0);
        Set_pareggiG1(partita, 0);
        Set_vittorieG2(partita, 0);
        Set_sconfitteG2(partita, 0);
        Set_pareggiG2(partita, 0);
        // inizializza la griglia vuota
        r = 0;
        while (r < DIMENSIONE_GRIGLIA){
            c = 0;
            while (c < DIMENSIONE_GRIGLIA){
                Set_griglia(partita, r, c, ' ');
                c = c + 1;
            }
            r = r + 1;
        }
    }

    // abilita il mouse tramite la libreria mouse.h
    abilitaMouse();

    while (!esci){
        // pulisce il terminale
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // stampa la schermata base del gioco
        stampaSchermataGioco(schermatePartita[0]);

        // stampa a schermo i dati della partita
        stampaGioco(*partita, *impostazioni);
        goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
        fflush(stdout);

        // se modalità CPU e turno del bot (giocatore 2), muove automaticamente
        if (Get_modoPartita(*impostazioni) == MODO_CPU && Get_turno(*partita) == TURNO_GIOCATORE2){
            simboloCorrente = Get_simboloGiocatore2(*impostazioni);
            cella = mossaBot(*partita, simboloCorrente, Get_simboloGiocatore1(*impostazioni));
            if (cella != CELLA_NON_VALIDA){
                r = 0;
                c = 0;
                while (r * DIMENSIONE_GRIGLIA + c != cella){
                    c = c + 1;
                    if (c == DIMENSIONE_GRIGLIA){
                        c = 0;
                        r = r + 1;
                    }
                }
                Set_griglia(partita, r, c, simboloCorrente);
                // controllo fine round
                vincitore = controllaVincitoreRound(*partita);
                piena = grigliaPiena(*partita);
                if (vincitore != '\0' || piena){
                    if (vincitore != '\0'){
                        if (vincitore == Get_simboloGiocatore1(*impostazioni)){
                            Set_vittorieG1(partita, Get_vittorieG1(*partita) + 1);
                            Set_sconfitteG2(partita, Get_sconfitteG2(*partita) + 1);
                        }else{
                            Set_vittorieG2(partita, Get_vittorieG2(*partita) + 1);
                            Set_sconfitteG1(partita, Get_sconfitteG1(*partita) + 1);
                        }
                    }else{
                        Set_pareggiG1(partita, Get_pareggiG1(*partita) + 1);
                        Set_pareggiG2(partita, Get_pareggiG2(*partita) + 1);
                    }
                    // aggiorna schermo con lo stato finale del round
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    stampaSchermataGioco(schermatePartita[0]);
                    stampaGioco(*partita, *impostazioni);
                    goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
                    fflush(stdout);

                    if (Get_round(*partita) >= Get_numeroRound(*impostazioni)){
                        // fine partita
                        risultato = 0;
                        if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)){
                            risultato = RISULTATO_VITTORIA_G1;
                        }else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)){
                            risultato = RISULTATO_VITTORIA_G2;
                        }else{
                            risultato = RISULTATO_PAREGGIO;
                        }
                        salvaStatistichePartita(Get_nomeGiocatore1(*impostazioni).data, Get_nomeGiocatore2(*impostazioni).data, risultato);

                        confermato = 0;
                        while (!confermato){
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            stampaSchermataGioco(schermatePartita[3]);
                            if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)){
                                // nome vincitore è giocatore 1
                                nomeG = Get_nomeGiocatore1(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    ");
                                cella = NOME_VINCITORE_COL - (int)strlen(nomeG.data) / 2;
                                goTo(cella, NOME_VINCITORE_RIG);
                                printf("%s", nomeG.data);
                            }else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)){
                                nomeG = Get_nomeGiocatore2(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    ");
                                cella = NOME_VINCITORE_COL - (int)strlen(nomeG.data) / 2;
                                goTo(cella, NOME_VINCITORE_RIG);
                                printf("%s", nomeG.data);
                            }
                            fflush(stdout);
                            goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
                            if (!leggiClick(&riga, &colonna)){
                                continue;
                            }
                            if (areaCliccata(bVittoria[0], riga, colonna)){
                                confermato = 1;
                                esci = 1;
                            }
                        }
                    }else{
                        // round successivo
                        fflush(stdout);
                        while (!leggiClick(&riga, &colonna));
                        Set_round(partita, Get_round(*partita) + 1);
                        Set_turno(partita, TURNO_GIOCATORE1);
                        r = 0;
                        while (r < DIMENSIONE_GRIGLIA){
                            c = 0;
                            while (c < DIMENSIONE_GRIGLIA){
                                Set_griglia(partita, r, c, ' ');
                                c = c + 1;
                            }
                            r = r + 1;
                        }
                    }
                }else{
                    // round non terminato: torna al turno del giocatore
                    Set_turno(partita, TURNO_GIOCATORE1);
                }
            }
            continue;
        }

        // legge il click del giocatore
        if (!leggiClick(&riga, &colonna)){
            continue;
        }
        // rilevamento della cella cliccata tramite la funzione cellaCliccata di gioco.h
        cella = cellaCliccata(riga, colonna);

        if (cella != CELLA_NON_VALIDA){
            r = 0;
            c = 0;
            while (r * DIMENSIONE_GRIGLIA + c != cella){
                c = c + 1;
                if (c == DIMENSIONE_GRIGLIA){
                    c = 0;
                    r = r + 1;
                }
            }

            // se la cella è ancora libera
            if (Get_griglia(*partita, r, c) == ' ' || Get_griglia(*partita, r, c) == '\0'){
                // simbolo del giocatore corrente letto dalle impostazioni
                if (Get_turno(*partita) == TURNO_GIOCATORE1){
                    simboloCorrente = Get_simboloGiocatore1(*impostazioni);
                }
                else{
                    simboloCorrente = Get_simboloGiocatore2(*impostazioni);
                }

                // piazza il simbolo nella cella
                Set_griglia(partita, r, c, simboloCorrente);

                // controllo fine round
                vincitore = controllaVincitoreRound(*partita);
                piena = grigliaPiena(*partita);

                if (vincitore != '\0' || piena){
                    // Aggiorna punteggio se c'è un vincitore del round
                    if (vincitore != '\0'){
                        if (vincitore == Get_simboloGiocatore1(*impostazioni)){
                            // Aggiorna vittorie giocatore 1 e sconfitte giocatore 2
                            Set_vittorieG1(partita, Get_vittorieG1(*partita) + 1);
                            Set_sconfitteG2(partita, Get_sconfitteG2(*partita) + 1);
                        }else{
                            // Aggiorna vittorie giocatore 2 e sconfitte giocatore 1
                            Set_vittorieG2(partita, Get_vittorieG2(*partita) + 1);
                            Set_sconfitteG1(partita, Get_sconfitteG1(*partita) + 1);
                        }
                    }else{
                        // Pareggio round
                        Set_pareggiG1(partita, Get_pareggiG1(*partita) + 1);
                        Set_pareggiG2(partita, Get_pareggiG2(*partita) + 1);
                    }

                    // Stampa l'ultimo stato grafico prima di procedere
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    stampaSchermataGioco(schermatePartita[0]);
                    stampaGioco(*partita, *impostazioni);
                    goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
                    fflush(stdout);

                    // Se siamo all'ultimo round, termina la partita e vai alla schermata vittoria
                    if (Get_round(*partita) >= Get_numeroRound(*impostazioni)){
                        // Determina il risultato finale e salva le statistiche per-avversario
                        risultato = 0;
                        if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)){
                            risultato = RISULTATO_VITTORIA_G1; // vittoria G1
                        }else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)){
                            risultato = RISULTATO_VITTORIA_G2; // vittoria G2
                        }else{
                            risultato = RISULTATO_PAREGGIO; // pareggio
                        }
                        salvaStatistichePartita(Get_nomeGiocatore1(*impostazioni).data, Get_nomeGiocatore2(*impostazioni).data, risultato);

                        confermato = 0;
                        while (!confermato){
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            stampaSchermataGioco(schermatePartita[3]);

                            // Calcola e scrivi il vincitore finale
                            if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)){
                                // vittoria G1
                                nomeG = Get_nomeGiocatore1(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // ripulisce il puntino
                                cella = NOME_VINCITORE_COL - (int)strlen(nomeG.data) / 2;
                                goTo(cella, NOME_VINCITORE_RIG);
                                printf("%s", nomeG.data);
                            }else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)){
                                // vittoria G2
                                nomeG = Get_nomeGiocatore2(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // ripulisce il punto
                                cella = NOME_VINCITORE_COL - (int)strlen(nomeG.data) / 2;
                                goTo(cella, NOME_VINCITORE_RIG);
                                printf("%s", nomeG.data);
                            }
                            fflush(stdout);
                            goTo(CURSORE_BASE.col, CURSORE_BASE.rig);

                            if (!leggiClick(&riga, &colonna)){
                                continue;
                            }

                            // Verifica click su bVittoria[0]
                            if (areaCliccata(bVittoria[0], riga, colonna)){
                                confermato = 1;
                                esci = 1;
                            }
                        }
                    }else{
                        fflush(stdout);

                        while (!leggiClick(&riga, &colonna));

                        Set_round(partita, Get_round(*partita) + 1);
                        Set_turno(partita, TURNO_GIOCATORE1);
                        // resetta la griglia per il prossimo round
                        r = 0;
                        while (r < DIMENSIONE_GRIGLIA){
                            c = 0;
                            while (c < DIMENSIONE_GRIGLIA){
                                Set_griglia(partita, r, c, ' ');
                                c = c + 1;
                            }
                            r = r + 1;
                        }
                    }
                }else{
                    // Alterna il turno solo se il round non è terminato
                    if (Get_turno(*partita) == TURNO_GIOCATORE1){
                        Set_turno(partita, TURNO_GIOCATORE2);
                    }else{
                        Set_turno(partita, TURNO_GIOCATORE1);
                    }
                }
            }
        }else if (areaCliccata(bGiocoMenu[0], riga, colonna)){
            // esce al menu principale
            esci = 1;
        }else if (areaCliccata(bGiocoMenu[1], riga, colonna)){
            // mostra la schermata di salvataggio e conferma
            confermato = 0;
            while (!confermato){
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                stampaSchermataGioco(schermatePartita[1]);
                goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
                fflush(stdout);

                if (!leggiClick(&riga, &colonna)){
                    continue;
                }

                if (areaCliccata(bSalvaConferma[0], riga, colonna)){
                    // salva la partita ed esci al menu principale
                    salvaPartita(impostazioni, partita);
                    confermato = 1;
                    esci = 1;
                }else if (areaCliccata(bSalvaConferma[1], riga, colonna) || areaCliccata(bSalvaConferma[2], riga, colonna)){
                    // ritorna al gioco
                    confermato = 1;
                }
            }
        }else if (areaCliccata(bGiocoMenu[2], riga, colonna)){
            // apre il supporto del gioco
            abilitaTastiera();
            navigaSupporto();
            abilitaMouse();
        }
    }

    // ripristina terminale
    abilitaTastiera();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Controlla se c'è un vincitore del round. Ritorna il simbolo vincitore o '\0'.
char controllaVincitoreRound(Partita partita){
    int r;
    int c;

    // righe
    r = 0;
    while (r < 3){
        if (partita.griglia[r][0] != ' ' && partita.griglia[r][0] != '\0' && partita.griglia[r][0] == partita.griglia[r][1] && partita.griglia[r][1] == partita.griglia[r][2]){
            return partita.griglia[r][0];
        }
        r = r + 1;
    }
    // colonne
    c = 0;
    while (c < 3){
        if (partita.griglia[0][c] != ' ' && partita.griglia[0][c] != '\0' && partita.griglia[0][c] == partita.griglia[1][c] && partita.griglia[1][c] == partita.griglia[2][c]){
            return partita.griglia[0][c];
        }
        c = c + 1;
    }
    // diagonale principale
    if (partita.griglia[0][0] != ' ' && partita.griglia[0][0] != '\0' && partita.griglia[0][0] == partita.griglia[1][1] && partita.griglia[1][1] == partita.griglia[2][2]){
        return partita.griglia[0][0];
    }
    // diagonale secondaria
    if (partita.griglia[0][2] != ' ' && partita.griglia[0][2] != '\0' && partita.griglia[0][2] == partita.griglia[1][1] && partita.griglia[1][1] == partita.griglia[2][0]){
        return partita.griglia[0][2];
    }
    return '\0';
}

// Verifica se la griglia è piena. Ritorna 1 se piena, 0 altrimenti.
int grigliaPiena(Partita partita){
    int r;
    int c;

    r = 0;
    while (r < 3){
        c = 0;
        while (c < 3){
            if (partita.griglia[r][c] == ' ' || partita.griglia[r][c] == '\0'){
                return 0;
            }
            c = c + 1;
        }
        r = r + 1;
    }
    return 1;
}

#pragma endregion