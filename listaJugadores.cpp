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
			cout << "0-Salir sin puntuar";
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
		lista.jugadores[contador + 1].Id = lista.jugadores[contador ].Id;
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
	int contador1 = 1;
	int contador2 = 0;
	bool Encontrado = false;
	CopiaLista.jugadores[0].Id = lista.jugadores[0].Id;
	CopiaLista.jugadores[0].puntos = lista.jugadores[0].puntos;
	CopiaLista.contador++;

	while (contador1 < lista.contador) {
		while (contador2 < contador1&&!Encontrado) {
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
	return CopiaLista;
}