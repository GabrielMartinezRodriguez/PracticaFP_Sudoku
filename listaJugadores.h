#ifndef _listaJugadores
#define _listaJugadores
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
#include "Jugador.h"

const int  MAX_JUGADORES = 10;
struct tListaJugadores {
	tJugador jugadores[MAX_JUGADORES];
	int contador;
};

void creaListaVacia(tListaJugadores & lista);
bool cargar(tListaJugadores & lista);
void mostrar(const tListaJugadores & lista);
bool guardar(const tListaJugadores &lista);
void puntuarJugador(tListaJugadores & lista, int puntos);
bool buscar(const tListaJugadores & lista, string id, int &pos);
void InsertarJugador(tListaJugadores &lista, const tJugador &Jugador, const int pos);
tListaJugadores ordenarPorRanking(const tListaJugadores &lista);
#endif