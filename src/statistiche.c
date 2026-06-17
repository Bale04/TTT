/*
 ============================================================================
 Name        : statistiche.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : file di gestione di salvataggio e recupero delle statistiche di gioco per giocatore
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statistiche.h"
#include "mouse.h"

// --------------------- FUNZIONI DI ACCESSO ---------------------
#pragma region funzioni di accesso

// ---------------------STATISTICHE---------------------------
int Get_vittorie(Statistiche s) { 
  return s.numeroVittorie; 
}
void Set_vittorie(Statistiche *s, int v) {
  s->numeroVittorie = v; 
}
int Get_sconfitte(Statistiche s) {
  return s.numeroSconfitte; 
}
void Set_sconfitte(Statistiche *s, int v) {
  s->numeroSconfitte = v; 
}
int Get_pareggi(Statistiche s) {
  return s.numeroPareggi; 
}
void Set_pareggi(Statistiche *s, int v) {
  s->numeroPareggi = v; 
}

// ---------------------RECORD AVVERSARIO---------------------------
const char *Get_nomeAvversario(const RecordAvversario *r) { 
  return r->nomeAvversario; 
}
void Set_nomeAvversario(RecordAvversario *r, const char *nome) {
  strncpy(r->nomeAvversario, nome, LUNGHEZZA_STRINGA - 1);
  r->nomeAvversario[LUNGHEZZA_STRINGA - 1] = '\0';
}

#pragma endregion

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
static void aggiornaFileGiocatore(const char *nomeGiocatore, const char *nomeAvversario, int tipo){
    char percorso[256];
    RecordAvversario *lista;
    int numAvversari;
    int trovato;
    FILE *fp;
    int i;
    RecordAvversario recordVuoto;

    sprintf(percorso, PERCORSO_STATS_SALVATE, nomeGiocatore);

    lista = NULL;
    numAvversari = 0;
    trovato = 0;

    // Prova a caricare il file esistente
    fp = fopen(percorso, "rb");
    if (fp != NULL){
        fread(&numAvversari, sizeof(int), 1, fp);
        if (numAvversari > 0){
            lista = (RecordAvversario *)malloc(numAvversari * sizeof(RecordAvversario));
            fread(lista, sizeof(RecordAvversario), numAvversari, fp);
        }
        fclose(fp);
    }

    // Cerca il record dell'avversario nella lista
    i = 0;
    while (i < numAvversari){
        if (strcmp(Get_nomeAvversario(&lista[i]), nomeAvversario) == 0){
      trovato = 1;
      if (tipo == RISULTATO_VITTORIA_G1) {
        Set_vittorie(&lista[i].stats, Get_vittorie(lista[i].stats) + 1);
      } else if (tipo == RISULTATO_VITTORIA_G2) {
        Set_sconfitte(&lista[i].stats, Get_sconfitte(lista[i].stats) + 1);
      } else {
        Set_pareggi(&lista[i].stats, Get_pareggi(lista[i].stats) + 1);
      }
      break;
    }
    i = i + 1;
  }

    if (!trovato){
        numAvversari = numAvversari + 1;
        lista = (RecordAvversario *)realloc(lista, numAvversari * sizeof(RecordAvversario));
        recordVuoto.stats.numeroVittorie = 0;
        recordVuoto.stats.numeroSconfitte = 0;
        recordVuoto.stats.numeroPareggi = 0;
        lista[numAvversari - 1] = recordVuoto;
        Set_nomeAvversario(&lista[numAvversari - 1], nomeAvversario);
        if (tipo == RISULTATO_VITTORIA_G1){
            Set_vittorie(&lista[numAvversari - 1].stats, 1);
        }else if (tipo == RISULTATO_VITTORIA_G2){
            Set_sconfitte(&lista[numAvversari - 1].stats, 1);
        }else{
            Set_pareggi(&lista[numAvversari - 1].stats, 1);
        }
    }

    // Salva il file aggiornato
    fp = fopen(percorso, "wb");
    if (fp != NULL){
        fwrite(&numAvversari, sizeof(int), 1, fp);
        fwrite(lista, sizeof(RecordAvversario), numAvversari, fp);
        fclose(fp);
    }

    if (lista != NULL){
        free(lista);
    }
}

// Salva le statistiche della partita per entrambi i giocatori
// risultato: 1 = vittoria G1, 2 = vittoria G2, 0 = pareggio
void salvaStatistichePartita(const char *nomeG1, const char *nomeG2, int risultato) {
  if (risultato == RISULTATO_VITTORIA_G1) {
    // G1 vittoria vs G2
    aggiornaFileGiocatore(nomeG1, nomeG2, RISULTATO_VITTORIA_G1);
    // G2 sconfitta vs G1
    aggiornaFileGiocatore(nomeG2, nomeG1, RISULTATO_VITTORIA_G2);
  } else if (risultato == RISULTATO_VITTORIA_G2) {
    // G1 sconfitta vs G2
    aggiornaFileGiocatore(nomeG1, nomeG2, RISULTATO_VITTORIA_G2);
    // G2 vittoria vs G1
    aggiornaFileGiocatore(nomeG2, nomeG1, RISULTATO_VITTORIA_G1);
  } else {
    // pareggio per entrambi
    aggiornaFileGiocatore(nomeG1, nomeG2, RISULTATO_PAREGGIO);
    aggiornaFileGiocatore(nomeG2, nomeG1, RISULTATO_PAREGGIO);
  }
}

#pragma endregion

// --------------------- NAVIGAZIONE STATISTICHE ---------------------
#pragma region navigazione

void navigaStatistiche(void){
    int esci;
    int schermata;
    int pagina;
    int numAvversari;
    int riga;
    int colonna;
    int inizio;
    int i;
    char percorso[256];
    char nomeRicercato[LUNGHEZZA_STRINGA];
    RecordAvversario *lista;
    FILE *fp;

    esci = 0;
    schermata = SCHERMATA_STAT_MENU;
    pagina = 0;
    lista = NULL;
    numAvversari = 0;
    memset(nomeRicercato, 0, sizeof(nomeRicercato));

    abilitaMouse();

    while (!esci){
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        if (schermata == SCHERMATA_STAT_MENU){
            // ----- StatisticheMenu -----
            stampaSchermataStatistiche(schermateStatistiche[SCHERMATA_STAT_MENU].data);
            goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
            fflush(stdout);

            if (!leggiClick(&riga, &colonna)){
                continue;
            }

            if (areaCliccata(bStatMenu[0], riga, colonna)){
                // [RICERCA] - input nome giocatore
                goTo(bStatMenu[0].c1 + 1, bStatMenu[0].r);
                abilitaTastiera();
                scanf("%19s", nomeRicercato);
                abilitaMouse();

                // Cerca il file del giocatore nella cartella StatisticheSalvate
                sprintf(percorso, PERCORSO_STATS_SALVATE, nomeRicercato);
                fp = fopen(percorso, "rb");
                if (fp != NULL){
                    // File trovato: carica i dati
                    if (lista != NULL){
                        free(lista);
                        lista = NULL;
                    }
                    numAvversari = 0;
                    fread(&numAvversari, sizeof(int), 1, fp);
                    if (numAvversari > 0){
                        lista = (RecordAvversario *)malloc(numAvversari * sizeof(RecordAvversario));
                        fread(lista, sizeof(RecordAvversario), numAvversari, fp);
                    }
                    fclose(fp);
                    schermata = SCHERMATA_STAT_LISTA;
                    pagina = 0;
                }
                // Se il file non esiste, non accade nulla (rimane su StatisticheMenu)
            }else if (areaCliccata(bStatMenu[1], riga, colonna)){
                // [ESCI] - torna al menu principale
                esci = 1;
            }
        }else if (schermata == SCHERMATA_STAT_LISTA){
            // ----- StatisticheLista -----
            stampaSchermataStatistiche(schermateStatistiche[SCHERMATA_STAT_LISTA].data);

            // Stampa il nome del giocatore cercato (riga 9, centrato)
            inizio = COLONNA_CENTRO_SCHERMO - (int)strlen(nomeRicercato) / 2;
            goTo(inizio, RIGA_NOME_RICERCATO);
            printf("%s", nomeRicercato);

            // Stampa gli avversari della pagina corrente (righe 12-16)
            inizio = pagina * AVVERSARI_PER_PAGINA;
            i = 0;
            while (i < AVVERSARI_PER_PAGINA && (inizio + i) < numAvversari){
                // Stampa il nome dell'avversario
                goTo(TABELLA_COL_INIZIO, TABELLA_RIG_INIZIO + i);
                printf("%s", Get_nomeAvversario(&lista[inizio + i]));

                // Stampa il numero di vittorie a colonna 31
                goTo(31, TABELLA_RIG_INIZIO + i);
                printf("%d", Get_vittorie(lista[inizio + i].stats));

                // Stampa i pareggi a colonna 50
                goTo(50, TABELLA_RIG_INIZIO + i);
                printf("%d", Get_pareggi(lista[inizio + i].stats));

                // Stampa le sconfitte a colonna 69
                goTo(69, TABELLA_RIG_INIZIO + i);
                printf("%d", Get_sconfitte(lista[inizio + i].stats));

                i = i + 1;
            }
            goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
            fflush(stdout);

            if (!leggiClick(&riga, &colonna)){
                continue;
            }

            if (areaCliccata(bLista[0], riga, colonna)){
                // [ESCI] - torna a StatisticheMenu
                schermata = SCHERMATA_STAT_MENU;
            }else if (areaCliccata(bLista[1], riga, colonna)){
                // [<--] - pagina precedente
                if (pagina > 0){
                    pagina = pagina - 1;
                }
            }else if (areaCliccata(bLista[2], riga, colonna)){
                // [-->] - pagina successiva
                if ((pagina + 1) * AVVERSARI_PER_PAGINA < numAvversari){
                    pagina = pagina + 1;
                }
            }
        }
    }

    // Libera la memoria allocata
    if (lista != NULL)
    {
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
