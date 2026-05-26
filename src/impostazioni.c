/*
 ============================================================================
 Name        : impostazioni.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 1.1 Copyright   : Your copyright notice
 Description : file di gestione delle impostazioni di gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "impostazioni.h"
// libreria condivisa per mouse e cursore
#include "mouse.h"

void resetImpostazioni(Impostazioni *impostazioni);

// DEFINIZIONE FUNZIONI DI ACCESSO
#pragma region definizione funzioni di accesso
void Set_modoPartita(int m, Impostazioni *impostazioni);
int Get_modoPartita(Impostazioni impostazioni);
void Set_nomeGiocatore1(Stringa n1, Impostazioni *impostazioni);
Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
void Set_nomeGiocatore2(Stringa n2, Impostazioni *impostazioni);
Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
void Set_simboloGiocatore1(char s1, Impostazioni *impostazioni);
char Get_simboloGiocatore1(Impostazioni impostazioni);
void Set_simboloGiocatore2(char s2, Impostazioni *impostazioni);
char Get_simboloGiocatore2(Impostazioni impostazioni);
void Set_partitaPrecedente(Stringa p, Impostazioni *impostazioni);
Stringa Get_partitaPrecedente(Impostazioni impostazioni);
void Set_annullaImpostazioni(int x, Impostazioni *impostazioni);
int Get_annullaImpostazioni(Impostazioni impostazioni);
void Set_numeroRound(int r, Impostazioni *impostazioni);
int Get_numeroRound(Impostazioni impostazioni);
void Set_nomePartita(Stringa n, Impostazioni *impostazioni);
Stringa Get_nomePartita(Impostazioni impostazioni);
#pragma endregion

// DEFINIZIONE ALTRE FUNZIONI
#pragma region dichiarazione altre funzioni
void stampaSchermata(Stringa s);
#pragma endregion

// dichiarazioni funzioni navigazione
#pragma region input
void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]);
// goTo, leggiClick, abilitaMouse, abilitaTastiera, areaCliccata
// sono definite in mouse.h e non vanno ridichiarate
#pragma endregion

#pragma region main
// avvia il main per non entrare in conflitto con gli altri main dei file .c
// #ifndef IMPOSTAZIONI_NO_MAIN
int main() {
  // appena si avvia il codice si impostano le impostazioni di default.
  Impostazioni impostazioni;
  resetImpostazioni(&impostazioni);

  // vettore che carica i nomi delle schermate da visualizzare alla selezione
  Stringa schermate[7] = {{"Impostazioni"}, {"NomiGiocatori"}, {"ModalitaDiGioco"},  {"CaricaPartita"}, {"SimboliGiocatori"}, {"AnnullaImpostazioni"}, {"PartitaERound"}};
  stampaSchermata(schermate[0]);
  // avvia la navigazione con il mouse nelle schermate impostazioni
  navigaImpostazioni(&impostazioni, schermate);

  return EXIT_SUCCESS;
}
// #endif
#pragma endregion

// ------------------------------ FUNZIONI DI ACCESSO ------------------------------------
#pragma region funzioni di accesso
// ---------------------MODO PARTITA---------------------------
void Set_modoPartita(int m, Impostazioni *impostazioni) {
  impostazioni->modoPartita = m;
}
int Get_modoPartita(Impostazioni impostazioni) {
  return impostazioni.modoPartita;
}
// ---------------------NOMI GIOCATORI---------------------------
void Set_nomeGiocatore1(Stringa n1, Impostazioni *impostazioni) {
  strncpy(impostazioni->nomeGiocatore1.data, n1.data, sizeof(impostazioni->nomeGiocatore1.data) - 1);
  // la funzione copia una stringa di caratteri (n1) in un'altra stringa
  // (nomeGiocatore1) dando come limite la dimensione massima dell'array di
  // destinazione.
}
Stringa Get_nomeGiocatore1(Impostazioni impostazioni) {
  return impostazioni.nomeGiocatore1;
}
// ------------------------------------------------
void Set_nomeGiocatore2(Stringa n2, Impostazioni *impostazioni) {
  strncpy(impostazioni->nomeGiocatore2.data, n2.data,
          sizeof(impostazioni->nomeGiocatore2.data) - 1);
}
Stringa Get_nomeGiocatore2(Impostazioni impostazioni) {
  return impostazioni.nomeGiocatore2;
}
// --------------------SIMBOLI GIOCATORI----------------------------
void Set_simboloGiocatore1(char s1, Impostazioni *impostazioni) {
  impostazioni->simboloGiocatore1 = s1;
}
char Get_simboloGiocatore1(Impostazioni impostazioni) {
  return impostazioni.simboloGiocatore1;
}
// ------------------------------------------------
void Set_simboloGiocatore2(char s2, Impostazioni *impostazioni) {
  impostazioni->simboloGiocatore2 = s2;
}
char Get_simboloGiocatore2(Impostazioni impostazioni) {
  return impostazioni.simboloGiocatore2;
}
// ------------------PARTITA PRECEDENTE------------------------------
void Set_partitaPrecedente(Stringa p, Impostazioni *impostazioni) {
  strncpy(impostazioni->partitaPrecedente.data, p.data, sizeof(impostazioni->partitaPrecedente.data) - 1);
}
Stringa Get_partitaPrecedente(Impostazioni impostazioni) {
  return impostazioni.partitaPrecedente;
}
// ---------------------IMPOSTAZIONI DEFAULT---------------------------
void Set_annullaImpostazioni(int x, Impostazioni *impostazioni) {
  impostazioni->annullaImpostazioni = x;
  if (x == 1) {
    Set_nomeGiocatore1((Stringa){"giocatore1"}, impostazioni);
    Set_nomeGiocatore2((Stringa){"giocatore2"}, impostazioni);
    Set_modoPartita(1, impostazioni);
    Set_partitaPrecedente((Stringa){""}, impostazioni);
    Set_simboloGiocatore1('X', impostazioni);
    Set_simboloGiocatore2('O', impostazioni);
    Set_numeroRound(1, impostazioni);
    Set_nomePartita((Stringa){"partita"}, impostazioni);
  }
}
int Get_annullaImpostazioni(Impostazioni impostazioni) {
  return impostazioni.annullaImpostazioni;
}
// ---------------------ROUND DA GIOCARE---------------------------
void Set_numeroRound(int r, Impostazioni *impostazioni) {
  if(r>MAX_ROUND){
    impostazioni->numeroRound = MAX_ROUND;
  }else{
    impostazioni->numeroRound = r;
  }
  
}
int Get_numeroRound(Impostazioni impostazioni) {
  return impostazioni.numeroRound;
}
// ---------------------NOME PARTITA---------------------------
void Set_nomePartita(Stringa n, Impostazioni *impostazioni) {
  strncpy(impostazioni->nomePartita.data, n.data, sizeof(impostazioni->nomePartita.data) - 1);
}
Stringa Get_nomePartita(Impostazioni impostazioni) {
  return impostazioni.nomePartita;
}
#pragma endregion

// ALTRE FUNZIONI
#pragma region altre funzioni

// ---------------------RESET DELLE IMPOSTAZIONI---------------------------
// dichiarata prima per poter resettare le impostazioni all'avvio

void resetImpostazioni(Impostazioni *impostazioni) {
  Set_nomeGiocatore1((Stringa){"giocatore1"}, impostazioni);
  Set_nomeGiocatore2((Stringa){"giocatore2"}, impostazioni);
  Set_modoPartita(1, impostazioni);
  Set_partitaPrecedente((Stringa){""}, impostazioni);
  Set_simboloGiocatore1('X', impostazioni);
  Set_simboloGiocatore2('O', impostazioni);
  Set_annullaImpostazioni(1, impostazioni);
  Set_numeroRound(1, impostazioni);
  Set_nomePartita((Stringa){"partita"}, impostazioni);
}

void stampaSchermata(Stringa s) {
  FILE *fpImpostazioni;
  int c;
  char nomeCompleto[256];

  // apertura del file in lettura per caricare la schermata di impostazioni
  sprintf(nomeCompleto, PERCORSO_FILE, s.data);
  fpImpostazioni = fopen(nomeCompleto, "r");
  if (fpImpostazioni == NULL) {
    printf("Errore Caricamento Schermata\n");
  } else {
    // finchè non raggiunge la fine del file legge i caratteri man mano e li stampa a schermo
    while ((c = fgetc(fpImpostazioni)) != EOF) {
      putchar(c);
    }
    fclose(fpImpostazioni);
    printf("\n");
  }
}

#pragma endregion

// FUNZIONI CURSORE E NAVIGAZIONE
#pragma region funzioni cursore
// goTo, leggiClick, abilitaMouse, abilitaTastiera, areaCliccata
// sono definite come static inline in mouse.h
// ---------------------NAVIGAZIONE IMPOSTAZIONI---------------------------
// loop principale: stampa schermata, leggi click, esegui azione
void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]) {
  int riga, colonna, pagina = 0, esci = 0;

  // rende il terminale cliccabile
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
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    stampaSchermata(schermate[pagina]);
    // gestione dei dati nelle schermate stampate
    switch (pagina){
      case 1:
        goTo(bNomi[0].c1+1, bNomi[0].r);
        printf("%s]", Get_nomeGiocatore1(*impostazioni).data);
        goTo(bNomi[1].c1+1, bNomi[1].r);
        printf("%s]", Get_nomeGiocatore2(*impostazioni).data);
        fflush(stdout);
        break;
      case 3:
        goTo(bCarica[0].c1+1, bCarica[0].r);
        printf("%s]", Get_partitaPrecedente(*impostazioni).data);
        fflush(stdout);
        break;
      case 4:
        goTo(bSimb[0].c1+1, bSimb[0].r);
        printf("%c", Get_simboloGiocatore1(*impostazioni));
        goTo(bSimb[1].c1+1, bSimb[1].r);
        printf("%c", Get_simboloGiocatore2(*impostazioni));
        fflush(stdout);
      case 6:
        goTo(bRound[0].c1+1, bRound[0].r);
        printf("%s]", Get_nomePartita(*impostazioni).data);
        goTo(bRound[1].c1+1, bRound[1].r);
        printf("%d]", Get_numeroRound(*impostazioni));
        fflush(stdout);
    }

    // gestione del click nelle pagine
    if (!leggiClick(&riga, &colonna))
      continue;

    switch (pagina) {
    case 0: // --------- Impostazioni ---------
      if (areaCliccata(bMenu[0], riga, colonna))
        pagina = 1;
      else if (areaCliccata(bMenu[1], riga, colonna))
        pagina = 2;
      else if (areaCliccata(bMenu[2], riga, colonna))
        pagina = 3;
      else if (areaCliccata(bMenu[3], riga, colonna))
        pagina = 4;
      else if (areaCliccata(bMenu[4], riga, colonna))
        pagina = 5;
      else if (areaCliccata(bMenu[5], riga, colonna))
        pagina = 6;
      else if (areaCliccata(bMenu[6], riga, colonna))
        esci = 1;
      break;

    case 1: // --------- NomiGiocatori ---------
      if (areaCliccata(bNomi[0], riga, colonna)) {
        Stringa nuovoNome1;
        goTo(bNomi[0].c1+1, bNomi[0].r);
        abilitaTastiera();
        scanf("%19s", nuovoNome1.data);
        abilitaMouse();
        Set_nomeGiocatore1(nuovoNome1, impostazioni);
      } else if (areaCliccata(bNomi[1], riga, colonna)) {
        Stringa nuovoNome2;
        goTo(bNomi[1].c1+1, bNomi[1].r);
        abilitaTastiera();
        scanf("%19s", nuovoNome2.data);
        abilitaMouse();
        Set_nomeGiocatore2(nuovoNome2, impostazioni);
      } else if (areaCliccata(bNomi[2], riga, colonna)) {
        pagina = 0;
      }
      break;

    case 2: // --------- ModalitaDiGioco ---------
      if (areaCliccata(bModo[0], riga, colonna)) {
        Set_modoPartita(0, impostazioni);
        pagina = 0;
      } else if (areaCliccata(bModo[1], riga, colonna)) {
        Set_modoPartita(1, impostazioni);
        pagina = 0;
      } else if (areaCliccata(bModo[2], riga, colonna)) {
        pagina = 0;
      }
      break;

    case 3: // --------- CaricaPartita ---------
      if (areaCliccata(bCarica[0], riga, colonna)) {
        Stringa vecchiaPartita;
        goTo(bCarica[0].c1+1, bCarica[0].r);
        abilitaTastiera();
        scanf("%s", vecchiaPartita.data);
        abilitaMouse();
        Set_partitaPrecedente(vecchiaPartita, impostazioni);
      } else if (areaCliccata(bCarica[1], riga, colonna)) {
        pagina = 0;
      }
      break;

    case 4: // --------- SimboliGiocatori ---------
      if (areaCliccata(bSimb[0], riga, colonna)) {
        char simboloNuovo1;
        goTo(bSimb[0].c1+1, bSimb[0].r);
        abilitaTastiera();
        scanf("%c", &simboloNuovo1);
        abilitaMouse();
        Set_simboloGiocatore1(simboloNuovo1, impostazioni);
      } else if (areaCliccata(bSimb[1], riga, colonna)) {
        char simboloNuovo2;
        goTo(bSimb[1].c1+1, bSimb[1].r);
        abilitaTastiera();
        scanf("%c", &simboloNuovo2);
        abilitaMouse();
        Set_simboloGiocatore2(simboloNuovo2, impostazioni);
      } else if (areaCliccata(bSimb[2], riga, colonna)) {
        pagina = 0;
      }
      break;

    case 5: // --------- AnnullaImpostazioni ---------
      if (areaCliccata(bAnnulla[0], riga, colonna)) {
        resetImpostazioni(impostazioni);
        pagina = 0;
      } else if (areaCliccata(bAnnulla[1], riga, colonna)) {
        pagina = 0;
      }
      break;

    case 6: // --------- PartitaERound ---------
      if (areaCliccata(bRound[0], riga, colonna)) {
        Stringa nuovaPartita;
        goTo(bRound[0].c1+1, bRound[0].r);
        abilitaTastiera();
        scanf("%19s", nuovaPartita.data);
        abilitaMouse();
        Set_nomePartita(nuovaPartita, impostazioni);
      } else if (areaCliccata(bRound[1], riga, colonna)) {
        Stringa nuovoRound;
        goTo(bRound[1].c1+1, bRound[1].r);
        abilitaTastiera();
        scanf("%3s", nuovoRound.data);
        abilitaMouse();
        Set_numeroRound(atoi(nuovoRound.data), impostazioni);
      } else if (areaCliccata(bRound[2], riga, colonna)) {
        pagina = 0;
      }
      break;
    }
  }

  // ripristina il terminale
#ifdef _WIN32
  SetConsoleMode(handleInput, modalitaPrecedente);
  system("cls");
#else
  printf("\033[?1000l\033[?1006l");
  fflush(stdout);
  tcsetattr(STDIN_FILENO, TCSANOW, &originale);
  system("clear");
#endif
  printf("Impostazioni chiuse.\n");
}
#pragma endregion