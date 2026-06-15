#ifndef costanti_H
#define costanti_H

// costanti di dimensione necessarie a tempo di compilazione per definire array statici e strutture

const int  DIMENSIONE_GRIGLIA = 3;
const int  NUMERO_CELLE = 9;
const int  LUNGHEZZA_STRINGA = 20;
const int  LUNGHEZZA_PERCORSO = 256;
const int  LUNGHEZZA_NOME_SUGGERIMENTO = 30;


// turni dei giocatori
const int TURNO_GIOCATORE1 = 1;
const int TURNO_GIOCATORE2 = 2;

// risultati finali della partita
const int RISULTATO_PAREGGIO = 0;
const int RISULTATO_VITTORIA_G1 = 1;
const int RISULTATO_VITTORIA_G2 = 2;

// cella non valida / mossa non trovata
const int CELLA_NON_VALIDA = -1;

// punteggi dell'algoritmo calcolaPunteggio (bot)
const int PUNTEGGIO_VITTORIA = 10;
const int PUNTEGGIO_SCONFITTA = -10;
const int PUNTEGGIO_MINIMO = -100;
const int PUNTEGGIO_MASSIMO = 100;

// modalità di gioco
const int MODO_GIOCATORE = 0;
const int MODO_CPU = 1;

// impostazioni default/modificate
const int IMPOSTAZIONI_DEFAULT = 1;
const int IMPOSTAZIONI_MODIFICATE = 0;

// pagine del menu impostazioni
const int PAGINA_IMPOSTAZIONI_MAIN = 0;
const int PAGINA_IMPOSTAZIONI_NOMI = 1;
const int PAGINA_IMPOSTAZIONI_MODALITA = 2;
const int PAGINA_IMPOSTAZIONI_CARICA = 3;
const int PAGINA_IMPOSTAZIONI_SIMBOLI = 4;
const int PAGINA_IMPOSTAZIONI_ANNULLA = 5;
const int PAGINA_IMPOSTAZIONI_ROUND = 6;

// pagine del menu principale
const int INDICE_MENU_PRINCIPALE = 0;

// schermate delle statistiche
const int SCHERMATA_STAT_MENU = 0;
const int SCHERMATA_STAT_LISTA = 1;

// coordinate di stampa statistiche
const int COLONNA_CENTRO_SCHERMO = 41;
const int RIGA_NOME_RICERCATO = 9;
const int TABELLA_COL_INIZIO = 7;
const int TABELLA_RIG_INIZIO = 12;

// esiti delle funzioni (successo / errore)
const int ESITO_SUCCESSO = 1;
const int ESITO_ERRORE = 0;

// pagine del supporto
const int PAGINA_SUPPORTO_MAIN = 0;
const int PAGINA_SUPPORTO_REGOLAMENTO = 1;
const int PAGINA_SUPPORTO_MANUALE = 2;
const int PAGINA_SUPPORTO_SUGGERIMENTI = 3;

// range di pagine dei suggerimenti
const int PAGINA_SUGGERIMENTO_INIZIALE = 1;
const int PAGINA_SUGGERIMENTO_FINALE = 5;

#endif
