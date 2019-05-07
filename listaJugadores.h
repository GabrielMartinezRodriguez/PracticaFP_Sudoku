#ifndef _listaJugadores
#define _listaJugadores
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
#include "Jugador.h"

const int  MAX_JUGADORES = 10;
typedef tJugador *tPtrJugador;
struct tListaJugadores {
	tPtrJugador jugadores;
	int contador;
	int tama�o;
};

void creaListaVacia(tListaJugadores & lista);//Inicializa la lista de jugadores a una lista vacia
bool cargar(tListaJugadores & lista);//Carga a memoria los jugadores del fichero listajugadores.txt. Devuelve true si ha sido posible y false si no
void mostrar(const tListaJugadores & lista);//Muestra por pantalla la lista de jugadores ordenadas por Id
bool guardar(const tListaJugadores &lista);//Guarda la lista de jugadores en el fichero listajugadores.txt
void puntuarJugador(tListaJugadores & lista, int puntos);//A�ade los puntos a un jugadores existente y si no existe lo crea y lo inserta en la posicion correspondiente
bool buscar(const tListaJugadores & lista, string id, int &pos, int &Inicio, int &Final);
void InsertarJugador(tListaJugadores &lista, const tJugador &Jugador, const int pos);//Inserta el jugador en la posicion indicada por el parametro pos
tListaJugadores ordenarPorRanking(const tListaJugadores &lista);//Hace una copia de la lista de jugadores y la ordena por ranking y posteriormente la devuelve
void annadirJugador(tListaJugadores &lista);
void CopiarLista(const tListaJugadores &lista, tListaJugadores &Copia);
void ampliar(tListaJugadores & lista);
void borrarListaJugadores(tListaJugadores & lista);
#endif