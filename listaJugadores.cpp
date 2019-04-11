#include "listaJugadores.h"

void creaListaVacia(tListaJugadores & lista) {
	int contador = 0;

	while (contador < MAX_JUGADORES) {
		lista.contador = 0;
		lista.jugadores[contador].Id = "";
		lista.jugadores[contador].puntos = NULL;
		contador++;
	}
}

bool cargar(tListaJugadores & lista) {
	ifstream  fichero;
	fichero.open("listaJugadores.txt");
	int contador = 0;
	while (!fichero.eof()) {
		fichero >> lista.jugadores[contador].Id;
		fichero >> lista.jugadores[contador].puntos;
		contador++;
	}
	lista.contador = contador-1;
	return true;
}
void mostrar(const tListaJugadores & lista) {
	int contador = 0;
	string mostrar;
	cout << "JUGADORES: " << endl;
	while (contador < lista.contador) {
		mostrar = toString(lista.jugadores[contador]);
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
			jugador = toString(lista.jugadores[contador]);
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
	bool Encontrado, Salir = false;;
	tJugador Jugador;
	Jugador.puntos = 0;
	while (!Salir) {
		cout << "Introduzca su Identificador de jugador para poder puntuarlo: ";
		cin >> id;
		Encontrado = buscar(lista, id, pos);

		if (Encontrado) {
			modificarJugador(lista.jugadores[pos], puntos);
			Salir = true;
		}
		else if (lista.contador < MAX_JUGADORES) {
			Jugador.Id = id;
			modificarJugador(Jugador, puntos);
			InsertarJugador(lista, Jugador, pos);
			Salir = true;
		}
		else {
			cout << "NO SE ENCONTRO EL IDENTIFICADOR Y LA LISTA ESTA LLENA."<<endl;
			cout << "1-Introduzca un identificador de un jugador ya registrado" << endl;
			cout << "0-Salir sin puntuar: ";
			cin >> selector;
			if (selector == 0) {
				Salir = true;
			}
		}
	}
	guardar(lista);
}
bool buscar(const tListaJugadores & lista, string id, int &pos) {
	int Centro, Inicio = 0, Final = lista.contador - 1;
	bool Encontrado = false;
	while (Inicio <= Final && !Encontrado) {
		Centro = (Inicio + Final) / 2;
		if (lista.jugadores[Centro].Id == id) {
			Encontrado = true;
			pos = Centro;
		}
		else if (id<lista.jugadores[Centro].Id){
			Final = Centro - 1;
		}
		else {
			Inicio = Centro + 1;
		}
	}
	if (!Encontrado) {
		pos = Inicio;
	}
	return Encontrado;
}

void InsertarJugador(tListaJugadores &lista, const tJugador &Jugador, const int pos) {
	int contador = lista.contador - 1;
	while (contador >= pos) {
		lista.jugadores[contador + 1].Id = lista.jugadores[contador].Id;
		lista.jugadores[contador + 1].puntos = lista.jugadores[contador].puntos;
		contador--;
	}
	lista.jugadores[pos].Id = Jugador.Id;
	lista.jugadores[pos].puntos = Jugador.puntos;
	lista.contador++;
}

tListaJugadores ordenarPorRanking(const tListaJugadores &lista) {
	tListaJugadores CopiaLista;
	creaListaVacia(CopiaLista);
	tJugador Aux;
	int contador1;
	int contador2;
	int selector;
	bool Encontrado = false;
	cout << "Seleccione el metodo de ordenacion que desea: "<<endl;
	cout << "1-Inserccion" << endl;
	cout << "2-Metodo de la burbuja" << endl;
	cin >> selector;
	if (selector == 1) {
		CopiaLista.jugadores[0].Id = lista.jugadores[0].Id;
		CopiaLista.jugadores[0].puntos = lista.jugadores[0].puntos;
		CopiaLista.contador++;
		contador1 = 1;
		contador2 = 0;
		while (contador1 < lista.contador) {
			while (contador2 < contador1 && !Encontrado) {
				if (!menor(lista.jugadores[contador1], CopiaLista.jugadores[contador2])) {
					Encontrado = true;
				}
				else {
					contador2++;
				}
			}
			InsertarJugador(CopiaLista, lista.jugadores[contador1], contador2);
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
				if (menor(CopiaLista.jugadores[contador2], CopiaLista.jugadores[contador2+1])) {
					Aux.Id = CopiaLista.jugadores[contador2].Id;
					Aux.puntos = CopiaLista.jugadores[contador2].puntos;
					CopiaLista.jugadores[contador2].Id = CopiaLista.jugadores[contador2 + 1].Id;
					CopiaLista.jugadores[contador2].puntos = CopiaLista.jugadores[contador2 + 1].puntos;
					CopiaLista.jugadores[contador2 + 1].Id = Aux.Id;
					CopiaLista.jugadores[contador2 + 1].puntos = Aux.puntos;
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
	bool Encontrado;
	int pos;
	NewPlayer.puntos = 0;
	if (lista.contador < MAX_JUGADORES) {
		cout << "Introduzca el id del jugador que quiere añadir: ";
		cin >> NewPlayer.Id;
		Encontrado = buscar(lista, NewPlayer.Id, pos);
		if (!Encontrado) {
			InsertarJugador(lista, NewPlayer, pos);
			cout << "Jugador añadido con exito" << endl;
			guardar(lista);
		}
		else {
			cout << "No se ha podido añadir el jugador, ya que ya existe un jugador con ese id" << endl;
		}
	}
	else {
		cout << "La lista de jugadores esta llena" << endl;
	}
	
}

tListaJugadores CopiarLista(const tListaJugadores &lista) {
	return lista;
}