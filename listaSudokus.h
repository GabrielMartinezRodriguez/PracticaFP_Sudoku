#ifndef _listaSudokus
#define _listaSudokus
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
#include "juego.h"

using namespace std;

// Número máximo de Sudokus registrados
const int MAX_SUDOKUS = 20;

// Array de Sudokus
typedef tSudoku tSudokus[MAX_SUDOKUS];

// Lista de Sudokus
typedef struct {
	tSudokus array;	// Array de sudokus
	int cont;	
} tListaSudokus;

bool cargarListaSudokus(tListaSudokus & lista);
void mostrarListaSudokus(const tListaSudokus &lista);
void creaListaSudokus(tListaSudokus & lista);
int menuListaSudokus(const tListaSudokus &lista);
void Insertar(tListaSudokus &lista, const tSudoku &Sudoku, const int Posicion);
bool operator<(const tSudoku &S1, const tSudoku &S2);
int buscarPos(const tListaSudokus & lista, const tSudoku &sudoku);
bool buscarFichero(const tListaSudokus & lista, string nombreFich);
bool registrarSudoku(tListaSudokus & lista);
bool guardar(const tListaSudokus & lista);
bool BorrarSudoku(tListaSudokus &lista);
#endif