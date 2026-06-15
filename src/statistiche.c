/*
 ============================================================================
 Name        : statistiche.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Description : Gestione delle statistiche di gioco per avversario
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statistiche.h"
#include "mouse.h"

// numero massimo di avversari per pagina nella schermata StatisticheLista
#define AVVERSARI_PER_PAGINA 5


// --------------------- STAMPA SCHERMATA ---------------------
#pragma region stampa

void stampaSchermataStatistiche(const char *nomeSchermata) {
    FILE *fp;
    int c;
    char nomeCompleto[256];

    sprintf(nomeCompleto, PERCORSO_STATISTICHE, nomeSchermata);
    fp = fopen(nomeCompleto, "r");
    if (fp == NULL) {
        printf("Errore caricamento schermata statistiche: %s\n", nomeCompleto);
    } else {
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);
        }
        fclose(fp);
    }
}

#pragma endregion


// --------------------- GESTIONE FILE STATISTICHE ---------------------
#pragma region gestione file

// Aggiorna il file statistiche di un giocatore per il record vs un avversario
// tipo: 1 = vittoria, 2 = sconfitta, 0 = pareggio
static void aggiornaFileGiocatore(const char *nomeGiocatore, const char *nomeAvversario, int tipo) {
    char percorso[256];
    sprintf(percorso, PERCORSO_STATS_SALVATE, nomeGiocatore);

    RecordAvversario *lista = NULL;
    int numAvversari = 0;
    int trovato = 0;

    // Prova a caricare il file esistente
    FILE *fp = fopen(percorso, "rb");
    if (fp != NULL) {
        fread(&numAvversari, sizeof(int), 1, fp);
        if (numAvversari > 0) {
            lista = (RecordAvversario *)malloc(numAvversari * sizeof(RecordAvversario));
            fread(lista, sizeof(RecordAvversario), numAvversari, fp);
        }
        fclose(fp);
    }

    // Cerca il record dell'avversario nella lista
    int i = 0;
    while (i < numAvversari) {
        if (strcmp(lista[i].nomeAvversario, nomeAvversario) == 0) {
            trovato = 1;
            if (tipo == 1) {
                lista[i].stats.numeroVittorie = lista[i].stats.numeroVittorie + 1;
            } else if (tipo == 2) {
                lista[i].stats.numeroSconfitte = lista[i].stats.numeroSconfitte + 1;
            } else {
                lista[i].stats.numeroPareggi = lista[i].stats.numeroPareggi + 1;
            }
            break;
        }
        i = i + 1;
    }

    // Se l'avversario non esiste, aggiungilo alla lista
    if (!trovato) {
        numAvversari = numAvversari + 1;
        lista = (RecordAvversario *)realloc(lista, numAvversari * sizeof(RecordAvversario));
        memset(&lista[numAvversari - 1], 0, sizeof(RecordAvversario));
        strncpy(lista[numAvversari - 1].nomeAvversario, nomeAvversario, 19);
        if (tipo == 1) {
            lista[numAvversari - 1].stats.numeroVittorie = 1;
        } else if (tipo == 2) {
            lista[numAvversari - 1].stats.numeroSconfitte = 1;
        } else {
            lista[numAvversari - 1].stats.numeroPareggi = 1;
        }
    }

    // Salva il file aggiornato
    fp = fopen(percorso, "wb");
    if (fp != NULL) {
        fwrite(&numAvversari, sizeof(int), 1, fp);
        fwrite(lista, sizeof(RecordAvversario), numAvversari, fp);
        fclose(fp);
    }

    if (lista != NULL) {
        free(lista);
    }
}

// Salva le statistiche della partita per entrambi i giocatori
// risultato: 1 = vittoria G1, 2 = vittoria G2, 0 = pareggio
void salvaStatistichePartita(const char *nomeG1, const char *nomeG2, int risultato) {
    if (risultato == 1) {
        aggiornaFileGiocatore(nomeG1, nomeG2, 1);  // G1 vittoria vs G2
        aggiornaFileGiocatore(nomeG2, nomeG1, 2);  // G2 sconfitta vs G1
    } else if (risultato == 2) {
        aggiornaFileGiocatore(nomeG1, nomeG2, 2);  // G1 sconfitta vs G2
        aggiornaFileGiocatore(nomeG2, nomeG1, 1);  // G2 vittoria vs G1
    } else {
        aggiornaFileGiocatore(nomeG1, nomeG2, 0);  // pareggio per entrambi
        aggiornaFileGiocatore(nomeG2, nomeG1, 0);
    }
}

#pragma endregion


// --------------------- NAVIGAZIONE STATISTICHE ---------------------
#pragma region navigazione

void navigaStatistiche(void) {
    int esci = 0;
    int schermata = 0;  // 0 = StatisticheMenu, 1 = StatisticheLista
    int pagina = 0;
    RecordAvversario *lista = NULL;
    int numAvversari = 0;
    char nomeRicercato[20];
    memset(nomeRicercato, 0, sizeof(nomeRicercato));

    abilitaMouse();

    while (!esci) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        if (schermata == 0) {
            // ----- StatisticheMenu -----
            stampaSchermataStatistiche(schermateStatistiche[0].data);
            goTo(1, 25);
            fflush(stdout);

            int riga, colonna;
            if (!leggiClick(&riga, &colonna))
                continue;

            if (areaCliccata(bStatMenu[0], riga, colonna)) {
                // [RICERCA] - input nome giocatore
                goTo(bStatMenu[0].c1 + 1, bStatMenu[0].r);
                abilitaTastiera();
                scanf("%19s", nomeRicercato);
                abilitaMouse();

                // Cerca il file del giocatore nella cartella StatisticheSalvate
                char percorso[256];
                sprintf(percorso, PERCORSO_STATS_SALVATE, nomeRicercato);
                FILE *fp = fopen(percorso, "rb");
                if (fp != NULL) {
                    // File trovato: carica i dati
                    if (lista != NULL) {
                        free(lista);
                        lista = NULL;
                    }
                    numAvversari = 0;
                    fread(&numAvversari, sizeof(int), 1, fp);
                    if (numAvversari > 0) {
                        lista = (RecordAvversario *)malloc(numAvversari * sizeof(RecordAvversario));
                        fread(lista, sizeof(RecordAvversario), numAvversari, fp);
                    }
                    fclose(fp);
                    schermata = 1;
                    pagina = 0;
                }
                // Se il file non esiste, non accade nulla (rimane su StatisticheMenu)
            } else if (areaCliccata(bStatMenu[1], riga, colonna)) {
                // [ESCI] - torna al menu principale
                esci = 1;
            }

        } else if (schermata == 1) {
            // ----- StatisticheLista -----
            stampaSchermataStatistiche(schermateStatistiche[1].data);

            // Stampa il nome del giocatore cercato (riga 9, centrato)
            int startCol = 41 - (int)strlen(nomeRicercato) / 2;
            goTo(startCol, 9);
            printf("%s", nomeRicercato);

            // Stampa gli avversari della pagina corrente (righe 12-16)
            int inizio = pagina * AVVERSARI_PER_PAGINA;
            int i = 0;
            while (i < AVVERSARI_PER_PAGINA && (inizio + i) < numAvversari) {
                int indice = inizio + i;
                goTo(7, 12 + i);
                printf("%-19s %10d %18d %18d",
                    lista[indice].nomeAvversario,
                    lista[indice].stats.numeroVittorie,
                    lista[indice].stats.numeroPareggi,
                    lista[indice].stats.numeroSconfitte);
                i = i + 1;
            }
            goTo(1, 25);
            fflush(stdout);

            int riga, colonna;
            if (!leggiClick(&riga, &colonna))
                continue;

            if (areaCliccata(bLista[0], riga, colonna)) {
                // [ESCI] - torna a StatisticheMenu
                schermata = 0;
            } else if (areaCliccata(bLista[1], riga, colonna)) {
                // [<--] - pagina precedente
                if (pagina > 0) {
                    pagina = pagina - 1;
                }
            } else if (areaCliccata(bLista[2], riga, colonna)) {
                // [-->] - pagina successiva
                if ((pagina + 1) * AVVERSARI_PER_PAGINA < numAvversari) {
                    pagina = pagina + 1;
                }
            }
        }
    }

    // Libera la memoria allocata
    if (lista != NULL) {
        free(lista);
    }

    // Ripristina il terminale
    abilitaTastiera();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#pragma endregion
