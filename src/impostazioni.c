/*
 ============================================================================
 Name        : impostazioni.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia,
 Ruggiero Dicorato Version     : V 0.4 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "impostazioni.h"
// gestione del mouse
#include <termios.h>
#include <unistd.h>

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
void resetImpostazioni(Impostazioni *impostazioni);
void stampaSchermata(Stringa s);
void modificaNomi(Impostazioni impostazioni);
#pragma endregion

#pragma region input
// dichiarazioni funzioni cursore
int leggiClick(int *r, int *c);
void inputTastiera(const char *prompt, char *buf, int maxLen);
void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]);
#pragma endregion

#pragma region main
int main() {
  // appena si avvia il codice si impostano le impostazioni di default.
  Impostazioni impostazioni;
  resetImpostazioni(&impostazioni);

  // vettore che carica i nomi delle schermate da visualizzare alla selezione
  Stringa schermate[7] = {{"Impostazioni"},     {"NomiGiocatori"},
                          {"ModalitaDiGioco"},  {"CaricaPartita"},
                          {"SimboliGiocatori"}, {"AnnullaImpostazioni"},
                          {"PartitaERound"}};
  // avvia la navigazione con il mouse nelle schermate impostazioni
  navigaImpostazioni(&impostazioni, schermate);

  return EXIT_SUCCESS;
}
#pragma endregion

// FUNZIONI DI ACCESSO
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
  strncpy(impostazioni->nomeGiocatore1.data, n1.data,
          sizeof(impostazioni->nomeGiocatore1.data) - 1);
  // la funzione copia una stringa di caratteri (n1) in un'altra stringa (nomeGiocatore1) dando come limite la dimensione massima dell'array di destinazione.
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
  strncpy(impostazioni->nomeGiocatore2.data, p.data,
          sizeof(impostazioni->nomeGiocatore2.data) - 1);
}
Stringa Get_partitaPrecedente(Impostazioni impostazioni) {
  return impostazioni.partitaPrecedente;
}
// ---------------------IMPOSTAZIONI DEFAULT---------------------------
void Set_annullaImpostazioni(int x, Impostazioni *impostazioni) {
  impostazioni->annullaImpostazioni = x;
  if (x == 1) {
    impostazioni->modoPartita = 1;
    strncpy(impostazioni->nomeGiocatore1.data, "giocatore1",
            sizeof(impostazioni->nomeGiocatore1.data) - 1);
    impostazioni->simboloGiocatore1 = 'X';
    strncpy(impostazioni->nomeGiocatore2.data, "giocatore2",
            sizeof(impostazioni->nomeGiocatore2.data) - 1);
    impostazioni->simboloGiocatore2 = 'O';
    strncpy(impostazioni->partitaPrecedente.data, "",
            sizeof(impostazioni->partitaPrecedente.data) - 1);
    impostazioni->numeroRound = 1;
    strncpy(impostazioni->nomePartita.data, "partita",
            sizeof(impostazioni->nomePartita.data) - 1);
  }
}
int Get_annullaImpostazioni(Impostazioni impostazioni) {
  return impostazioni.annullaImpostazioni;
}
// ---------------------ROUND DA GIOCARE---------------------------
void Set_numeroRound(int r, Impostazioni *impostazioni) {
  impostazioni->numeroRound = r;
}
int Get_numeroRound(Impostazioni impostazioni) {
  return impostazioni.numeroRound;
}
// ---------------------NOME PARTITA---------------------------
void Set_nomePartita(Stringa n, Impostazioni *impostazioni) {
  strncpy(impostazioni->nomePartita.data, n.data,
          sizeof(impostazioni->nomePartita.data) - 1);
}
Stringa Get_nomePartita(Impostazioni impostazioni) {
  return impostazioni.nomePartita;
}
#pragma endregion

// ALTRE FUNZIONI
#pragma region altre funzioni
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

  // serve per unire il nome dell'impostazione da passare aggiungendo
  // l'estensione .txt
  sprintf(nomeCompleto, "/home/Bale/GitHub/TTT/Interfacce/%s.txt", s.data);
  // apre il file in lettura per caricare la schermata di impostazioni
  fpImpostazioni = fopen(nomeCompleto, "r");
  if (fpImpostazioni == NULL) {
    printf("Errore Caricamento Schermata\n");
  } else {
    // finchè non raggiunge la fine del file legge i caratteri man mano e li
    // stampa a schermo
    while ((c = fgetc(fpImpostazioni)) != EOF) {
      putchar(c);
    }
    fclose(fpImpostazioni);
    printf("\n");
  }
}

// funzione di modifica del nome dei giocatori
void modificaNomi(Impostazioni impostazioni) {
  Stringa nome1, nome2;
  printf("Inserisci il nome del giocatore 1: ");
  scanf("%s", nome1.data);
  Set_nomeGiocatore1(nome1, &impostazioni);
  printf("Inserisci il nome del giocatore 2: ");
  scanf("%s", nome2.data);
  Set_nomeGiocatore2(nome2, &impostazioni);
}

#pragma endregion

// FUNZIONI CURSORE E NAVIGAZIONE
#pragma region funzioni cursore
// ---------------------LETTURA CLICK MOUSE---------------------------
// legge le coordinate di un click sinistro del mouse (formato SGR)
// restituisce 1 se click valido, 0 altrimenti
int leggiClick(int *r, int *c) {
  char ch;
  while (1) {
    if (read(STDIN_FILENO, &ch, 1) != 1)
      return 0;
    if (ch == '\033') {
      char seq[32];
      int i = 0;
      if (read(STDIN_FILENO, &seq[i], 1) != 1 || seq[i] != '[')
        continue;
      i++;
      if (read(STDIN_FILENO, &seq[i], 1) != 1 || seq[i] != '<')
        continue;
      i++;
      while (i < 30) {
        if (read(STDIN_FILENO, &seq[i], 1) != 1)
          break;
        if (seq[i] == 'M' || seq[i] == 'm') {
          seq[i + 1] = '\0';
          break;
        }
        i++;
      }
      if (seq[i] == 'M') {
        int btn, col, row;
        if (sscanf(seq + 2, "%d;%d;%d", &btn, &col, &row) == 3 && btn == 0) {
          *r = row;
          *c = col;
          return 1;
        }
      }
    }
  }
}
// ---------------------INPUT DA TASTIERA---------------------------
// disabilita mouse, abilita echo, legge stringa, poi ripristina raw mode
void inputTastiera(const char *prompt, char *buf, int maxLen) {
  struct termios att, norm;
  tcgetattr(STDIN_FILENO, &att);
  norm = att;
  norm.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &norm);
  printf("\033[?1006l\033[?1000l"); // disabilita mouse
  printf("\033[25;1H\033[K%s", prompt);
  fflush(stdout);
  if (fgets(buf, maxLen, stdin) != NULL)
    buf[strcspn(buf, "\n")] = '\0';
  tcsetattr(STDIN_FILENO, TCSANOW, &att);
  printf("\033[?1000h\033[?1006h"); // riabilita mouse
  fflush(stdout);
}
// ---------------------CERCA BOTTONE---------------------------
// controlla se il click (r,c) cade su uno dei bottoni, restituisce il codice
int cercaBottone(AreaCliccabile b[], int n, int r, int c) {
  for (int i = 0; i < n; i++)
    if (r == b[i].r && c >= b[i].c1 && c <= b[i].c2)
      return b[i].v;
  return 0;
}
// ---------------------NAVIGAZIONE IMPOSTAZIONI---------------------------
// loop principale: stampa schermata, leggi click, esegui azione
void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]) {
  struct termios orig;
  int r, c, az, pagina = 0, esci = 0;

  // bottoni per ogni schermata
  AreaCliccabile bMenu[] = {{9, 26, 51, 1},  {11, 27, 49, 2}, {13, 30, 45, 3},
                     {15, 28, 47, 4}, {17, 26, 49, 5}, {19, 26, 50, 6},
                     {20, 65, 70, 99}};
  AreaCliccabile bNomi[] = {{12, 31, 44, 11}, {16, 31, 44, 12}, {18, 38, 44, 99}};
  AreaCliccabile bModo[] = {{13, 19, 27, 21}, {13, 49, 53, 22}, {16, 38, 44, 99}};
  AreaCliccabile bCarica[] = {{12, 40, 42, 31}, {14, 38, 44, 99}};
  AreaCliccabile bSimb[] = {{12, 39, 42, 41}, {16, 39, 42, 42}, {18, 38, 44, 99}};
  AreaCliccabile bAnnulla[] = {{13, 29, 33, 51}, {13, 49, 52, 52}};
  AreaCliccabile bRound[] = {{12, 37, 46, 61}, {16, 40, 43, 62}, {18, 38, 44, 99}};

  // rende il terminale cliccabile
  struct termios raw;
  tcgetattr(STDIN_FILENO, &orig);
  raw = orig;
  raw.c_lflag &= ~(ICANON | ECHO);
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
  printf("\033[?1000h\033[?1006h");
  fflush(stdout);

  while (!esci) {
    system("clear");
    stampaSchermata(schermate[pagina]);
    if (!leggiClick(&r, &c))
      continue;

    // DEBUG: coordinate del click
    printf("\033[26;1H\033[KDEBUG -> riga: %d, colonna: %d", r, c);
    fflush(stdout);

    switch (pagina) {
    case 0: // --------- Impostazioni ---------
      az = cercaBottone(bMenu, 7, r, c);
      if (az >= 1 && az <= 6)
        pagina = az;
      else if (az == 99)
        esci = 1;
      break;

    case 1: // --------- NomiGiocatori ---------
      az = cercaBottone(bNomi, 3, r, c);
      if (az == 11) {
        char buf[20];
        inputTastiera("Inserisci nome Giocatore 1: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_nomeGiocatore1(nome, impostazioni);
        }
      } else if (az == 12) {
        char buf[20];
        inputTastiera("Inserisci nome Giocatore 2: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_nomeGiocatore2(nome, impostazioni);
        }
      } else if (az == 99)
        pagina = 0;
      break;

    case 2: // --------- ModalitaDiGioco ---------
      az = cercaBottone(bModo, 3, r, c);
      if (az == 21){
        Set_modoPartita(0, impostazioni);
		printf("MODALIÀ PERSONA\n");
		pagina = 0;
	  }else if (az == 22){
        Set_modoPartita(1, impostazioni);
		printf("MODALIÀ CPU\n");
		pagina = 0;
	  }
      if (az == 99){
        pagina = 0;
	  }
      break;

    case 3: // --------- CaricaPartita ---------
      az = cercaBottone(bCarica, 2, r, c);
      if (az == 31) {
        char buf[20];
        inputTastiera("Nome partita da caricare: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_partitaPrecedente(nome, impostazioni);
        }
        pagina = 0;
      }
      if (az == 99)
        pagina = 0;
      break;

    case 4: // --------- SimboliGiocatori ---------
      az = cercaBottone(bSimb, 3, r, c);
      if (az == 41) {
        char buf[4];
        inputTastiera("Simbolo Giocatore 1 (1 carattere): ", buf, 4);
        if (buf[0] != '\0')
          Set_simboloGiocatore1(buf[0], impostazioni);
        pagina = 0;
      } else if (az == 42) {
        char buf[4];
        inputTastiera("Simbolo Giocatore 2 (1 carattere): ", buf, 4);
        if (buf[0] != '\0')
          Set_simboloGiocatore2(buf[0], impostazioni);
        pagina = 0;
      } else if (az == 99)
        pagina = 0;
      break;

    case 5: // --------- AnnullaImpostazioni ---------
      az = cercaBottone(bAnnulla, 2, r, c);
      if (az == 51) {
        resetImpostazioni(impostazioni);
        pagina = 0;
      } else if (az == 52)
        pagina = 0;
      break;

    case 6: // --------- PartitaERound ---------
      az = cercaBottone(bRound, 3, r, c);
      if (az == 61) {
        char buf[20];
        inputTastiera("Nome partita: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_nomePartita(nome, impostazioni);
        }
        pagina = 0;
      } else if (az == 62) {
        char buf[4];
        inputTastiera("Numero round: ", buf, 4);
        if (buf[0] != '\0')
          Set_numeroRound(atoi(buf), impostazioni);
        pagina = 0;
      }
      if (az == 99)
        pagina = 0;
      break;
    }
  }

  // ripristina il terminale
  printf("\033[?1006l\033[?1000l");
  fflush(stdout);
  tcsetattr(STDIN_FILENO, TCSANOW, &orig);
  system("clear");
  printf("Impostazioni chiuse.\n");
}
#pragma endregion