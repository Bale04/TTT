/*
 ============================================================================
 Name        : TTT.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struttura della gestione delle stringhe
typedef struct {
    char data[20];
} Stringa;

// struttura delle impostazioni della partita
typedef struct{
	int modoPartita;  // 1 - CPU,   0 - Giocatore
	Stringa nomeGiocatore1;  // nome del giocatore 1
	char simboloGiocatore1;  // simbolo giocatore 1
	Stringa nomeGiocatore2;  // nome del giocatore 2
	char simboloGiocatore2;  // simbolo del giocatore 2
	Stringa partitaPrecedente;  // nome della partita da riprendere
	int annullaImpostazioni;  // 1 - Default,  0 - Modificate
	int numeroRound;  // numero dei round
	Stringa nomePartita;  // nome della partita da giocare
}Impostazioni;

// FUNZIONI DI ACCESSO
// ---------------------MODO PARTITA---------------------------
void Set_modoPartita(int m, Impostazioni* impostazioni){
	impostazioni->modoPartita = m;
}
int Get_modoPartita(Impostazioni impostazioni){
	return impostazioni.modoPartita;
}
// ---------------------NOMI GIOCATORI---------------------------
void Set_nomeGiocatore1(Stringa n1, Impostazioni *impostazioni){
	strncpy(impostazioni->nomeGiocatore1.data, n1.data, sizeof(impostazioni->nomeGiocatore1.data) - 1);
	// la funzione copia una stringa di caratteri (n1) in un'altra stringa (nomeGiocatore1) dando come limite la dimensione massima dell'array di destinazione.
}
Stringa Get_nomeGiocatore1(Impostazioni impostazioni){
	return impostazioni.nomeGiocatore1;
}
// ------------------------------------------------
void Set_nomeGiocatore2(Stringa n2, Impostazioni* impostazioni){
	strncpy(impostazioni->nomeGiocatore2.data, n2.data, sizeof(impostazioni->nomeGiocatore2.data) - 1);
}
Stringa Get_nomeGiocatore2(Impostazioni impostazioni){
	return impostazioni.nomeGiocatore2;
}
// --------------------SIMBOLI GIOCATORI----------------------------
void Set_simboloGiocatore1(char s1, Impostazioni* impostazioni){
	impostazioni->simboloGiocatore1 = s1;
}
char Get_simboloGiocatore1(Impostazioni impostazioni){
	return impostazioni.simboloGiocatore1;
}
// ------------------------------------------------
void Set_simboloGiocatore2(char s2, Impostazioni* impostazioni){
	impostazioni->simboloGiocatore2 = s2;
}
char Get_simboloGiocatore2(Impostazioni impostazioni){
	return impostazioni.simboloGiocatore2;
}
// ------------------PARTITA PRECEDENTE------------------------------

// ---------------------IMPOSTAZIONI DEFAULT---------------------------

// ---------------------ROUND DA GIOCARE---------------------------

// ---------------------NOME PARTITA---------------------------



int main(void) {
	// appena si avvia il codice si impostano le impostazioni di default.
	Impostazioni impostazioni={1, {"giocatore1"}, 'X', {"giocatore2"}, 'O',{""}, 1, 3, {"partita"}};
	Stringa pazz= {"NIGGERS\n"};
	Set_nomeGiocatore1(pazz, &impostazioni);
	printf("%s", Get_nomeGiocatore1(impostazioni).data);
	return EXIT_SUCCESS;
}
