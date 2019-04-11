#include "listaSudokus.h"
bool cargarListaSudokus(tListaSudokus & lista) {
	int contador = 0;
	
	ifstream fichero;
	fichero.open("listaSudokus.txt");
	if (fichero.is_open()) {
	   
		while (!fichero.eof()) {
			fichero >> lista.array[contador].fichero;
		    fichero >> lista.array[contador].nivel;
		    contador++;
		}
		
		lista.cont = contador-1;
		return true;
	}
	else {
		return false;
	}
	
}

void mostrarListaSudokus(const tListaSudokus &lista) {
	int contador = 0;
	while (contador < lista.cont) {
		cout << contador + 1 << "-";
		cout << lista.array[contador].fichero<<" ";
		switch (lista.array[contador].nivel) {
			case 0:
				cout << "FACIL"<<endl;
				break;
			case 1:
				cout << "MEDIO" << endl;
				break;
			case 2:
				cout << "DIFICIL" << endl;
				break;
		}
		contador++;
	}
}

void creaListaSudokus(tListaSudokus & lista) {
	int contador = 0;
	lista.cont = 0;
	while (contador < MAX_SUDOKUS) {
		lista.array[contador].fichero = " ";
		contador++;
	}
}

int menuListaSudokus(const tListaSudokus &lista) {
	int selector = -1;
	
	while (selector<1 || selector>lista.cont) {
		mostrarListaSudokus(lista);
		cin >> selector;
	}
	selector--;
	return selector;
}

bool guardar(const tListaSudokus & lista) {
	int contador = 0;
	ofstream fichero;
	fichero.open("listaSudokus.txt");
	if (fichero.is_open()) {
		while (contador < lista.cont) {
			fichero << lista.array[contador].fichero << " " << lista.array[contador].nivel << endl;
			contador++;
		}
		fichero.close();
	}
	else {
		return false;
	}
	return true;
}

bool registrarSudoku(tListaSudokus & lista) {
	tSudoku Sudoku;
	int Posicion;
	ifstream fichero;
	
	if (lista.cont < MAX_SUDOKUS) {
		cout << "Introduzca el fichero que contiene el sudoku en la carpeta del juego y posteriormente,"<<endl<<"introduzca el nombre del fichero (con la extension .txt): ";
		cin >> Sudoku.fichero;
		
		if (!buscarFichero(lista, Sudoku.fichero)) {
			fichero.open(Sudoku.fichero);
			if (fichero.is_open()) {
				cout << "Introduzca el nivel de dificultad:" << endl << "0-Facil" << endl << "1-Medio" << endl << "2-Dificil" << endl;
				cin >> Sudoku.nivel;
				if (Sudoku.nivel >= 0 && Sudoku.nivel <= 2) {
					Posicion = buscarPos(lista, Sudoku);
					Insertar(lista, Sudoku, Posicion);
					guardar(lista);
					return true;
				}
				else {
					cout << "No es un nivel de dificultad valido" << endl;
				}
				
			}
			else {
				cout << "No se ha encontrado el fichero en la carpeta" << endl;
			}
		}
		else {
			cout << "Ya existe un sudoku con ese nombre" << endl;
			return false;
		}
	}
	else{
		cout << "La lista de sudokus esta llena" << endl;
		return false;
	}
}

bool buscarFichero(const tListaSudokus & lista, string nombreFich) {
	int puntos,contador=0;
	bool Encontrado = false;
	
	while (contador<lista.cont&&!Encontrado) {
		if (lista.array[contador].fichero == nombreFich) {
			Encontrado = true;
			
		}
		contador++;
	}
	return Encontrado;
}

int buscarPos(const tListaSudokus & lista, const tSudoku &sudoku) {
	int Inicio=0,Final=lista.cont-1,Centro=0;
	
	while (Inicio <= Final) {
		Centro = (Inicio + Final) / 2;
		if (sudoku <lista.array[Centro] ){
			Final = Centro - 1;
		}
		else {
			Inicio = Centro + 1;
		}
	}
	return Inicio;
}

bool operator<(const tSudoku &S1, const tSudoku &S2) {
	if (S1.nivel >= S2.nivel) {
		if (S1.nivel == S2.nivel) {
			return S1.fichero < S2.fichero;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}

void Insertar(tListaSudokus &lista,const tSudoku &Sudoku,const int Posicion) {
	int cont = lista.cont-1;
	while (cont>=Posicion) {
		lista.array[cont + 1].fichero = lista.array[cont].fichero;
		lista.array[cont + 1].nivel = lista.array[cont].nivel;
		cont--;
	}
	lista.array[Posicion].fichero = Sudoku.fichero;
	lista.array[Posicion].nivel = Sudoku.nivel;
	lista.cont++;
}
bool BorrarSudoku(tListaSudokus &lista) {
	int selector = 0, contador ;
	bool correcto;
	cout << "Seleccione el sudoku que desea borrar:" << endl;;
	selector=menuListaSudokus(lista);
	contador = selector ;
	while (contador < lista.cont) {
		lista.array[contador].fichero = lista.array[contador + 1].fichero;
		lista.array[contador].nivel = lista.array[contador + 1].nivel;
		contador++;
	}
	lista.array[lista.cont - 1].fichero = "";
	lista.array[lista.cont - 1].nivel = NULL;
	lista.cont--;
	correcto = guardar(lista);
	return correcto;
}