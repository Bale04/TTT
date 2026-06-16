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
#include "supporto.h"

#pragma region funzioni esterne
// funzioni esterne da salvataggio.c
extern int salvaPartita(const Impostazioni *impostazioni, const Partita *partita);
extern int caricaPartita(Impostazioni *impostazioni, Partita *partita);

// funzione esterna da statistiche.c
extern void salvaStatistichePartita(const char *nomeG1, const char *nomeG2, int risultato);

// funzioni esterne da impostazioni.c
extern Stringa Get_nomePartita(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
extern Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
extern int    Get_numeroRound(Impostazioni impostazioni);
extern char   Get_simboloGiocatore1(Impostazioni impostazioni);
extern char   Get_simboloGiocatore2(Impostazioni impostazioni);
extern int    Get_modoPartita(Impostazioni impostazioni);
#pragma endregion

#pragma region dichiarazioni funzioni
// funzioni di accesso Partita
void Set_griglia(Partita *partita, int riga, int colonna, char simbolo);
char Get_griglia(Partita partita, int riga, int colonna);
void Set_turno(Partita *partita, int turno);
int  Get_turno(Partita partita);
void Set_round(Partita *partita, int round);
int  Get_round(Partita partita);
// funzioni di accesso Partita - statisticheG1
int  Get_vittorieG1(Partita partita);
void Set_vittorieG1(Partita *partita, int v);
int  Get_sconfitteG1(Partita partita);
void Set_sconfitteG1(Partita *partita, int v);
int  Get_pareggiG1(Partita partita);
void Set_pareggiG1(Partita *partita, int v);
// funzioni di accesso Partita - statisticheG2
int  Get_vittorieG2(Partita partita);
void Set_vittorieG2(Partita *partita, int v);
int  Get_sconfitteG2(Partita partita);
void Set_sconfitteG2(Partita *partita, int v);
int  Get_pareggiG2(Partita partita);
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
int  controlloGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]);
int  calcolaPunteggio(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA], char simboloBot, char simboloAvversario, int isMaximizing);
int  mossaBot(Partita partita, char simboloBot, char simboloAvversario);

#pragma endregion


// ------------------------- FUNZIONI DI ACCESSO PARTITA -------------------------------
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
// ---------------------STATISTICHE G1---------------------------
int  Get_vittorieG1(Partita partita){ 
    return partita.statisticheG1.numeroVittorie; 
}
void Set_vittorieG1(Partita *partita, int v){ 
    partita->statisticheG1.numeroVittorie = v;
}
int  Get_sconfitteG1(Partita partita){ 
    return partita.statisticheG1.numeroSconfitte; 
}
void Set_sconfitteG1(Partita *partita, int v){ 
    partita->statisticheG1.numeroSconfitte = v; 
}
int  Get_pareggiG1(Partita partita){ 
    return partita.statisticheG1.numeroPareggi; 
}
void Set_pareggiG1(Partita *partita, int v){ 
    partita->statisticheG1.numeroPareggi = v; 
}
// ---------------------STATISTICHE G2---------------------------
int  Get_vittorieG2(Partita partita){ 
    return partita.statisticheG2.numeroVittorie; 
}
void Set_vittorieG2(Partita *partita, int v){ 
    partita->statisticheG2.numeroVittorie = v; 
}
int  Get_sconfitteG2(Partita partita){ 
    return partita.statisticheG2.numeroSconfitte; 
}
void Set_sconfitteG2(Partita *partita, int v){ 
    partita->statisticheG2.numeroSconfitte = v; 
}
int  Get_pareggiG2(Partita partita){ 
    return partita.statisticheG2.numeroPareggi; 
}
void Set_pareggiG2(Partita *partita, int v){ 
    partita->statisticheG2.numeroPareggi = v; 
}

#pragma endregion


// ----------------------------- BOT CPU --------------------------------
#pragma region bot

// controlla il vincitore sulla copia della griglia usata dal bot
char controllaVincitoreGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]) {
    char vincitore = '\0';
    int i = 0;

    // Controlla righe e colonne
    while (i < DIMENSIONE_GRIGLIA && vincitore == '\0') {
        if (g[i][0] != ' ' && g[i][0] != '\0' && g[i][0] == g[i][1] && g[i][1] == g[i][2]) {
            vincitore = g[i][0];
        } else if (g[0][i] != ' ' && g[0][i] != '\0' && g[0][i] == g[1][i] && g[1][i] == g[2][i]) {
            vincitore = g[0][i];
        }
        i = i + 1;
    }

    // Controlla diagonale principale e secondaria
    if (vincitore == '\0') {
        if (g[0][0] != ' ' && g[0][0] != '\0' && g[0][0] == g[1][1] && g[1][1] == g[2][2]) {
            vincitore = g[0][0];
        } else if (g[0][2] != ' ' && g[0][2] != '\0' && g[0][2] == g[1][1] && g[1][1] == g[2][0]) {
            vincitore = g[0][2];
        }
    }

    return vincitore;
}

