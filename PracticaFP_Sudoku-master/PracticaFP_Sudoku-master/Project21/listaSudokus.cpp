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
		
		lista.cont = contador;
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
	cout << "Introduzca el nombre del fichero (con la extension .txt) " << endl;
	cin >> Sudoku.fichero;
	if (!buscarFichero(lista,Sudoku.fichero)) {
		cout << "Introduzca los puntos que se obtienen al resolverlo" << endl;
		cin >> Sudoku.nivel;
		Posicion=buscarPos(lista, Sudoku);
		Insertar(lista, Sudoku,Posicion);
	}
	return true;

}
bool buscarFichero(const tListaSudokus & lista, string nombreFich) {
	ifstream listaSudokus;
	string Fichero;
	int puntos;
	bool Encontrado = false;
	listaSudokus.open("listaSudokus.txt");

	while (!listaSudokus.eof()&&!Encontrado) {
		listaSudokus >> Fichero;
		listaSudokus >> puntos;
		if (Fichero == nombreFich) {
			Encontrado = true;
		}
	}
	return Encontrado;
}
int buscarPos(const tListaSudokus & lista, const tSudoku &sudoku) {
	int Inicio=0,Final=lista.cont-1,Centro=0;
	
	while (Inicio <= Final) {
		Centro = (Inicio + Final) / 2;
		if (lista.array[Centro] < sudoku){
			Inicio = Centro + 1;

		}
		else {
			Final = Centro - 1;
		}
	}
	return Centro;
	
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
	int cont = lista.cont;
	while (cont>=Posicion) {
		lista.array[cont + 1].fichero = lista.array[cont].fichero;
		lista.array[cont + 1].nivel = lista.array[cont].nivel;
		cont--;
	}
	lista.array[Posicion].fichero = Sudoku.fichero;
	lista.array[Posicion].nivel = Sudoku.nivel;
}