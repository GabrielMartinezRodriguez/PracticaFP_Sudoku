
#include "casilla.h"


//Inicialmente casilla vacia con todos los valores posibles
void iniciaCasilla(tCasilla &casilla) {
	casilla.estado = VACIO;
	cjto_lleno(casilla.posibles);
	casilla.numero = NULL;
}


//Rellena con el caracter c la casilla 
//Si fija es true el estado se pone a FIJA: cuando se carga el tablero se llama con true, el resto de los casos a false
//El valor por defecto de fija es false

void rellenaCasilla(tCasilla & casilla, char c, bool fija ) { //fija es true cuando se lee de fichero
	int Numero;
	
	/*si el caracter es inexistente, el estado de la casilla
	se declara vacío, y el número 0 (null)*/
	if (c == ' ') {
		casilla.estado = VACIO;
		casilla.numero = NULL;
	}
	
	//en caso contrario...
	else {
		
		//el estado es fijo o relleno
		if (fija) {
			casilla.estado = FIJA;
		}
		else {
			casilla.estado = RELLENO;
		}
		 
		//el caracter se transforma a número
		Numero = c - '0';
		casilla.numero = Numero; //y se guarda en el lugar correspondiente de la estructura
		
	}
	
}

// Dibuja una casilla
void dibujaCasilla(const tCasilla &casilla) {
	int color;
	switch (casilla.estado) {
		case VACIO:
			color = PALETA[0];
			break;
		case RELLENO:
			color = PALETA[2];
			break;
		case FIJA:
			color = PALETA[1];
			break;
	}
	colorFondo(color);
	if (casilla.estado != VACIO) {
		cout << casilla.numero;
	}
	else {
		cout << " ";
	}
	colorFondo(0);
	
}

//Determina si una casilla aun no rellena tiene un unico valor posible
//recibe la casilla y el numero 
//Devuelve falso para las casillas fijas o ya rellenas
bool esSimple(const tCasilla & casilla, int & numero){
	bool devolver;

	//en caso de la casilla estar rellena o ser fija, automaticamente se devuelve falso
	if (casilla.estado == RELLENO || casilla.estado == FIJA) {
		devolver = false;
	}
	else {
		devolver = esUnitario(casilla.posibles, numero);
	}
	
	return devolver;

}

// Establece el color de fondo de una casilla
void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}