// controlla se la griglia è piena
int controlloGriglia(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA]) {
    int piena = 1;
    int i = 0;
    int r;
    int c;

    // Scansiona le 9 celle
    while (i < 9 && piena == 1) {
        r = i / DIMENSIONE_GRIGLIA;
        c = i % DIMENSIONE_GRIGLIA;
        if (g[r][c] == ' ' || g[r][c] == '\0') {
            piena = 0;
        }
        i = i + 1;
    }

    return piena;
}

// algoritmo ricorsivo per il calcolo del punteggio della posizione
// isMaximizing == 1: turno del bot (massimizza)
// isMaximizing == 0: turno del giocatore (minimizza)
int calcolaPunteggio(char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA], char simboloBot, char simboloAvversario, int isMaximizing) {
    int punteggio = 0;
    int i;
    int r;
    int c;
    int p;
    char vinc = controllaVincitoreGriglia(g);

    if (vinc == simboloBot) {
        punteggio = PUNTEGGIO_VITTORIA;
    } else if (vinc == simboloAvversario) {
        punteggio = PUNTEGGIO_SCONFITTA;
    } else if (controlloGriglia(g)) {
        punteggio = RISULTATO_PAREGGIO;
    } else {
        if (isMaximizing) {
            int best = PUNTEGGIO_MINIMO;
            i = 0;
            while (i < 9) {
                r = i / DIMENSIONE_GRIGLIA;
                c = i % DIMENSIONE_GRIGLIA;
                if (g[r][c] == ' ' || g[r][c] == '\0') {
                    g[r][c] = simboloBot;
                    p = calcolaPunteggio(g, simboloBot, simboloAvversario, 0);
                    g[r][c] = ' ';
                    if (p > best) {
                        best = p;
                    }
                }
                i = i + 1;
            }
            punteggio = best;
        } else {
            int best = PUNTEGGIO_MASSIMO;
            i = 0;
            while (i < 9) {
                r = i / DIMENSIONE_GRIGLIA;
                c = i % DIMENSIONE_GRIGLIA;
                if (g[r][c] == ' ' || g[r][c] == '\0') {
                    g[r][c] = simboloAvversario;
                    p = calcolaPunteggio(g, simboloBot, simboloAvversario, 1);
                    g[r][c] = ' ';
                    if (p < best) {
                        best = p;
                    }
                }
                i = i + 1;
            }
            punteggio = best;
        }
    }

    return punteggio;
}

