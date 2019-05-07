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
string toString(const tJugador &jugador);//Devuelve un string que contiene el id y los puntos de un jugador
void modificarJugador(tJugador & jugador, int puntos);//Añade a un jugador los puntos que hay en la variable puntos
bool menor(const tJugador & j1, const tJugador & j2);//Devuelve true si j1 es menor que j2 teniendo en cuenta los puntos y en caso de empate el id
bool operator<(const tJugador & opIzq, const tJugador &opDer);//Hace una comparacion de los id de cada jugador con el operador <
#endif