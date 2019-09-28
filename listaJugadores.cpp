#include "listaJugadores.h"

void creaListaVacia(tListaJugadores & lista) {
		lista.jugadores = new tPtrJugador[5];
		lista.contador = 0;
		lista.maximo = 5;
}

bool cargar(tListaJugadores & lista) {
	ifstream  fichero;
	fichero.open("listaJugadores.txt");
	int contador = 0;
	if (fichero.is_open()) {
		while (!fichero.eof()) {
			if (contador == lista.maximo) {
				ampliar(lista);
			}
			lista.jugadores[contador] = new tJugador;
			fichero >> lista.jugadores[contador]->Id;
			fichero >> lista.jugadores[contador]->puntos;
			contador++;
		}
		contador--;
		delete lista.jugadores[contador];

		lista.contador = contador;
		fichero.close();
		return true;
	}
	else{
		return false;
	}
	
	
}
void mostrar(const tListaJugadores & lista) {
	int contador = 0;
	string mostrar;
	cout << "JUGADORES: " << endl;
	while (contador < lista.contador) {
		mostrar = toString(*lista.jugadores[contador]);
		cout <<contador+1<<"- "<<mostrar<<endl;
		contador++;
	}
}

bool guardar(const tListaJugadores &lista) {
	int contador = 0;
	string jugador;
	ofstream fichero;
	fichero.open("listaJugadores.txt");
	if (fichero.is_open()) {
		while (contador < lista.contador) {
			jugador = toString(*lista.jugadores[contador]);
			fichero << jugador << endl;
			contador++;
		}
	}
	else {
		return false;
	}
	return true;
}

void puntuarJugador(tListaJugadores & lista, int puntos) {
	string id;
	int pos,selector;
	bool Encontrado=false, Salir = false;;
	tJugador Jugador;
	Jugador.puntos = 0;
	while (!Salir) {
		cout << "Introduzca su Identificador de jugador para poder puntuarlo: ";
		cin >> id;
		pos = buscar(lista, id,Encontrado,0,lista.contador-1);

		if (Encontrado) {
			modificarJugador(*lista.jugadores[pos], puntos);
			Salir = true;
		}
		else  {
			Jugador.Id = id;
			Jugador.puntos = 0;
			modificarJugador(Jugador, puntos);
			InsertarJugador(lista, Jugador, pos);
			Salir = true;
		}
		
	}
	guardar(lista);
}
int buscar(const tListaJugadores & lista, const string &id, bool &Encontrado,int Inicio,int Final) {
	int Centro,pos;
	Centro = (Inicio + Final) / 2;
	//COMPROBAMOS SI ES UN CASO BASE PARA RETORNAR UN VALOR
	if (Inicio > Final) {
		return Inicio;
	}
	else if (lista.jugadores[Centro]->Id == id) {
		Encontrado = true;
		return Centro;
	}
	//UNA VEZ COMPROBAMOS QUE NO ES UN CASO BASE, DECIDIMOS LLAMAR DE NUEVO A LA FUNCION BUSCAR PERO TENIENDO EN CUENTA EL INICIO Y FINAL EN FUNCION DEL RESULTADO DE LA COMPARACION
	if (id < lista.jugadores[Centro]->Id) {
		pos=buscar(lista, id, Encontrado, Inicio, Centro - 1);
	}
	else {
		pos=buscar(lista, id, Encontrado, Centro+1,Final);
	}
	return pos;
}

void InsertarJugador(tListaJugadores &lista, const tJugador &Jugador, const int pos) {
	int contador = lista.contador-1;
	if (lista.contador == lista.maximo) {
		ampliar(lista);
	}
	
	while (contador >= pos) {
		lista.jugadores[contador + 1] = lista.jugadores[contador];
		contador--;
	}
	lista.jugadores[pos] = new tJugador;
	lista.jugadores[pos]->Id = Jugador.Id;
	lista.jugadores[pos]->puntos = Jugador.puntos;
	lista.contador++;
}