// restituisce la cella migliore (0-8) per il bot, o -1 se nessuna mossa disponibile
int mossaBot(Partita partita, char simboloBot, char simboloAvversario) {
    char g[DIMENSIONE_GRIGLIA][DIMENSIONE_GRIGLIA];
    int best = PUNTEGGIO_MINIMO;
    int migRiga = CELLA_NON_VALIDA;
    int migCol = CELLA_NON_VALIDA;
    int i = 0;
    int r;
    int c;
    int p;
    int cellaMossa = CELLA_NON_VALIDA;

    // Copia lo stato della griglia
    while (i < 9) {
        r = i / DIMENSIONE_GRIGLIA;
        c = i % DIMENSIONE_GRIGLIA;
        g[r][c] = Get_griglia(partita, r, c);
        i = i + 1;
    }

    // Ricerca la mossa migliore
    i = 0;
    while (i < 9) {
        r = i / DIMENSIONE_GRIGLIA;
        c = i % DIMENSIONE_GRIGLIA;
        if (g[r][c] == ' ' || g[r][c] == '\0') {
            g[r][c] = simboloBot;
            p = calcolaPunteggio(g, simboloBot, simboloAvversario, 0);
            g[r][c] = ' ';
            if (p > best) {
                best = p;
                migRiga = r;
                migCol = c;
            }
        }
        i = i + 1;
    }

    if (migRiga != CELLA_NON_VALIDA) {
        cellaMossa = migRiga * DIMENSIONE_GRIGLIA + migCol;
    }

    return cellaMossa;
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


// mostra a schermo i dati della partita in corso
void stampaGioco(Partita partita, Impostazioni impostazioni) {
    int turno = Get_turno(partita);
    int round = Get_round(partita);

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
    int r = 0;
    while (r < 3) {
        int c = 0;
        while (c < 3) {
            char simbolo = Get_griglia(partita, r, c);
            goTo(GRIGLIA_CENTRO_COL[c], GRIGLIA_CENTRO_RIG[r]);
            if (simbolo == ' ' || simbolo == '\0') {
                printf(" ");
            } else {
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

void navigaPartita(Partita *partita, Impostazioni *impostazioni) {
    int esci = 0;

    // Se c'è una partita precedente specificata la carica
    if (strlen(impostazioni->partitaPrecedente.data) > 0) {
        if (caricaPartita(impostazioni, partita)) {
            // dopo aver caricato la partita pulisce il campo partitaPrecedente in modo che non venga caricata di nuovo ad ogni ciclo di while
            impostazioni->partitaPrecedente.data[0] = '\0';
        } else {
            // Se fallisce il caricamento inizializza normalmente
            Set_turno(partita, 1);
            Set_round(partita, 1);
            Set_vittorieG1(partita, 0);
            Set_sconfitteG1(partita, 0);
            Set_pareggiG1(partita, 0);
            Set_vittorieG2(partita, 0);
            Set_sconfitteG2(partita, 0);
            Set_pareggiG2(partita, 0);
            int ri = 0;
            while (ri < 3) {
                int ci = 0;
                while (ci < 3) {
                    Set_griglia(partita, ri, ci, ' ');
                    ci = ci + 1;
                }
                ri = ri + 1;
            }
        }
    } else {
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
        int ri = 0;
        while (ri < 3) {
            int ci = 0;
            while (ci < 3) {
                Set_griglia(partita, ri, ci, ' ');
                ci = ci + 1;
            }
            ri = ri + 1;
        }
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

        // stampa a schermo i dati della partita
        stampaGioco(*partita, *impostazioni);
        goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
        fflush(stdout);

        int riga, colonna;

        // se modalità CPU e turno del bot (giocatore 2), muove automaticamente
        if (Get_modoPartita(*impostazioni) == MODO_CPU && Get_turno(*partita) == TURNO_GIOCATORE2) {
            char simboloBot = Get_simboloGiocatore2(*impostazioni);
            char simboloAvv = Get_simboloGiocatore1(*impostazioni);
            int  cellaBot    = mossaBot(*partita, simboloBot, simboloAvv);
            if (cellaBot != CELLA_NON_VALIDA) {
                Set_griglia(partita, cellaBot / DIMENSIONE_GRIGLIA, cellaBot % DIMENSIONE_GRIGLIA, simboloBot);
                // controllo fine round
                char vincBt = controllaVincitoreRound(*partita);
                int  pienaBt = grigliaPiena(*partita);
                if (vincBt != '\0' || pienaBt) {
                    if (vincBt != '\0') {
                        if (vincBt == Get_simboloGiocatore1(*impostazioni)) {
                            Set_vittorieG1(partita, Get_vittorieG1(*partita) + 1);
                            Set_sconfitteG2(partita, Get_sconfitteG2(*partita) + 1);
                        } else {
                            Set_vittorieG2(partita, Get_vittorieG2(*partita) + 1);
                            Set_sconfitteG1(partita, Get_sconfitteG1(*partita) + 1);
                        }
                    } else {
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

                    if (Get_round(*partita) >= Get_numeroRound(*impostazioni)) {
                        // fine partita
                        int risultato;
                        if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)) {
                            risultato = RISULTATO_VITTORIA_G1;
                        } else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)) {
                            risultato = RISULTATO_VITTORIA_G2;
                        } else {
                            risultato = RISULTATO_PAREGGIO;
                        }
                        salvaStatistichePartita(Get_nomeGiocatore1(*impostazioni).data, Get_nomeGiocatore2(*impostazioni).data, risultato);

                        int tornaAlMenuBt = 0;
                        while (!tornaAlMenuBt) {
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            stampaSchermataGioco(schermatePartita[3]);
                            if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)) {
                                Stringa nomeG1 = Get_nomeGiocatore1(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    ");
                                goTo(NOME_VINCITORE_COL - (int)strlen(nomeG1.data) / 2, NOME_VINCITORE_RIG);
                                printf("%s", nomeG1.data);
                            } else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)) {
                                Stringa nomeG2 = Get_nomeGiocatore2(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    ");
                                goTo(NOME_VINCITORE_COL - (int)strlen(nomeG2.data) / 2, NOME_VINCITORE_RIG);
                                printf("%s", nomeG2.data);
                            }
                            fflush(stdout);
                            goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
                            int rigaVt, colonnaVt;
                            if (!leggiClick(&rigaVt, &colonnaVt)) {
                                continue;
                            }
                            if (areaCliccata(bVittoria[0], rigaVt, colonnaVt)) {
                                tornaAlMenuBt = 1;
                                esci = 1;
                            }
                        }
                    } else {
                        // round successivo
                        fflush(stdout);
                        while (!leggiClick(&riga, &colonna));
                        Set_round(partita, Get_round(*partita) + 1);
                        Set_turno(partita, TURNO_GIOCATORE1);
                        int ri = 0;
                        while (ri < DIMENSIONE_GRIGLIA) {
                            int ci = 0;
                            while (ci < DIMENSIONE_GRIGLIA) { Set_griglia(partita, ri, ci, ' '); ci = ci + 1; }
                            ri = ri + 1;
                        }
                    }
                } else {
                    // round non terminato: torna al turno del giocatore
                    Set_turno(partita, TURNO_GIOCATORE1);
                }
            }
            continue;
        }

        // legge il click del giocatore
        if (!leggiClick(&riga, &colonna)) {
            continue;
        }

        // rilevamento della cella cliccata tramite la funzione cellaCliccata di gioco.h
        int cella = cellaCliccata(riga, colonna);

        if (cella != CELLA_NON_VALIDA) {
            int cellaR = cella / DIMENSIONE_GRIGLIA;
            int cellaC = cella % DIMENSIONE_GRIGLIA;

            // se la cella è ancora libera
            if (Get_griglia(*partita, cellaR, cellaC) == ' ' || Get_griglia(*partita, cellaR, cellaC) == '\0') {
                // simbolo del giocatore corrente letto dalle impostazioni
                char simboloCorrente;
                if (Get_turno(*partita) == TURNO_GIOCATORE1) {
                    simboloCorrente = Get_simboloGiocatore1(*impostazioni);
                } else {
                    simboloCorrente = Get_simboloGiocatore2(*impostazioni);
                }

                // piazza il simbolo nella cella
                Set_griglia(partita, cellaR, cellaC, simboloCorrente);

                // controllo fine round
                char vincitoreSimbolo = controllaVincitoreRound(*partita);
                int piena = grigliaPiena(*partita);

                if (vincitoreSimbolo != '\0' || piena) {
                    // Aggiorna punteggio se c'è un vincitore del round
                    if (vincitoreSimbolo != '\0') {
                        if (vincitoreSimbolo == Get_simboloGiocatore1(*impostazioni)) {
                            Set_vittorieG1(partita, Get_vittorieG1(*partita) + 1);
                            Set_sconfitteG2(partita, Get_sconfitteG2(*partita) + 1);
                        } else {
                            Set_vittorieG2(partita, Get_vittorieG2(*partita) + 1);
                            Set_sconfitteG1(partita, Get_sconfitteG1(*partita) + 1);
                        }
                    } else {
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
                    if (Get_round(*partita) >= Get_numeroRound(*impostazioni)) {
                        // Determina il risultato finale e salva le statistiche per-avversario
                        int risultato;
                        if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)) {
                            risultato = RISULTATO_VITTORIA_G1; // vittoria G1
                        } else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)) {
                            risultato = RISULTATO_VITTORIA_G2; // vittoria G2
                        } else {
                            risultato = RISULTATO_PAREGGIO; // pareggio
                        }
                        salvaStatistichePartita(Get_nomeGiocatore1(*impostazioni).data, Get_nomeGiocatore2(*impostazioni).data, risultato);

                        int tornaAlMenuCliccato = 0;
                        while (!tornaAlMenuCliccato) {
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            stampaSchermataGioco(schermatePartita[3]);

                            // Calcola e scrivi il vincitore finale
                            if (Get_vittorieG1(*partita) > Get_vittorieG2(*partita)) {
                                // vittoria G1
                                Stringa nomeG1 = Get_nomeGiocatore1(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // ripulisce il puntino
                                int startCol = NOME_VINCITORE_COL - (int)strlen(nomeG1.data) / 2;
                                goTo(startCol, NOME_VINCITORE_RIG);
                                printf("%s", nomeG1.data);
                            } else if (Get_vittorieG2(*partita) > Get_vittorieG1(*partita)) {
                                // vittoria G2
                                Stringa nomeG2 = Get_nomeGiocatore2(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // ripulisce il punto
                                int startCol = NOME_VINCITORE_COL - (int)strlen(nomeG2.data) / 2;
                                goTo(startCol, NOME_VINCITORE_RIG);
                                printf("%s", nomeG2.data);
                            }
                            fflush(stdout);
                            goTo(CURSORE_BASE.col, CURSORE_BASE.rig);

                            int rigaConf, colonnaConf;
                            if (!leggiClick(&rigaConf, &colonnaConf)) {
                                continue;
                            }

                            // Verifica click su bVittoria[0]
                            if (areaCliccata(bVittoria[0], rigaConf, colonnaConf)) {
                                tornaAlMenuCliccato = 1;
                                esci = 1;
                            }
                        }
                    } else {
                        fflush(stdout);

                        while (!leggiClick(&riga, &colonna));

                        Set_round(partita, Get_round(*partita) + 1);
                        Set_turno(partita, TURNO_GIOCATORE1);
                        // resetta la griglia per il prossimo round
                        int ri = 0;
                        while (ri < DIMENSIONE_GRIGLIA) {
                            int ci = 0;
                            while (ci < DIMENSIONE_GRIGLIA) {
                                Set_griglia(partita, ri, ci, ' ');
                                ci = ci + 1;
                            }
                            ri = ri + 1;
                        }
                    }
                } else {
                    // Alterna il turno solo se il round non è terminato
                    if (Get_turno(*partita) == TURNO_GIOCATORE1) {
                        Set_turno(partita, TURNO_GIOCATORE2);
                    } else {
                        Set_turno(partita, TURNO_GIOCATORE1);
                    }
                }
            }
        } else if (areaCliccata(bGiocoMenu[0], riga, colonna)) {
            // esce al menu principale
            esci = 1;
        } else if (areaCliccata(bGiocoMenu[1], riga, colonna)) {
            // mostra la schermata di salvataggio e conferma
            int confermato = 0;
            while (!confermato) {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                stampaSchermataGioco(schermatePartita[1]);
                goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
                fflush(stdout);

                int rigaConf, colonnaConf;
                if (!leggiClick(&rigaConf, &colonnaConf)) {
                    continue;
                }

                if (areaCliccata(bSalvaConferma[0], rigaConf, colonnaConf)) {
                    // salva la partita ed esci al menu principale
                    salvaPartita(impostazioni, partita);
                    confermato = 1;
                    esci = 1;
                } else if (areaCliccata(bSalvaConferma[1], rigaConf, colonnaConf) || areaCliccata(bSalvaConferma[2], rigaConf, colonnaConf)) {
                    // ritorna al gioco
                    confermato = 1;
                }
            }
        } else if (areaCliccata(bGiocoMenu[2], riga, colonna)) {
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
char controllaVincitoreRound(Partita partita) {
    // righe
    int i = 0;
    while (i < 3) {
        if (partita.griglia[i][0] != ' ' && partita.griglia[i][0] != '\0' &&
            partita.griglia[i][0] == partita.griglia[i][1] &&
            partita.griglia[i][1] == partita.griglia[i][2]) {
            return partita.griglia[i][0];
        }
        i = i + 1;
    }
    // colonne
    i = 0;
    while (i < 3) {
        if (partita.griglia[0][i] != ' ' && partita.griglia[0][i] != '\0' &&
            partita.griglia[0][i] == partita.griglia[1][i] &&
            partita.griglia[1][i] == partita.griglia[2][i]) {
            return partita.griglia[0][i];
        }
        i = i + 1;
    }
    // diagonale principale
    if (partita.griglia[0][0] != ' ' && partita.griglia[0][0] != '\0' &&
        partita.griglia[0][0] == partita.griglia[1][1] &&
        partita.griglia[1][1] == partita.griglia[2][2]) {
        return partita.griglia[0][0];
    }
    // diagonale secondaria
    if (partita.griglia[0][2] != ' ' && partita.griglia[0][2] != '\0' &&
        partita.griglia[0][2] == partita.griglia[1][1] &&
        partita.griglia[1][1] == partita.griglia[2][0]) {
        return partita.griglia[0][2];
    }
    return '\0';
}


// Verifica se la griglia è piena. Ritorna 1 se piena, 0 altrimenti.
int grigliaPiena(Partita partita) {
    int r = 0;
    while (r < 3) {
        int c = 0;
        while (c < 3) {
            if (partita.griglia[r][c] == ' ' || partita.griglia[r][c] == '\0') {
                return 0;
            }
            c = c + 1;
        }
        r = r + 1;
    }
    return 1;
}

#pragma endregion