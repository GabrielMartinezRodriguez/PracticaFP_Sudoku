#ifndef _juego
#define _juego


#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "tablero.h"
using namespace std;



// Tipos de Sudokus
typedef enum { FACIL, MEDIO, DIFICIL } tNivelSudoku;

// tipo Sudoku
typedef struct {
	string fichero;
	int nivel;
} tSudoku;

// Juego
typedef struct {
	tSudoku sudoku;
	tTablero tablero;
	bool terminado;
}tJuego;

// Mostrar menú de acciones para jugar un sudoku
int mostrarMenuJugada();
// Bucle del juego de un sudoku
int JugarUnSudoku(tSudoku &sudoku);

// Inicializa el juego
void iniciaJuego(tJuego & juego, const tSudoku &sudoku);

//muestra el juego
void mostrarJuego(const tJuego &juego);

//CADA OPCION REALIZA LA FUNCION CORRESPONDIENTE A LA OPCION DEL MENU
void Opcion5(tJuego &juego);
void Opcion4(tJuego &juego, tSudoku &sudoku);
void Opcion3(tJuego &juego);
void Opcion2(tJuego &juego);
void Opcion1(tJuego &juego);
//carga del juego
bool cargaJuego(tJuego & juego, const tSudoku &sudoku);
//PIDE UNA CASILLA ES DECIR UNA CORDENADA QUE SEA POSIBLE EN EL TABLERO DE 9X9
void PedirCasilla(int &x, int &y);

#endif
