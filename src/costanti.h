#ifndef costanti_H
#define costanti_H

// costanti di dimensione necessarie a tempo di compilazione per definire array statici e strutture

#define DIMENSIONE_GRIGLIA 3
#define NUMERO_CELLE 9
#define LUNGHEZZA_STRINGA 20
#define LUNGHEZZA_PERCORSO 256
#define LUNGHEZZA_NOME_SUGGERIMENTO 30


// turni dei giocatori
static const int TURNO_GIOCATORE1 = 1;
static const int TURNO_GIOCATORE2 = 2;

// risultati finali della partita
static const int RISULTATO_PAREGGIO = 0;
static const int RISULTATO_VITTORIA_G1 = 1;
static const int RISULTATO_VITTORIA_G2 = 2;

// cella non valida / mossa non trovata
static const int CELLA_NON_VALIDA = -1;

// punteggi dell'algoritmo calcolaPunteggio (bot)
static const int PUNTEGGIO_VITTORIA = 10;
static const int PUNTEGGIO_SCONFITTA = -10;
static const int PUNTEGGIO_MINIMO = -100;
static const int PUNTEGGIO_MASSIMO = 100;

// modalità di gioco
static const int MODO_GIOCATORE = 0;
static const int MODO_CPU = 1;

// impostazioni default/modificate
static const int IMPOSTAZIONI_DEFAULT = 1;
static const int IMPOSTAZIONI_MODIFICATE = 0;

// pagine del menu impostazioni
static const int PAGINA_IMPOSTAZIONI_MAIN = 0;
static const int PAGINA_IMPOSTAZIONI_NOMI = 1;
static const int PAGINA_IMPOSTAZIONI_MODALITA = 2;
static const int PAGINA_IMPOSTAZIONI_CARICA = 3;
static const int PAGINA_IMPOSTAZIONI_SIMBOLI = 4;
static const int PAGINA_IMPOSTAZIONI_ANNULLA = 5;
static const int PAGINA_IMPOSTAZIONI_ROUND = 6;

// pagine del menu principale
static const int INDICE_MENU_PRINCIPALE = 0;

// schermate delle statistiche
static const int SCHERMATA_STAT_MENU = 0;
static const int SCHERMATA_STAT_LISTA = 1;

// coordinate di stampa statistiche
static const int COLONNA_CENTRO_SCHERMO = 41;
static const int RIGA_NOME_RICERCATO = 9;
static const int TABELLA_COL_INIZIO = 7;
static const int TABELLA_RIG_INIZIO = 12;

// esiti delle funzioni (successo / errore)
static const int ESITO_SUCCESSO = 1;
static const int ESITO_ERRORE = 0;

// pagine del supporto
static const int PAGINA_SUPPORTO_MAIN = 0;
static const int PAGINA_SUPPORTO_REGOLAMENTO = 1;
static const int PAGINA_SUPPORTO_MANUALE = 2;
static const int PAGINA_SUPPORTO_SUGGERIMENTI = 3;

// range di pagine dei suggerimenti
static const int PAGINA_SUGGERIMENTO_INIZIALE = 1;
static const int PAGINA_SUGGERIMENTO_FINALE = 5;

#endif
