/*
 ============================================================================
 Name        : impostazioni.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia,
 Ruggiero Dicorato Version     : V 1.0 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "impostazioni.h"
// gestione del mouse e del terminale
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

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
#pragma endregion

#pragma region input
// dichiarazioni funzioni cursore
int leggiClick(int *r, int *c);
void inputTastiera(const char *prompt, char *buf, int maxLen);
void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]);
void goTo(int x, int y);
int areaCliccata(AreaCliccabile a, int r, int c);
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
    resetImpostazioni(impostazioni);
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

  // apertura del file in lettura per caricare la schermata di impostazioni
  sprintf(nomeCompleto, PERCORSO_FILE, s.data);
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

#pragma endregion

// FUNZIONI CURSORE E NAVIGAZIONE
#pragma region funzioni cursore
// ---------------------LETTURA CLICK MOUSE---------------------------
// legge le coordinate di un click sinistro del mouse
// restituisce 1 se click valido, 0 altrimenti
#ifdef _WIN32
int leggiClick(int *r, int *c) {
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD rec;
  DWORD count;
  while (1) {
    if (!ReadConsoleInput(hIn, &rec, 1, &count))
      return 0;
    if (rec.EventType == MOUSE_EVENT &&
        rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
      *r = rec.Event.MouseEvent.dwMousePosition.Y + 1;
      *c = rec.Event.MouseEvent.dwMousePosition.X + 1;
      goTo(*c, *r);
      return 1;
    }
  }
}
#else
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
          goTo(*c, *r);
          return 1;
        }
      }
    }
  }
}
#endif
// ---------------------INPUT DA TASTIERA---------------------------
// disabilita mouse, abilita echo, legge stringa, poi ripristina
#ifdef _WIN32
void inputTastiera(const char *prompt, char *buf, int maxLen) {
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
  DWORD modeOld;
  GetConsoleMode(hIn, &modeOld);
  SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT |
                          ENABLE_PROCESSED_INPUT);
  printf("\n%s", prompt);
  fflush(stdout);
  if (fgets(buf, maxLen, stdin) != NULL)
    buf[strcspn(buf, "\n")] = '\0';
  SetConsoleMode(hIn, modeOld);
}
#else
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
#endif
// ---------------------FUNZIONI SUPPORTO CURSORE E
// AREE---------------------------
void goTo(int x, int y) {
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x - 1;
  pos.Y = y - 1;
  SetConsoleCursorPosition(hConsole, pos);
#else
  printf("\033[%d;%dH", y, x);
  fflush(stdout);
#endif
}

int areaCliccata(AreaCliccabile a, int r, int c) {
  return (r == a.r && c >= a.c1 && c <= a.c2);
}
// ---------------------NAVIGAZIONE IMPOSTAZIONI---------------------------
// loop principale: stampa schermata, leggi click, esegui azione
void navigaImpostazioni(Impostazioni *impostazioni, Stringa schermate[]) {
  int r, c, pagina = 0, esci = 0;

  // rende il terminale cliccabile
#ifdef _WIN32
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
  DWORD modeOld;
  GetConsoleMode(hIn, &modeOld);
  SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
#else
  struct termios orig, raw;
  tcgetattr(STDIN_FILENO, &orig);
  raw = orig;
  raw.c_lflag &= ~(ICANON | ECHO);
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
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
    if (!leggiClick(&r, &c))
      continue;

    // DEBUG: coordinate del click
    printf("\033[26;1H\033[KDEBUG -> riga: %d, colonna: %d", r, c);
    fflush(stdout);

    switch (pagina) {
    case 0: // --------- Impostazioni ---------
      if (areaCliccata((AreaCliccabile){9, 26, 51}, r, c))
        pagina = 1;
      else if (areaCliccata((AreaCliccabile){11, 27, 49}, r, c))
        pagina = 2;
      else if (areaCliccata((AreaCliccabile){13, 30, 45}, r, c))
        pagina = 3;
      else if (areaCliccata((AreaCliccabile){15, 28, 47}, r, c))
        pagina = 4;
      else if (areaCliccata((AreaCliccabile){17, 26, 49}, r, c))
        pagina = 5;
      else if (areaCliccata((AreaCliccabile){19, 26, 50}, r, c))
        pagina = 6;
      else if (areaCliccata((AreaCliccabile){20, 65, 70}, r, c))
        esci = 1;
      break;

    case 1: // --------- NomiGiocatori ---------
      if (areaCliccata((AreaCliccabile){12, 31, 44}, r, c)) {
        char buf[20];
        inputTastiera("Inserisci nome Giocatore 1: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_nomeGiocatore1(nome, impostazioni);
        }
      } else if (areaCliccata((AreaCliccabile){16, 31, 44}, r, c)) {
        char buf[20];
        inputTastiera("Inserisci nome Giocatore 2: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_nomeGiocatore2(nome, impostazioni);
        }
      } else if (areaCliccata((AreaCliccabile){18, 38, 44}, r, c)) {
        pagina = 0;
      }
      break;

    case 2: // --------- ModalitaDiGioco ---------
      if (areaCliccata((AreaCliccabile){13, 19, 27}, r, c)) {
        Set_modoPartita(0, impostazioni);
        printf("MODALIÀ PERSONA\n");
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){13, 49, 53}, r, c)) {
        Set_modoPartita(1, impostazioni);
        printf("MODALIÀ CPU\n");
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){16, 38, 44}, r, c)) {
        pagina = 0;
      }
      break;

    case 3: // --------- CaricaPartita ---------
      if (areaCliccata((AreaCliccabile){12, 40, 42}, r, c)) {
        char buf[20];
        inputTastiera("Nome partita da caricare: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_partitaPrecedente(nome, impostazioni);
        }
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){14, 38, 44}, r, c)) {
        pagina = 0;
      }
      break;

    case 4: // --------- SimboliGiocatori ---------
      if (areaCliccata((AreaCliccabile){12, 39, 42}, r, c)) {
        char buf[4];
        inputTastiera("Simbolo Giocatore 1 (1 carattere): ", buf, 4);
        if (buf[0] != '\0') {
          Set_simboloGiocatore1(buf[0], impostazioni);
        }
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){16, 39, 42}, r, c)) {
        char buf[4];
        inputTastiera("Simbolo Giocatore 2 (1 carattere): ", buf, 4);
        if (buf[0] != '\0') {
          Set_simboloGiocatore2(buf[0], impostazioni);
        }
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){18, 38, 44}, r, c)) {
        pagina = 0;
      }
      break;

    case 5: // --------- AnnullaImpostazioni ---------
      if (areaCliccata((AreaCliccabile){13, 29, 33}, r, c)) {
        resetImpostazioni(impostazioni);
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){13, 49, 52}, r, c)) {
        pagina = 0;
      }
      break;

    case 6: // --------- PartitaERound ---------
      if (areaCliccata((AreaCliccabile){12, 37, 46}, r, c)) {
        char buf[20];
        inputTastiera("Nome partita: ", buf, 20);
        if (buf[0] != '\0') {
          Stringa nome;
          strncpy(nome.data, buf, sizeof(nome.data) - 1);
          nome.data[sizeof(nome.data) - 1] = '\0';
          Set_nomePartita(nome, impostazioni);
        }
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){16, 40, 43}, r, c)) {
        char buf[4];
        inputTastiera("Numero round: ", buf, 4);
        if (buf[0] != '\0')
          Set_numeroRound(atoi(buf), impostazioni);
        pagina = 0;
      } else if (areaCliccata((AreaCliccabile){18, 38, 44}, r, c)) {
        pagina = 0;
      }
      break;
    }
  }

  // ripristina il terminale
#ifdef _WIN32
  SetConsoleMode(hIn, modeOld);
  system("cls");
#else
  printf("\033[?1006l\033[?1000l");
  fflush(stdout);
  tcsetattr(STDIN_FILENO, TCSANOW, &orig);
  system("clear");
#endif
  printf("Impostazioni chiuse.\n");
}
#pragma endregion