tListaJugadores ordenarPorRanking(const tListaJugadores &lista) {
	tListaJugadores CopiaLista;
	tPtrJugador puntero;
	int contador1;
	int contador2;
	int selector;
	bool Encontrado = false;
	cout << "Seleccione el metodo de ordenacion que desea: "<<endl;
	cout << "1-Inserccion" << endl;
	cout << "2-Metodo de la burbuja" << endl;
	cin >> selector;
	if (selector == 1) {
		CopiaLista.contador = 0;
		CopiaLista.maximo = lista.maximo;
		CopiaLista.jugadores = new tPtrJugador[lista.maximo];
		
		CopiaLista.jugadores[0] = lista.jugadores[0];
		
		CopiaLista.contador++;
		contador1 = 1;
		contador2 = 0;
		while (contador1 < lista.contador) {
			while (contador2 < contador1 && !Encontrado) {
				if (!menor(*lista.jugadores[contador1], *CopiaLista.jugadores[contador2])) {
					Encontrado = true;
				}
				else {
					contador2++;
				}
			}
			//InsertarJugador(CopiaLista, *lista.jugadores[contador1], contador2);
			for (int i = CopiaLista.contador-1; i >= contador2;i--) {
				CopiaLista.jugadores[i + 1] = CopiaLista.jugadores[i];
			}
			CopiaLista.jugadores[contador2] = lista.jugadores[contador1];
			CopiaLista.contador++;
			contador1++;
			contador2 = 0;
			Encontrado = false;
		}
	}
	else if (selector == 2) {
		CopiaLista = CopiarLista(lista);
		contador1 = CopiaLista.contador;
		contador2 = 0;
		while (contador1 > 0) {
			while (contador2 < contador1-1) {
				if (menor(*CopiaLista.jugadores[contador2], *CopiaLista.jugadores[contador2+1])) {
					puntero = CopiaLista.jugadores[contador2];
					CopiaLista.jugadores[contador2] = CopiaLista.jugadores[contador2 + 1];
					CopiaLista.jugadores[contador2 + 1] = puntero;
				}
				contador2++;
			}
			contador1--;
			contador2 = 0;
		}
	}
	else {
		cout << "Seleccion no valida" << endl;
	}
	
	return CopiaLista;
}
void annadirJugador(tListaJugadores &lista) {
	tJugador NewPlayer;
	bool Encontrado=false;
	int pos;
	NewPlayer.puntos = 0;
	
	cout << "Introduzca el id del jugador que quiere añadir: ";
	cin >> NewPlayer.Id;
	pos = buscar(lista, NewPlayer.Id,Encontrado,0,lista.contador-1);
	if (!Encontrado) {
		InsertarJugador(lista, NewPlayer, pos);
		cout << "Jugador añadido con exito" << endl;
		guardar(lista);
	}
	else {
		cout << "No se ha podido añadir el jugador, ya que ya existe un jugador con ese id" << endl;
	}
}
	



tListaJugadores CopiarLista(const tListaJugadores &lista) {
	tListaJugadores copia;
	copia.contador = 0;
	copia.maximo = lista.maximo;
	copia.jugadores = new tPtrJugador[copia.maximo];
	for (int contador = 0; contador <lista.contador; contador++) {
		copia.jugadores[contador] = lista.jugadores[contador];
	}
	copia.contador=lista.contador;
	return copia;
}
void ampliar(tListaJugadores &lista) {
	tListaJugadores copia;
	lista.maximo = lista.maximo * 2;
	copia.jugadores = new tPtrJugador[lista.maximo];
	for (int i = 0; i < lista.maximo/2; i++) {
		copia.jugadores[i] = lista.jugadores[i];
	}
	delete[] lista.jugadores;
	lista.jugadores = copia.jugadores;

}
void borrarListaJugadores(tListaJugadores & lista) {
	for (int i = 0; i < lista.contador; i++) {
		delete lista.jugadores[i];
	}
	delete[] lista.jugadores;
}