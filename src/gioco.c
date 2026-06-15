/*
 ============================================================================
 Name        : gioco.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 0.4
 Copyright   : Your copyright notice
 Description : file di gestione del gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gioco.h"
#include "supporto.h"
#include "salvataggio.h"

// funzione esterna da statistiche.c
extern void salvaStatistichePartita(const char *nomeG1, const char *nomeG2, int risultato);

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
void navigaPartita(Partita *partita, Impostazioni *impostazioni);

// funzioni di accesso Partita
void Set_griglia(Partita *partita, int riga, int colonna, char simbolo);
char Get_griglia(Partita partita, int riga, int colonna);
void Set_turno(Partita *partita, int turno);
int  Get_turno(Partita partita);
void Set_round(Partita *partita, int round);
int  Get_round(Partita partita);

// funzioni di verifica stato round
char controllaVincitoreRound(Partita partita);
int grigliaPiena(Partita partita);

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


// sovrascrive i dati dinamici sulla schermata: nome partita, round, turno, griglia, vittorie
void stampaGioco(Partita partita, Impostazioni impostazioni) {
    int turno = Get_turno(partita);
    int round = Get_round(partita);

    // stampa il nome della partita centrato nella barra del titolo (riga 6)
    goTo(GIOCO_TITOLO_COL, GIOCO_TITOLO_RIG);
    printf("%s", Get_nomePartita(impostazioni).data);

    // stampa il numero del round (riga 8, dopo "ROUND: ")
    goTo(GIOCO_ROUND_COL, GIOCO_ROUND_RIG);
    printf("%d", round);

    // stampa il turno (numero del giocatore: 1 o 2) (riga 8, dopo "TURNO: ")
    goTo(GIOCO_TURNO_COL, GIOCO_TURNO_RIG);
    printf("%d", turno);

    // stampa le vittorie a sinistra (riga 12 per G1, riga 13 per G2, colonna 11)
    goTo(VITTORIA_COL, VITTORIA_G1_RIG);
    printf("%d", partita.statisticheG1.numeroVittorie);
    goTo(VITTORIA_COL, VITTORIA_G2_RIG);
    printf("%d", partita.statisticheG2.numeroVittorie);

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

    // Se c'è una partita precedente specificata, caricala
    if (strlen(impostazioni->partitaPrecedente.data) > 0) {
        if (caricaPartita(impostazioni, partita)) {
            // Dopo il caricamento con successo, puliamo partitaPrecedente per evitare ricaricamenti futuri
            memset(impostazioni->partitaPrecedente.data, 0, sizeof(impostazioni->partitaPrecedente.data));
        } else {
            // Se fallisce il caricamento, inizializza normalmente
            Set_turno(partita, 1);
            Set_round(partita, 1);
            partita->statisticheG1.numeroVittorie = 0;
            partita->statisticheG1.numeroSconfitte = 0;
            partita->statisticheG1.numeroPareggi = 0;
            partita->statisticheG2.numeroVittorie = 0;
            partita->statisticheG2.numeroSconfitte = 0;
            partita->statisticheG2.numeroPareggi = 0;
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
        // Inizializza una nuova partita normalmente
        Set_turno(partita, 1);
        Set_round(partita, 1);
        partita->statisticheG1.numeroVittorie = 0;
        partita->statisticheG1.numeroSconfitte = 0;
        partita->statisticheG1.numeroPareggi = 0;
        partita->statisticheG2.numeroVittorie = 0;
        partita->statisticheG2.numeroSconfitte = 0;
        partita->statisticheG2.numeroPareggi = 0;
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

        // sovrascrive i dati dinamici (nome partita, round, turno, griglia, vittorie)
        stampaGioco(*partita, *impostazioni);
        goTo(1, 25);
        fflush(stdout);

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
                char simboloCorrente;
                if (Get_turno(*partita) == 1) {
                    simboloCorrente = Get_simboloGiocatore1(*impostazioni);
                } else {
                    simboloCorrente = Get_simboloGiocatore2(*impostazioni);
                }

                // piazza il simbolo nella cella
                Set_griglia(partita, cellaR, cellaC, simboloCorrente);

                // --- CONTROLLO FINE ROUND ---
                char vincitoreSimbolo = controllaVincitoreRound(*partita);
                int piena = grigliaPiena(*partita);

                if (vincitoreSimbolo != '\0' || piena) {
                    // Aggiorna punteggio se c'è un vincitore del round
                    if (vincitoreSimbolo != '\0') {
                        if (vincitoreSimbolo == Get_simboloGiocatore1(*impostazioni)) {
                            partita->statisticheG1.numeroVittorie = partita->statisticheG1.numeroVittorie + 1;
                            partita->statisticheG2.numeroSconfitte = partita->statisticheG2.numeroSconfitte + 1;
                        } else {
                            partita->statisticheG2.numeroVittorie = partita->statisticheG2.numeroVittorie + 1;
                            partita->statisticheG1.numeroSconfitte = partita->statisticheG1.numeroSconfitte + 1;
                        }
                    } else {
                        // Pareggio round
                        partita->statisticheG1.numeroPareggi = partita->statisticheG1.numeroPareggi + 1;
                        partita->statisticheG2.numeroPareggi = partita->statisticheG2.numeroPareggi + 1;
                    }

                    // Stampa l'ultimo stato grafico prima di procedere
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                    stampaSchermataGioco(schermatePartita[0]);
                    stampaGioco(*partita, *impostazioni);
                    goTo(1, 25);
                    fflush(stdout);

                    // Se siamo all'ultimo round, termina la partita e vai alla schermata vittoria
                    if (partita->round >= Get_numeroRound(*impostazioni)) {
                        // Determina il risultato finale e salva le statistiche per-avversario
                        int risultato;
                        if (partita->statisticheG1.numeroVittorie > partita->statisticheG2.numeroVittorie) {
                            risultato = 1; // vittoria G1
                        } else if (partita->statisticheG2.numeroVittorie > partita->statisticheG1.numeroVittorie) {
                            risultato = 2; // vittoria G2
                        } else {
                            risultato = 0; // pareggio
                        }
                        salvaStatistichePartita(Get_nomeGiocatore1(*impostazioni).data, Get_nomeGiocatore2(*impostazioni).data, risultato);

                        int tornaAlMenuCliccato = 0;
                        while (!tornaAlMenuCliccato) {
#ifdef _WIN32
                            system("cls");
#else
                            system("clear");
#endif
                            stampaSchermataGioco(schermatePartita[3]); // Vittoria.txt

                            // Calcola e scrivi il vincitore finale
                            if (partita->statisticheG1.numeroVittorie > partita->statisticheG2.numeroVittorie) {
                                Stringa nomeG1 = Get_nomeGiocatore1(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // ripulisce il puntino
                                int startCol = NOME_VINCITORE_COL - (int)strlen(nomeG1.data) / 2;
                                goTo(startCol, NOME_VINCITORE_RIG);
                                printf("%s", nomeG1.data);
                            } else if (partita->statisticheG2.numeroVittorie > partita->statisticheG1.numeroVittorie) {
                                Stringa nomeG2 = Get_nomeGiocatore2(*impostazioni);
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // ripulisce il punto
                                int startCol = NOME_VINCITORE_COL - (int)strlen(nomeG2.data) / 2;
                                goTo(startCol, NOME_VINCITORE_RIG);
                                printf("%s", nomeG2.data);
                            } else {
                                // Pareggio finale: non stampa nulla al vincitore
                                goTo(32, 12);
                                printf("                   "); // Cancella "VINCE IL GIOCATORE:"
                                goTo(NOME_VINCITORE_COL - 10, NOME_VINCITORE_RIG);
                                printf("                    "); // Cancella il punto
                            }
                            fflush(stdout);
                            goTo(1, 25);

                            int rigaConf, colonnaConf;
                            if (!leggiClick(&rigaConf, &colonnaConf))
                                continue;

                            // Verifica click su bVittoria[0] (TORNA AL MENU)
                            if (areaCliccata(bVittoria[0], rigaConf, colonnaConf)) {
                                tornaAlMenuCliccato = 1;
                                esci = 1;
                            }
                        }
                    } else {
                        // Se non è l'ultimo round, mostra messaggio e passa al round successivo
                        goTo(22, 22);
                        printf("ROUND TERMINATO! Clicca per continuare...");
                        goTo(1, 25);
                        fflush(stdout);

                        int rTemp, cTemp;
                        while (!leggiClick(&rTemp, &cTemp));

                        partita->round = partita->round + 1;
                        Set_turno(partita, 1);
                        // resetta la griglia per il prossimo round
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
                    // Alterna il turno solo se il round non è terminato
                    if (Get_turno(*partita) == 1) {
                        Set_turno(partita, 2);
                    } else {
                        Set_turno(partita, 1);
                    }
                }
            }
        } else if (areaCliccata(bGiocoMenu[0], riga, colonna)) {
            // [ESCI] - esce direttamente al menu principale
            esci = 1;
        } else if (areaCliccata(bGiocoMenu[1], riga, colonna)) {
            // [SALVA PARTITA] - mostra la schermata di salvataggio e conferma
            int confermato = 0;
            while (!confermato) {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                stampaSchermataGioco(schermatePartita[1]); // SalvaPartita.txt
                goTo(1, 25);
                fflush(stdout);

                int rigaConf, colonnaConf;
                if (!leggiClick(&rigaConf, &colonnaConf))
                    continue;

                if (areaCliccata(bSalvaConferma[0], rigaConf, colonnaConf)) {
                    // Cliccato SI: salva la partita ed esci al menu principale
                    salvaPartita(impostazioni, partita);
                    confermato = 1;
                    esci = 1;
                } else if (areaCliccata(bSalvaConferma[1], rigaConf, colonnaConf) ||
                           areaCliccata(bSalvaConferma[2], rigaConf, colonnaConf)) {
                    // Cliccato NO o ESCI: ritorna al gioco
                    confermato = 1;
                }
            }
        } else if (areaCliccata(bGiocoMenu[2], riga, colonna)) {
            // [SUPPORTO] - apre il supporto dal gioco
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
    printf("Partita terminata.\n");
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