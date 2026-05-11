/*
 ============================================================================
 Name        : impostazioni.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 0.3
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe
#include "impostazioni.h"



// DEFINIZIONE FUNZIONI DI ACCESSO
#pragma region definizione funzioni di accesso
void Set_modoPartita(int m, Impostazioni* impostazioni);
int Get_modoPartita(Impostazioni impostazioni);
void Set_nomeGiocatore1(Stringa n1, Impostazioni *impostazioni);
Stringa Get_nomeGiocatore1(Impostazioni impostazioni);
void Set_nomeGiocatore2(Stringa n2, Impostazioni* impostazioni);
Stringa Get_nomeGiocatore2(Impostazioni impostazioni);
void Set_simboloGiocatore1(char s1, Impostazioni* impostazioni);
char Get_simboloGiocatore1(Impostazioni impostazioni);
void Set_simboloGiocatore2(char s2, Impostazioni* impostazioni);
char Get_simboloGiocatore2(Impostazioni impostazioni);
void Set_partitaPrecedente(Stringa p, Impostazioni *impostazioni);
Stringa Get_partitaPrecedente(Impostazioni impostazioni);
void Set_annullaImpostazioni(int x, Impostazioni* impostazioni);
int Get_annullaImpostazioni(Impostazioni impostazioni);
void Set_numeroRound(int r, Impostazioni* impostazioni);
int Get_numeroRound(Impostazioni impostazioni);
void Set_nomePartita(Stringa n, Impostazioni* impostazioni);
Stringa Get_nomePartita(Impostazioni impostazioni);
#pragma endregion

#pragma region main
int main(void) {
	// appena si avvia il codice si impostano le impostazioni di default.
	Impostazioni impostazioni={1, {"giocatore1"}, 'X', {"giocatore2"}, 'O',{""}, 1, 3, {"partita"}};
	FILE *fpImpostazioni;
	int c;

	// apre il file in lettura per caricare la schermata di impostazioni
	fpImpostazioni = fopen("Impostazioni.txt", "r");
	if (fpImpostazioni == NULL) {
		printf("Errore Caricamento Impostazioni\n");
	} else {
		// finchè non raggiunge la fine del file legge i caratteri man mano e li stampa a schermo
		while ((c = fgetc(fpImpostazioni)) != EOF) {
			putchar(c);
		}
		fclose(fpImpostazioni);
		printf("\n");
	}

	Stringa nom = {""};
	// Set_nomeGiocatore1(nom, &impostazioni);
	// printf("\n%s\n", Get_nomeGiocatore1(impostazioni).data);
	return EXIT_SUCCESS;
}
#pragma endregion



// FUNZIONI DI ACCESSO
#pragma region 
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
void Set_partitaPrecedente(Stringa p, Impostazioni *impostazioni){
	strncpy(impostazioni->nomeGiocatore2.data, p.data, sizeof(impostazioni->nomeGiocatore2.data) - 1);

}
Stringa Get_partitaPrecedente(Impostazioni impostazioni){
	return impostazioni.partitaPrecedente;
}
// ---------------------IMPOSTAZIONI DEFAULT---------------------------
void Set_annullaImpostazioni(int x, Impostazioni* impostazioni){
	impostazioni->annullaImpostazioni = x;
	if (x==1){
		impostazioni->modoPartita = 1;
		strncpy(impostazioni->nomeGiocatore1.data, "giocatore1", sizeof(impostazioni->nomeGiocatore1.data) - 1);
		impostazioni->simboloGiocatore1 = 'X';
		strncpy(impostazioni->nomeGiocatore2.data, "giocatore2", sizeof(impostazioni->nomeGiocatore2.data) - 1);
		impostazioni->simboloGiocatore2 = 'O';
		strncpy(impostazioni->partitaPrecedente.data, "", sizeof(impostazioni->partitaPrecedente.data) - 1);
		impostazioni->numeroRound = 3;
		strncpy(impostazioni->nomePartita.data, "partita", sizeof(impostazioni->nomePartita.data) - 1);
	}
}
int Get_annullaImpostazioni(Impostazioni impostazioni){
	return impostazioni.annullaImpostazioni;
}
// ---------------------ROUND DA GIOCARE---------------------------
void Set_numeroRound(int r, Impostazioni* impostazioni){
	impostazioni->numeroRound = r;
}
int Get_numeroRound(Impostazioni impostazioni){
	return impostazioni.numeroRound;
}
// ---------------------NOME PARTITA---------------------------
void Set_nomePartita(Stringa n, Impostazioni* impostazioni){
	strncpy(impostazioni->nomePartita.data, n.data, sizeof(impostazioni->nomePartita.data) - 1);
}
Stringa Get_nomePartita(Impostazioni impostazioni){
	return impostazioni.nomePartita;
}
#pragma endregion