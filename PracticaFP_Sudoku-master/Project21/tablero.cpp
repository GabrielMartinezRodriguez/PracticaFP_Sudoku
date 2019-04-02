#include "tablero.h"
#include <fstream>
/*RECIBE UN TABLERO SIN INICIALIZAR Y INICIALIZA TODAS LAS CASILLAS A ESTADO VACIO*/
void iniciaTablero(tTablero &tablero) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			iniciaCasilla(tablero[i][j]);
		}
	}
}
/*RECIBE UN TABLERO Y UN FICHERO QUE CONTIENE EL NOMBRE DEL ARCHIVO QUE CONTIENE EL SUDOKU.DEVUELVE TRUE SI LA 
CARGA HA SIDO POSIBLE O FALSE DE LO CONTRARIO LO CARGA EN LA VARIABLE TABLERO Y DEVUELVE TRUE*/
bool cargaTablero(const string &fichero, tTablero &tablero) {
	ifstream Sudoku;
	char c;
	int numero;
	Sudoku.open(fichero);
	if (Sudoku.is_open()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				Sudoku.get(c);
				rellenaCasilla(tablero[i][j], c,true);
				if (c != ' ') {
					numero = c - '0';//CONVERTIMOS LA VARIABLE C QUE ES UN CHAR EN UN INT CON SU VALOR REAL Y NO SU CODIGO ASCII
					ReajustarPosibles(tablero, i, j, numero, "Poner");
				}
				
				}
			Sudoku.get(c);
		}
		return true;
	}
	return false;
}
/*RECIBE UN TABLERO, UNA CORDENADA (FIL,COL), UN NUMERO Y UN STRING QUE CONTIENE DOS VALORES POSIBLES(PONER O QUITAR). 
ESTA FUNCION SIRVE PARA REAJUSTAR DE LAS CASILLAS LOS VALORES POSIBLES CUANDO ESTE SUFRE ALGUN CAMBIO*/
void ReajustarPosibles(tTablero &tablero, int fila, int col, int c,string Modo) {
	int EsquinaFila, EsquinaColumna;
	//CON ESTO SE CONSIGUE OBTENER LA CORDENADA SUPERIOR IZQUIERDA DE LA SUBMATRIZ DE UNA CASILLA
	EsquinaFila = fila - fila % 3;
	EsquinaColumna = col - col % 3;
	if (Modo=="Poner") {
		for (int i = 0; i < 9; i++) {

			delElemento(tablero[i][col].posibles, c);

		}
		for (int j = 0; j < 9; j++) {
			delElemento(tablero[fila][j].posibles, c);
		}
		
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				delElemento(tablero[EsquinaFila + i][EsquinaColumna + j].posibles, c);
			}
		}
	}
	else if (Modo=="Quitar") {
		for (int i = 0; i < 9; i++) {
			if (esPosible(tablero, fila, i, c)) {
				addElemento(tablero[i][col].posibles, c);
			}
		}
		for (int j = 0; j < 9; j++) {
			if (esPosible(tablero, j, col, c)) {
				addElemento(tablero[fila][j].posibles, c);
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (esPosible(tablero, EsquinaFila + i, EsquinaColumna + j, c)) {
					addElemento(tablero[EsquinaFila + i][EsquinaColumna + j].posibles, c);
				}
				
			}
		}
	}
	
}
/*ESTA FUNCION RECIBE EL TABLERO, UNA CORDENADA DE UNA CASILLA, Y UN NUMERO. SE UTILIZA CUANDO SE QUITA UN NUMERO DE UNA CASILLA PARA SABER SI ES POSIBLE 
QUITARLO DE POSIBLES DE OTRA CASILLA. DEVULEVE TRUE SI ES POSIBLE QUITARLO Y FALSE SI NO ES POSIBLE*/
bool esPosible(tTablero &tablero,int fila,int col,int c) {
	bool posible = true;
	int EsquinaFila, EsquinaColumna;
	int contador = 0,contador1=0,contador2=0;

	while(contador<9&&posible){
		if (tablero[contador][col].numero==c) {
			posible = false;
		}
		contador++;
	}
	contador = 0;
	while (contador < 9 && posible) {
		if (tablero[fila][contador].numero==c) {
			posible = false;
		}
		contador++;
	}
	
	EsquinaFila = fila - fila % 3;
	EsquinaColumna = col - col % 3;
	while (contador1 < 3 && posible) {
		while (contador2 < 3 && posible) {
			if (tablero[EsquinaFila+contador1][EsquinaColumna+contador2].numero==c) {
				posible = false;
			}
			contador2++;
		}
		contador2 = 0;
		contador1++;
	}
	return posible;
}
//SE UTILIZA PARA PONER UN NUMERO EN UNA CASILLA VACIA. DEVUELVE TRUE SI SE PUDO PONER EL NUMERO EN LA CASILLA
bool ponerNum(tTablero &tablero, int x, int y, int c) {
	char CtoAscii;
	bool devolver = false;
		if (pertenece(tablero[x][y].posibles, c)) {
			CtoAscii = c + '0';
			rellenaCasilla(tablero[x][y], CtoAscii,false);
			ReajustarPosibles(tablero, x, y, c,"Poner");
			devolver = true;
		}
	
	return devolver;
}
//SE UTILIZA PARA BORRAR UN NUMERO DE UNA CASILLA RELLENA. DEVUELVE TRUE SI SE PUDO BORRAR EL NUMERO DE LA CASILLA
bool borraNum(tTablero &tablero, int x, int y) {
	int numero;
	bool devolver = false;
	if (tablero[x][y].estado == RELLENO) {
		
			numero = tablero[x][y].numero;
			rellenaCasilla(tablero[x][y], ' ',false);
			ReajustarPosibles(tablero, x, y, numero,"Quitar");
			devolver = true;
	
	}
	return devolver;
}
//ESTA FUNCION COMPRUEBA SI ESTA LLENO EL TABLERO. DEVUELVE TRUE SI LO ESTA Y FALSE SI NO
bool tableroLleno(const tTablero &tablero) {
	for (int i=0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tablero[i][j].estado == VACIO) {
				return false;
			}
		}
	}
	return true;
}
//RECIBE LOS VALORES POSIBLES DE UNA CASILLA, Y UNA CORDENADA DE UNA CASILLA. IMPRIME LOS VALORES POSIBLES DE LA CASILLA
void mostrarPosibles(const tTablero &tablero, int x, int y) {
	if (tablero[x][y].estado != FIJA) {
		for (int i = 0; i < 9; i++) {
			if (tablero[x][y].posibles.elementos[i]) {
				cout << i + 1<<" ";
			}
		}
	}
}
//RECIBE EL TABLERO Y RELLENA TODAS LAS CASILLAS SIMPLES CON SU UNICO VALOR POSIBLE
void rellenarSimples(tTablero &tablero) {
	int numero;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (esSimple(tablero[i][j], numero)) {
				ponerNum(tablero, i, j,numero);
			}
		}
	}
}
//RECIBE EL TABLERO, Y LO MUESTRA POR PANTALLA
void dibujarTablero(const tTablero &tablero) {
	cout <<"-------------------" << endl;
	for (int i = 0; i < 9; i++) {
		
		cout << "|";
		for (int j = 0; j < 9; j++) {
			dibujaCasilla(tablero[i][j]);
			if (j % 3 != 2) {
				cout << " ";
			}
			if (j % 3 == 2) {
				cout << "|";
			}
		}
		if (i % 3 == 2) {
			cout <<endl<< "-------------------";
		}
		cout << endl;
	}
}
