#ifndef _Jugador
#define _Jugador
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;

struct tJugador {
	string Id;
	int puntos;
};
string toString(const tJugador &jugador);
void modificarJugador(tJugador & jugador, int puntos);
bool menor(const tJugador & j1, const tJugador & j2);
bool operator<(const tJugador & opIzq, const tJugador &opDer);
#endif