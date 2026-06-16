#ifndef costanti_H
#define costanti_H

// costanti di dimensione necessarie a tempo di compilazione per definire array statici e strutture

#define DIMENSIONE_GRIGLIA 3
#define NUMERO_CELLE 9
#define LUNGHEZZA_STRINGA 20
#define LUNGHEZZA_PERCORSO 256
#define LUNGHEZZA_NOME_SUGGERIMENTO 30


// turni dei giocatori
#define TURNO_GIOCATORE1 1
#define TURNO_GIOCATORE2 2

// risultati finali della partita
#define RISULTATO_PAREGGIO 0
#define RISULTATO_VITTORIA_G1 1
#define RISULTATO_VITTORIA_G2 2

// cella non valida / mossa non trovata
#define CELLA_NON_VALIDA -1

// punteggi dell'algoritmo calcolaPunteggio (bot)
#define PUNTEGGIO_VITTORIA 10
#define PUNTEGGIO_SCONFITTA -10
#define PUNTEGGIO_MINIMO -100
#define PUNTEGGIO_MASSIMO 100

// modalità di gioco
#define MODO_GIOCATORE 0
#define MODO_CPU 1

// impostazioni default/modificate
#define IMPOSTAZIONI_DEFAULT 1
#define IMPOSTAZIONI_MODIFICATE 0

// pagine del menu impostazioni
#define PAGINA_IMPOSTAZIONI_MAIN 0
#define PAGINA_IMPOSTAZIONI_NOMI 1
#define PAGINA_IMPOSTAZIONI_MODALITA 2
#define PAGINA_IMPOSTAZIONI_CARICA 3
#define PAGINA_IMPOSTAZIONI_SIMBOLI 4
#define PAGINA_IMPOSTAZIONI_ANNULLA 5
#define PAGINA_IMPOSTAZIONI_ROUND 6

// pagine del menu principale
#define INDICE_MENU_PRINCIPALE 0

// schermate delle statistiche
#define SCHERMATA_STAT_MENU 0
#define SCHERMATA_STAT_LISTA 1

// coordinate di stampa statistiche
#define COLONNA_CENTRO_SCHERMO 41
#define RIGA_NOME_RICERCATO 9
#define TABELLA_COL_INIZIO 7
#define TABELLA_RIG_INIZIO 12

// esiti delle funzioni (successo / errore)
#define ESITO_SUCCESSO 1
#define ESITO_ERRORE 0

// pagine del supporto
#define PAGINA_SUPPORTO_MAIN 0
#define PAGINA_SUPPORTO_REGOLAMENTO 1
#define PAGINA_SUPPORTO_MANUALE 2
#define PAGINA_SUPPORTO_SUGGERIMENTI 3

// range di pagine dei suggerimenti
#define PAGINA_SUGGERIMENTO_INIZIALE 1
#define PAGINA_SUGGERIMENTO_FINALE 5

#endif
